//////////////////////////////////////////////////////////////////
//  ior.c				
//							
// Archivo principal del experimento IOR. 
//  
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//
//		FUNCIONAMIENTO GENERAL DE UN EXPERIMENTO PROGRAMADO CON GLUT
//
//	En la función main() se van llamando sucesivamente a las distintas funciones de
//	inicialización y control de las librerias GLUT/GLX/OPENGL. Aquellas que no sea común
//	alterar su comportamiento se encuentran recogidas en el archivo "glutcontrol.c"; las 
//	funciones que habitualmente han de editarse, pues regulan la interacción con el 
//	sujeto durante el experimento, son las siguientes:
//		-ExperimentFSA(): Autómata de estados finitos que lee una variable
//		 de estado global "g_state" y en función de su valor dirige el 
//		 flujo del experimentos (recogida de eventos,interacción con el usuario,
//		 salida gráfica y grabación de los datos). Esta función es llamada periodicamente,
//		 aunque puede emplearse como retrollamada del thread de recogida de
//		 datos wacom, con lo determinaría un comportamiento asíncrono. Es una buena
//		 práctica tener asignada sólo un tipo de retrollamada para la funcion 
//		 ExperimentFSA(), pues de otra forma resultaría inseguro distinguir que modo 
//		 a disparado la función y cómo debe comportarse el programa.
//		-GraphicOutput(): Programado también bajo un paradigma FSA, en función
//		 del estado del experimento, la salida gráfica es distinta. Para esto,
//		 la función lee igualmente el valor de "g_state" y decide a que funciones de
//		 graficado es necesario llamar y con que argumentos. Estas funciones se encuentran
//		 en el archivo "drawingfunctions.c"
//		-OnKeyboard(): Función manejadora de los eventos de teclado. Su argumento es el
//		 valor ASCII de la tecla pulsada. También se pueden instalar otros manejadores
//		 de eventos: OnMouse(), OnTablet().
//		-GrabarDatos(): Imprime a un archivo los resultados del experimento almacenados
//		 en la estructura de RESULTADOS "data".  
//
///////////////////////////////////////////////////////////////////////////////////////////


#include "ior.h"

////////////////////////////////////////////////////   WACOM GLOBALS
extern struct ABS_STATE gAbsState[WACOMFIELD_MAX];
extern struct KEY_STATE gKeyState[WACOMBUTTON_MAX];

////////////////////////////////////////////////////   GLUT GLOBALS
int window;
static int g_counter = 0;

////////////////////////////////////////////////////   IOR GLOBALS
int g_xpos = INIT_X;
int g_ypos = INIT_Y;
int g_state = EXP_STATE_PRE;
int g_init_time = 0;
FILE* archivo = NULL;
int flag = FALSE;
int next_time;
struct RESULTADOS data;


//------------------------------------------------------------  ExperimentFSA()
//
void ExperimentFSA(int value) {
			
	g_counter = value + 1; 

	switch(g_state)
	{
		
		case EXP_STATE_PRE:						
			if (gAbsState[WACOMFIELD_PRESSURE].nValue > 0) {
				g_state=EXP_STATE_SEGUIMIENTO1;
				g_init_time = glutGet(GLUT_ELAPSED_TIME);
			}				
		break;
		
		case EXP_STATE_SEGUIMIENTO1:
			g_xpos += SPEED;
			if(CheckError()) {
				g_state = EXP_STATE_ERROR;
				break;
			}				
			else if (glutGet(GLUT_ELAPSED_TIME) - g_init_time > FLASH_INIT_TIME) {
				g_state = EXP_STATE_FLASH;
			}
			else {
				GraphicOutput();
				glutSwapBuffers();
			}
		break;
		
		case EXP_STATE_FLASH:
			g_xpos += SPEED;
			if(CheckError()) {
				g_state = EXP_STATE_ERROR;
				break;
			}
			else if (glutGet(GLUT_ELAPSED_TIME) - g_init_time > FLASH_END_TIME) {
				g_state = EXP_STATE_SEGUIMIENTO2;
				GraphicOutput();
				glutSwapBuffers();
			}
			else {
				GraphicOutput();
				glutSwapBuffers();
			}
		break;
			
		case EXP_STATE_SEGUIMIENTO2:
			g_xpos += SPEED;		
			if(CheckError()) {
				g_state = EXP_STATE_ERROR;
				break;
			}
			else if (glutGet(GLUT_ELAPSED_TIME) - g_init_time > TOTAL_END_TIME)	{
				g_state = EXP_STATE_RESPUESTA;
			}
			else {
				GraphicOutput();
				glutSwapBuffers();
			}			
		break;
		
		case EXP_STATE_RESPUESTA:			
			if (gAbsState[WACOMFIELD_PRESSURE].nValue == 0)
				flag = TRUE;
			if (flag && (gAbsState[WACOMFIELD_PRESSURE].nValue > 0) ) {
				data.x=(int)gAbsState[WACOMFIELD_POSITION_X].nValue * X_FACTOR;
				data.y=(int)gAbsState[WACOMFIELD_POSITION_Y].nValue * Y_FACTOR;
				exit(0);
			}
		break;
		
		case EXP_STATE_ERROR:			
			GraphicOutput();//		-En la función main() se van llamando sucesivamente a las distintas funciones de
//		 inicialización y control de las librerias GLUT/GLX/OPENGL. Aquellas que no sea común
//		 alterar su comportamiento se encuentran recogidas en el archivo glutcontrol.c; las 
//		 funciones que habitualmente han de editarse, pues regulan la interacción con el 
//		 sujeto durante el experimento, son las siguientes
			glutSwapBuffers();
			usleep(2000000);
			exit(0);		
		break;
		
		default:
			exit(0);
		break;
	}
	glutTimerFunc(TimeLeft(), ExperimentFSA, g_counter);

}

//------------------------------------------------------------  TimeLeft()
//
int TimeLeft(void)
{
	int now = glutGet(GLUT_ELAPSED_TIME);
	
    if(next_time <= now)
	{
		next_time = now + TICK_INTERVAL;
        return 0;
	}
    else    return(next_time - now);
}


//------------------------------------------------------------  GraphicOutput()
//
void GraphicOutput() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch(g_state)
	{
		case EXP_STATE_PRE:
		case EXP_STATE_SEGUIMIENTO1:
		case EXP_STATE_SEGUIMIENTO2:
		case EXP_STATE_RESPUESTA:
			
			DrawCircle(g_xpos,g_ypos);
		
		break;
		
		case EXP_STATE_FLASH:
			
			DrawCircle(g_xpos,g_ypos);
			DrawCircle(FLASH_X,FLASH_Y);
		
		break;
		
		case EXP_STATE_ERROR:
			
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		break;
	}
}


//------------------------------------------------------------  CheckError()
//
int CheckError() {
	int x = (int)(gAbsState[WACOMFIELD_POSITION_X].nValue * X_FACTOR);
	if( (x >= g_xpos-ERR_RADIUS) && (x <= g_xpos+ERR_RADIUS) && (gAbsState[WACOMFIELD_PRESSURE].nValue > 0) )
		return FALSE;
	else
		return TRUE;
	
		
}

//------------------------------------------------------------  OnKeyboad()
//
void OnKeyboard(unsigned char key, int x, int y){

	switch (key) { case 27: exit(0); break; }
}

//------------------------------------------------------------  GrabarDatos()
//
void GrabarDatos() {
	fprintf(archivo, "\t %d \t%d \t%d \n",data.x,data.y,glutGet(GLUT_ELAPSED_TIME) - g_init_time);
}

//------------------------------------------------------------  main()
//
int main(int argc, char **argv)
{
	// initialise glut
    glutInit(&argc,argv);

    // request a depth buffer, RGBA display mode, and we want double buffering
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE);

    // set the initial window size
    glutInitWindowSize(X_RES,Y_RES);

    // create the window
    window = glutCreateWindow("Inhibition of Return");
        
    // if we would want fullscreen:
    glutFullScreen();
		//glutGameModeString(GAMEMODESTRING);
		//window = glutEnterGameMode();
	
    // set the function to use to draw our scene
    glutDisplayFunc(OnDraw);
	
    // set the function to handle changes in screen size
    glutReshapeFunc(OnReshape);
		
	// set the function to handle events on keyboard
	glutKeyboardFunc(OnKeyboard);

    // set the function to be called when we exit
    atexit(OnExit);
    
    // run our custom initialisation
    OnInit();
    
   // this function runs a while loop to keep the program running.    
    glutMainLoop();
    
	exit(0);
	    
}

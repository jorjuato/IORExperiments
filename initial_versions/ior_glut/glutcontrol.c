//////////////////////////////////////////////////////////////////
//  glutcontrol.c				
//							
// Archivo que contiene las funciones de inicialización y control
// básicas de las librerias GLUT/GLX/OPENGL. Estas funciones determinan
// el tipo de acceso a los recursos gráficos que tendrá nuestra aplicación.  
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

#include "glutcontrol.h"
extern int g_counter;

//------------------------------------------------------------  OnDraw()
//
void OnDraw() {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_MODELVIEW_MATRIX );
	glLoadIdentity();
	GraphicOutput();
 	glutSwapBuffers();
	
}

//------------------------------------------------------------  OnReshape()
//
void OnReshape(int w, int h) {   
    
 	if (!h)
		return;
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	GraphicOutput();
	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
 	glutSwapBuffers();
		
}

//------------------------------------------------------------  OnInit()
//
void OnInit() {
    glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetColor(7);
	gluOrtho2D(0,X_RES, 0, Y_RES);
	archivo = fopen("datos_flash","w");
	WacomInit(WACOM_SCANMODE_NOCALLBACK, NULL);

    // set the function to handle timer event
	next_time = glutGet(GLUT_ELAPSED_TIME) + TICK_INTERVAL;
	glutTimerFunc(TimeLeft(), ExperimentFSA, g_counter);	 
}

//------------------------------------------------------------  OnExit()
//
void OnExit() {
	fclose(archivo);
	WacomClose();
}




//////////////////////////////////////////////////////////////////
//  glutcontrol.c				
//							
// Archivo que contiene las funciones de inicializaci�n y control
// b�sicas de las librerias GLUT/GLX/OPENGL. Estas funciones determinan
// el tipo de acceso a los recursos gr�ficos que tendr� nuestra aplicaci�n.  
//  
// Copyleft (L)		Febrero 2008		Jorge Ib��ez  						
//
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//
//		FUNCIONAMIENTO GENERAL DE UN EXPERIMENTO PROGRAMADO CON GLUT
//
//	En la funci�n main() se van llamando sucesivamente a las distintas funciones de
//	inicializaci�n y control de las librerias GLUT/GLX/OPENGL. Aquellas que no sea com�n
//	alterar su comportamiento se encuentran recogidas en el archivo "glutcontrol.c"; las 
//	funciones que habitualmente han de editarse, pues regulan la interacci�n con el 
//	sujeto durante el experimento, son las siguientes:
//		-ExperimentFSA(): Aut�mata de estados finitos que lee una variable
//		 de estado global "g_state" y en funci�n de su valor dirige el 
//		 flujo del experimentos (recogida de eventos,interacci�n con el usuario,
//		 salida gr�fica y grabaci�n de los datos). Esta funci�n es llamada periodicamente,
//		 aunque puede emplearse como retrollamada del thread de recogida de
//		 datos wacom, con lo determinar�a un comportamiento as�ncrono. Es una buena
//		 pr�ctica tener asignada s�lo un tipo de retrollamada para la funcion 
//		 ExperimentFSA(), pues de otra forma resultar�a inseguro distinguir que modo 
//		 a disparado la funci�n y c�mo debe comportarse el programa.
//		-GraphicOutput(): Programado tambi�n bajo un paradigma FSA, en funci�n
//		 del estado del experimento, la salida gr�fica es distinta. Para esto,
//		 la funci�n lee igualmente el valor de "g_state" y decide a que funciones de
//		 graficado es necesario llamar y con que argumentos. Estas funciones se encuentran
//		 en el archivo "drawingfunctions.c"
//		-OnKeyboard(): Funci�n manejadora de los eventos de teclado. Su argumento es el
//		 valor ASCII de la tecla pulsada. Tambi�n se pueden instalar otros manejadores
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




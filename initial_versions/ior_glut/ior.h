//////////////////////////////////////////////////////////////////
//  ior.h				
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

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h> 
#include <math.h>
#include <unistd.h>
#include "wacom.h"
#include "glutcontrol.h"

//Definiciones de valores de la configuracion de la tableta
//#define X_RES		1600.00
//#define Y_RES		1200.00
#define X_RES		1280.00
#define Y_RES		1200.00
#define X_AXE_RANG	10208.00
#define Y_AXE_RANG	7424.00

//#define X_AXE_RANG	87200.00
//#define Y_AXE_RANG	65600.00
#define X_FACTOR	( (X_RES) / (X_AXE_RANG) )
#define Y_FACTOR	( (Y_RES) / (Y_AXE_RANG) )
#define PRESS_FACTOR 512
//#define PRESS_FACTOR 1024
#define GAMEMODESTRING "1600x1200:32@60" 


#define TRUE	1 
#define FALSE	0
#define TICK_INTERVAL				40		// Sampling time in miliseconds

typedef enum
{
	EXP_STATE_PRE,
	EXP_STATE_SEGUIMIENTO1,
	EXP_STATE_FLASH,
	EXP_STATE_SEGUIMIENTO2,
	EXP_STATE_RESPUESTA,
	EXP_STATE_ERROR,
	EXP_STATE_MAX
} EXP_STATE;

struct RESULTADOS
{
	int x;
	int y;
	int errors;
};
////////////////////////////////////////// Prototype definitions
//
z
void OnKeyboard(unsigned char key, int x, int y);
void GraphicOutput();
void ExperimentFSA(int value);
int CheckError(void);
void GrabarDatos(void);
int TimeLeft(void);


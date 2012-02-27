//////////////////////////////////////////////////////////////////
//  drawingfunctions.c				
//							
// Archivo con las rutinas para el graficado de primitivas, figuras y texturas.
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

#include "drawingfunctions.h"

//--------------------------------------------------------------
//  Simple list of colors:
//--------------------------------------------------------------
static GLfloat basic_colors[]= {
   0.0, 0.0, 0.0 ,    1.0, 0.0, 0.0 ,     0.0, 1.0, 0.0 , 
   0.0, 0.0, 1.0 ,    1.0, 1.0, 0.0 ,     0.0, 1.0, 1.0 , 
   1.0, 0.0, 1.0 ,    1.0, 1.0, 1.0 };
//______________________________________________________________
//			0	 1		2	 3		4		5		6		7
//       BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE
//--------------------------------------------------------------




//------------------------------------------------------------  DrawCircle()
//
void DrawCircle(int x_center, int y_center) {
	int i;
	float th,x,y;
	
	glBegin(GL_LINE_STRIP);
    	for(i=0; i<360; i++)
    	{
      		th = M_PI * i / 180.0;
			x = RADIUS * cos(th) + x_center;
			y = RADIUS * sin(th) + y_center;
			glVertex2f(x, y);
   		}
    glEnd();
	
}

//------------------------------------------------------------  SetColor()
//
void SetColor(int i) {
  glColor3fv(basic_colors+((i%8)*3));
}

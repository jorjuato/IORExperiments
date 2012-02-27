//////////////////////////////////////////////////////////////////
//  sdlgl.h				
//							
// Cabeceras con definiciones para el acceso a las funciones gráficas
// 					de las librerias SDL y OpenGL
//
//  
// Copyleft (L)		Noviembre 2007		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////


//Cabeceras de las librerias standar de C para io básica y llamadas al sistema
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>     /* standard unix functions  */
#include <math.h>
// main SDL-OpenGL headers
#include "SDL.h" 
#include "SDL_opengl.h" 




// Definiciones de valores de la configuracion física de la tableta
#define X_RES		1600.00
#define Y_RES		1200.00
#define WIDTH		X_RES
#define HEIGHT		Y_RES
#define X_AXE_RANG	87200.00
#define Y_AXE_RANG	65600.00
#define PRESS_FACTOR 1024
#define X_FACTOR	( (X_RES) / (X_AXE_RANG) )
#define Y_FACTOR	( (Y_RES) / (Y_AXE_RANG) )
#define ASPECT_RATIO (WIDTH / HEIGHT )
#define GAMEMODESTRING "1600x1200:24@60" 

#define true 1
#define false 0 
#define TRUE	true 
#define FALSE	false
#define APPERROR	TRUE
#define APPSUCCESS	FALSE
#define ERROR		FALSE
#define SUCCESS 	TRUE

#define COLORKEY 0, 0, 0 //The Transparent colour



///////////////////////////////////////////////////		Basic Initializing and Drawing SDL/GL API

int setup_opengl();

SDL_Surface* setup_sdlgl();

SDL_Surface* setup_sdl(); 

void OnExit();

SDL_Surface* LoadImage(char *file);

void DrawImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh, SDL_Surface *dstimg, int dx, int dy, int alpha);

void EnableTransparency();

GLuint LoadTexture(char *filename);

void DrawTexture(GLuint textureid, int x, int y);

void SetColor(int);		/* simple color selection */

void DrawCircle(int x_center, int y_center);

///////////////////////////////////////////////////		Logging API

int InitErrorLog(char* logfile);

void CloseErrorLog(void);

int Log(char *szFormat, ...);

FILE* ErrorLog;

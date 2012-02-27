//////////////////////////////////////////////////////////////////
//  drawing_functions.h
//
// Cabeceras del API definido en drawing_functions.c:
// Pequeña libreria que compendia varias funciones relacionadas 
// con pixels, superficies, imagenes y texturas.
//							
//
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////

//Cabeceras de las librerias standar de C para io básica y llamadas al sistema
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>     /* standard unix functions  */
#include <math.h>
// main SDL-OpenGL headers
#include "SDL/SDL.h" 
#include "SDL/SDL_opengl.h" 

#define true 1
#define false 0 
#define TRUE	true 
#define FALSE	false
#define APPERROR	TRUE
#define APPSUCCESS	FALSE
#define ERROR		FALSE
#define SUCCESS 	TRUE

#define COLORKEY 0, 0, 0 //The Transparent colour

//--------------------------------------------------------------//
//  Simple list of SDL RBG Uint32 colors:						//
//--------------------------------------------------------------//

#define ColorRGB(X,Y,Z) (Uint32)(65536 * X + 256 * Y + Z)

#define RGB_Black		ColorRGB(0  , 0  , 0  )
#define RGB_Red			ColorRGB(255, 0  , 0  )
#define RGB_Green		ColorRGB(0  , 255, 0  )
#define RGB_Blue		ColorRGB(0  , 0  , 255)
#define RGB_Cyan		ColorRGB(0  , 255, 255)
#define RGB_Magenta		ColorRGB(255, 0  , 255)
#define RGB_Yellow		ColorRGB(255, 255, 0  )
#define RGB_White		ColorRGB(255, 255, 255)

#define RGB_Maroon		ColorRGB(128, 0  , 0  )
#define RGB_Darkgreen	ColorRGB(0  , 128, 0  )
#define RGB_Navy		ColorRGB(0  , 0  , 128)
#define RGB_Teal		ColorRGB(0  , 128, 128)
#define RGB_Purple		ColorRGB(128, 0  , 128)
#define RGB_Olive		ColorRGB(128, 128, 0  )
#define RGB_Gray		ColorRGB(128, 128, 128)
#define RGB_Grey		ColorRGB(192, 192, 192)

//--------------------------------------------------------------//
//  Simple list of OpenGL float colors:							//
//--------------------------------------------------------------//
static GLfloat basic_colors[]= {								//
   0.0, 0.0, 0.0 ,    1.0, 0.0, 0.0 ,     0.0, 1.0, 0.0 ,		// 
   0.0, 0.0, 1.0 ,    1.0, 1.0, 0.0 ,     0.0, 1.0, 1.0 , 		//
   1.0, 0.0, 1.0 ,    1.0, 1.0, 1.0 };							//
//______________________________________________________________//
//			0	 1		2	 3		4		5		6		7	//
//       BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE	//
//--------------------------------------------------------------//


void SetColor(int);		/* simple color selection */

//Uint32 ColorRGB(Uint8 red, Uint8 green, Uint8 blue );

Uint32 ColorRGBFormat(SDL_PixelFormat *fmt,Uint8 red, Uint8 green, Uint8 blue );

void PutPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

Uint32 GetPixel(SDL_Surface *surface, int x, int y);



void DrawImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh, SDL_Surface *dstimg, int dx, int dy, int alpha);

void EnableTransparency();

GLuint LoadTexture(char *filename);

void DrawTexture(GLuint textureid, int x, int y);



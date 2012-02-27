///////////////////////////////////////////////////////////////////////////
// (0,0)														(0,WIDTH)//
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
//					SDL COORDINATE REFERENCE SYSTEM						 //
//								( x , y )								 //
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
// (HEIGHT,0)										       (HEIGHT,WIDTH)//
///////////////////////////////////////////////////////////////////////////


// main SDL-OpenGL headers
#ifndef __INCLUDESDL
#include <SDL/SDL.h> 
#include <SDL/SDL_opengl.h> 
#endif

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
//  Simple list of SDL RBGA Uint32 colors (con transparencias):	//
//--------------------------------------------------------------//

#define ColorRGBA(X , Y , Z , A) (Uint32)(16777216 * X + 65536 * Y + 256 * Z + A)

#define RGBA_Black		0x000000FF
#define RGBA_Red		0xFF0000FF
#define RGBA_Green		0x00FF00FF
#define RGBA_Blue		0x0000FFFF
#define RGBA_Cyan		0x00FFFFFF
#define RGBA_Magenta	0xFF00FFFF
#define RGBA_Yellow		0xFFFF00FF
#define RGBA_White		0xFFFFFFFF
/*
#define RGBA_Black		ColorRGBA(0  , 0  , 0  , 255)
#define RGBA_Red		ColorRGBA(255, 0  , 0  , 255)
#define RGBA_Green		ColorRGBA(0  , 255, 0  , 255)
#define RGBA_Blue		ColorRGBA(0  , 0  , 255, 255)
#define RGBA_Cyan		ColorRGBA(0  , 255, 255, 255)
#define RGBA_Magenta	ColorRGBA(255, 0  , 255, 255)
#define RGBA_Yellow		ColorRGBA(255, 255, 0  , 255)
#define RGBA_White		ColorRGBA(255, 255, 255, 255)
*/
#define RGBA_Maroon		ColorRGBA(128, 0  , 0  , 255)
#define RGBA_Darkgreen	ColorRGBA(0  , 128, 0  , 255)
#define RGBA_Navy		ColorRGBA(0  , 0  , 128, 255)
#define RGBA_Teal		ColorRGBA(0  , 128, 128, 255)
#define RGBA_Purple		ColorRGBA(128, 0  , 128, 255)
#define RGBA_Olive		ColorRGBA(128, 128, 0  , 255)
#define RGBA_Gray		ColorRGBA(128, 128, 128, 255)
#define RGBA_Grey		ColorRGBA(192, 192, 192, 255)




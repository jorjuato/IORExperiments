//////////////////////////////////////////////////////////////////
//  drawing_functions.c
//
// Pequeña libreria que compendia varias funciones relacionadas 
// con pixels, superficies, imagenes y texturas.
//							
//
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////

//Cabecera principal
#include "drawing_functions.h"

extern SDL_Surface *screen;
extern SDL_Surface *image;

//------------------------------------------------------------------------------//
//																				//
//							 Drawing Stuff										//
//																				//
//------------------------------------------------------------------------------//

//------------------------------------------------------------  SetColor()
//
void SetColor(int i) {
  glColor3fv(basic_colors+((i%8)*3));
}

/* Actualmente, esta funcion es sustituida por una macro
//------------------------------------------------------------  ColorRGB()
//
Uint32 ColorRGB(Uint8 red, Uint8 green, Uint8 blue )
{
	return 65536 * red + 256 * green + blue
}*/

//------------------------------------------------------------  ColorRGBFormated()
//
Uint32 ColorRGBFormat(SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue )
{
	return SDL_MapRGB(fmt,red,green,blue);
}


//------------------------------------------------------------  PutPixel()
//  NOTE: The surface must be locked before calling this!
void PutPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

//------------------------------------------------------------  GetPixel()
//  NOTE: The surface must be locked before calling this!
Uint32 GetPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}



//------------------------------------------------------------  DrawImage()
//
void DrawImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh, SDL_Surface *dstimg, int dx, int dy, int alpha) {
	if ((srcimg == NULL) || (alpha == 0)) return; //If theres no image, or its 100% transparent.
	SDL_Rect src, dst;

	src.x = sx;  src.y = sy;  src.w = sw;  src.h = sh;
	dst.x = dx;  dst.y = dy;  dst.w = src.w;  dst.h = src.h;
	if (alpha != 255) 
		SDL_SetAlpha(srcimg, SDL_SRCALPHA, alpha);
	SDL_BlitSurface(srcimg, &src, dstimg, &dst);
}

//------------------------------------------------------------  EnableTransparency()
//
void EnableTransparency() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//------------------------------------------------------------  LoadTexture()
//
GLuint LoadTexture(char *filename) {

        SDL_Surface *surface;
        GLuint textureid;
        int mode;

        //surface = IMG_Load(filename);
        surface = SDL_LoadBMP(filename);

        // could not load filename
        if (!surface) 
			return ERROR;

        // work out what format to tell glTexImage2D to use...
        if (surface->format->BytesPerPixel == 3)  // RGB 24bit
                mode = GL_RGB;
        else if (surface->format->BytesPerPixel == 4) // RGBA 32bit
                mode = GL_RGBA;
        else {  SDL_FreeSurface(surface); return ERROR;  }

        // create one texture name
        glGenTextures(1, &textureid);

        // tell opengl to use the generated texture name
        glBindTexture(GL_TEXTURE_2D, textureid);

        // this reads from the sdl surface and puts it into an opengl texture
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

        // these affect how this texture is drawn later on...
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        // clean up
        SDL_FreeSurface(surface);

        return textureid;

}

//------------------------------------------------------------  DrawTexture()
//
void DrawTexture(GLuint textureid, int x, int y) {

        // tell opengl to use the generated texture name
        glBindTexture(GL_TEXTURE_2D, textureid);
        glEnable(GL_TEXTURE_2D);

        // make a rectangle
        glBegin(GL_QUADS);

        // top left
        glTexCoord2f(0, 0);
        glVertex2f(x, y);

        // top right
        glTexCoord2f(1, 0);
        glVertex2f(128+x, y);

        // bottom right
        glTexCoord2f(1, 1);
        glVertex2f(128+x, 128+y);

        // bottom left
        glTexCoord2f(0, 1);
        glVertex2f(x, 128+y);

        glEnd();

}


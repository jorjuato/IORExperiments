//////////////////////////////////////////////////////////////////
//  sdlgl_stuff.c			
//							
//
// gcc -Wall  -lpthread -lGL -lGLU -lglut -O3 snake_threaded.c wacusb.c wacserial.c wactablet.c wacomthread.c -o snake
// gcc -Wall  -lpthread sdlglflash.c sdlgl_stuff.c wacusb.c wacserial.c wactablet.c wacomthread.c -o sdlflash `sdl-config --cflags --libs` 
//
// Copyleft (L)		Noviembre 2007		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////


//Cabecera principal
#include "sdlgl.h"
//Cabeceras con definiciones del API Wacom
//#include "wacom.h"

#define APP_NAME	"SDLGL Flash Lag Experiment" 
#define APP_VERSION	"0.0.0.0.0"


//--------------------------------------------------------------//
//  Simple list of colors:										//
//--------------------------------------------------------------//
static GLfloat basic_colors[]= {								//
   0.0, 0.0, 0.0 ,    1.0, 0.0, 0.0 ,     0.0, 1.0, 0.0 ,		// 
   0.0, 0.0, 1.0 ,    1.0, 1.0, 0.0 ,     0.0, 1.0, 1.0 , 		//
   1.0, 0.0, 1.0 ,    1.0, 1.0, 1.0 };							//
//______________________________________________________________//
//			0	 1		2	 3		4		5		6		7	//
//       BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE	//
//--------------------------------------------------------------//
   
   
   
   
//------------------------------------------------------------------------------//
//																				//
//							 Setup Routines										//
//																				//
//------------------------------------------------------------------------------//



//------------------------------------------------------------  setup_opengl()
//
int setup_opengl()
{
    //float aspect = (float)WIDTH / (float)HEIGHT;

    /* Make the viewport cover the whole window */
    glViewport(0, 0, WIDTH, HEIGHT);

    /* Set the camera projection matrix:
     * field of view: 90 degrees
     * near clipping plane at 0.1
     * far clipping plane at 100.0
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
    //gluPerspective(60.0, aspect, 0.1, 100.0);
    /* We're done with the camera, now matrix operations 
     * will affect the modelview matrix
     * */
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    /* set the clear color to gray */
    //glClearColor(0.5, 0.5 ,0.5, 0);
    glClearColor(0, 0 ,0, 0);
    /* We want z-buffer tests enabled*/
    glEnable(GL_DEPTH_TEST);


	//glFlush();
    /* Do draw back-facing polygons*/
   // glDisable(GL_CULL_FACE);
    return(SUCCESS);
}


//------------------------------------------------------------  setup_sdlgl()
//
SDL_Surface* setup_sdlgl() 
{
    const SDL_VideoInfo* video;
	SDL_Surface *screen;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        return(ERROR);
    }

    atexit(OnExit);

    video = SDL_GetVideoInfo( );

    if( !video ) {
        fprintf(stderr,
                "Couldn't get video information: %s\n", SDL_GetError());
        return(ERROR);
    }

    /* Set the minimum requirements for the OpenGL window */
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* Note the SDL_DOUBLEBUF flag is not required to enable double 
     * buffering when setting an OpenGL video mode. 
     * Double buffering is enabled or disabled using the 
     * SDL_GL_DOUBLEBUFFER attribute.
     */
    if( !(screen = SDL_SetVideoMode( WIDTH, HEIGHT, video->vfmt->BitsPerPixel, SDL_OPENGL | SDL_FULLSCREEN )) ) {
        fprintf(stderr, 
                "Couldn't set video mode: %s\n", SDL_GetError());
        return(ERROR);
    }
    return screen;
}

//------------------------------------------------------------  setup_sdl()
//
SDL_Surface* setup_sdl() 
{
    const SDL_VideoInfo* video;
    SDL_Surface *screen;
	
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        return(ERROR);
    }

    atexit(OnExit);

    video = SDL_GetVideoInfo( );

    if( !video ) 
	{
        fprintf(stderr,"Couldn't get video information: %s\n", SDL_GetError());
        return(ERROR);
    }
    if( (screen = SDL_SetVideoMode( WIDTH, HEIGHT, video->vfmt->BitsPerPixel, SDL_DOUBLEBUF | SDL_FULLSCREEN )) == NULL ) 
	{
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        return(ERROR);
    }
    return screen;

}
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

//------------------------------------------------------------  LoadImage()
//
SDL_Surface* LoadImage(char *file) {
	SDL_Surface *tmp;
	tmp = SDL_LoadBMP(file);
 
	if (tmp == NULL) 
	{
		fprintf(stderr, "Error: '%s' could not be opened: %s\n", file, SDL_GetError());
	} 
	else 
	{
		if(SDL_SetColorKey(tmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tmp->format, COLORKEY)) == -1)
		fprintf(stderr, "Warning: colorkey will not be used, reason: %s\n", SDL_GetError());
		
	}
	return SDL_DisplayFormat(tmp);
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


//------------------------------------------------------------------------------//
//																				//
//							 Error Log System									//
//																				//
//------------------------------------------------------------------------------//


//------------------------------------------------------------  InitErrorLog()
//
int InitErrorLog(char* logfile)								// Initializes Error Logging
{
	if(!(ErrorLog = fopen(logfile, "w")))			// If We Can't Open LOG_FILE For Writing
	{
		perror("Can't init Logfile!\n" );			// Report With perror() (Standard + Explains Cause Of The Error) 
		return(ERROR);									// And Exit, This Is Critical, We Want Logging
	}

	Log("%s V%s -- Log Init...\n\n", 
		APP_NAME, APP_VERSION);						// We Print The Name Of The App In The Log

	return TRUE;									// Otherwhise Return TRUE (Everything Went OK)
}


//------------------------------------------------------------  CloseErrorLog()
//
void CloseErrorLog(void)							// Closes Error Logging
{
	Log("\n-- Closing Log...\n");					// Print The End Mark

	if(ErrorLog)									// If The File Is Open
	{
		fclose(ErrorLog);							// Close It
	}

	return;											// And Return, Quite Plain Huh? :)
}


//------------------------------------------------------------  Log()
//
int Log(char *szFormat, ...)						// Add A Line To The Log
{
	va_list Arg;									// We're Using The Same As The printf() Family, A va_list
													// To Substitute The Tokens Like %s With Their Value In The Output

	va_start(Arg,szFormat);							// We Start The List

	if(ErrorLog)									// If The Log Is Open
	{
		vfprintf(ErrorLog, szFormat, Arg);			// We Use vprintf To Perform Substituctions
		fflush(ErrorLog);							// And Ensure The Line Is Written, The Log Must Be Quick
	}

	va_end(Arg);									// We End The List

	return 0;										// And Return A Ok
}

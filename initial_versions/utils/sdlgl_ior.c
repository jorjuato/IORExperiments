//////////////////////////////////////////////////////////////////
//  sdlglflash.c			
//							
//
//
// Copyleft (L)		Noviembre 2007		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////

#define Experiment

//Cabeceras con definiciones del API Wacom
#include "wacom.h"
//Cabecera principal
#include "sdlgl.h"
#include "drawing_functions.h"
//Cabeceras con definiciones para el experimento Flash Lag
#include "ior.h"


////////////////////////////////////////////////////   SDL-GL GLOBALS	
static Uint32 next_time=0,last_time=0,init_time=0;
SDL_Surface *screen = NULL;
GLuint ball = 0;
char *imgfile="/home/jorge/glutlinuxinput/pelota.bmp";
char *logfile="ior.log";
char *datafile="data.raw";	   
////////////////////////////////////////////////////   FLASH LAG GLOBALS
GLfloat g_xpos = INIT_X;
GLfloat g_ypos = INIT_Y;
int g_state = EXP_STATE_PRE;
int g_init_time = 0;
FILE* data = NULL;
int flag = FALSE;


//------------------------------------------------------------  time_left()
//
int time_left(void)
{
	int now = SDL_GetTicks();
	
    if(next_time <= now)
	{
		next_time = now + TICK_INTERVAL;
        return 0;
	}
    else    return(next_time - now);
}

//------------------------------------------------------------  update()
//
static void update()
{
  	GLfloat time_inc = (GLfloat)(next_time - last_time) / 1000;

	
  	switch(g_state)
	{
		GrabarDatos();
		case EXP_STATE_PRE:						
			if (gAbsState[WACOMFIELD_PRESSURE].nValue > 0) {
				g_state=EXP_STATE_SEGUIMIENTO1;
				g_init_time = SDL_GetTicks();
			}				
		break;
		
		case EXP_STATE_SEGUIMIENTO1:
			g_xpos += (GLfloat)SPEED * time_inc;
			if(CheckError()) {
				g_state = EXP_STATE_ERROR;
				return;
			}				
			else if (SDL_GetTicks() - g_init_time >= FLASH_INIT_TIME) {
				g_state = EXP_STATE_FLASH;
			}
			else {
				GraphicOutput();
				SDL_GL_SwapBuffers();
			}
		break;
		
		case EXP_STATE_FLASH:
			g_xpos += (GLfloat)SPEED * time_inc;
			if(CheckError()) {
				g_state = EXP_STATE_ERROR;
				return;
			}
			else if (SDL_GetTicks() - g_init_time >= FLASH_END_TIME) {
				g_state = EXP_STATE_SEGUIMIENTO2;
				GraphicOutput();
				SDL_GL_SwapBuffers();
			}
			else {
				GraphicOutput();
				SDL_GL_SwapBuffers();
			}
		break;
			
		case EXP_STATE_SEGUIMIENTO2:
			g_xpos += (GLfloat)SPEED * time_inc;	
			if(CheckError()) {
				g_state = EXP_STATE_ERROR;
				return;
			}
			else if (SDL_GetTicks() - g_init_time >= TOTAL_END_TIME)	{
				g_state = EXP_STATE_RESPUESTA;
			}
			else {
				GraphicOutput();
				SDL_GL_SwapBuffers();
			}			
		break;
		
		case EXP_STATE_RESPUESTA:			
			if (gAbsState[WACOMFIELD_PRESSURE].nValue == 0)
				flag = TRUE;
			if (flag && (gAbsState[WACOMFIELD_PRESSURE].nValue > 0) ) {
				GrabarDatos();
				exit(APPSUCCESS);
			}
		break;
		
		case EXP_STATE_ERROR:			
			GraphicOutput();
			SDL_GL_SwapBuffers();
			usleep(2000000);
			exit(APPERROR);		
		break;
		
		default:
			exit(APPERROR);
		break;
	}
	last_time = next_time;

}


//------------------------------------------------------------  GrabarDatos()
//
void GrabarDatos() {
	float x,y;

	x=(float)gAbsState[WACOMFIELD_POSITION_X].nValue * X_FACTOR;
	y=(float)gAbsState[WACOMFIELD_POSITION_Y].nValue * Y_FACTOR;
	
	fprintf(data, "\t %f \t%f \t%d \n",x,y,last_time);
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


//------------------------------------------------------------  DrawCircle()
//
void DrawCircle(int x_center, int y_center) {
	DrawTexture(ball, x_center, y_center);
	
}
//------------------------------------------------------------  CheckError()
//
int CheckError() {
	int x = (int)(gAbsState[WACOMFIELD_POSITION_X].nValue * X_FACTOR);
	if( (x >= g_xpos-ERR_RADIUS) && (x <= g_xpos+ERR_RADIUS) && (gAbsState[WACOMFIELD_PRESSURE].nValue > 0) )
	//if( (x < g_xpos-ERR_RADIUS) || (x > g_xpos+ERR_RADIUS) )		
		return FALSE;
	else
		return TRUE;
}
//------------------------------------------------------------  main_loop()
//
static void main_loop() 
{
    SDL_Event event;
    init_time = SDL_GetTicks();
    next_time = init_time + TICK_INTERVAL;
    last_time = next_time;
    GraphicOutput();
	SDL_GL_SwapBuffers();
	
    while(1) 
    {
       	SDL_Delay(time_left());
        update();        
        while( SDL_PollEvent( &event ) ) 
        {

            switch( event.type ) 
            {
            	case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
            	break;
           		
           		case SDL_QUIT:
        	       exit (APPSUCCESS);
        	       
        	    default:
        	    break;
			}
		}  
    }
}

//------------------------------------------------------------  OnDraw()
//
void OnDraw() {
}

//------------------------------------------------------------  OnInit()
//
void OnInit() {

	WacomInit(WACOM_SCANMODE_NOCALLBACK, NULL);
	
	if ( !(data = fopen(datafile, "w")))
	{
		perror("Couldn't open file");
		exit(APPERROR);			
	}	
	if ( !(InitErrorLog(logfile)))
	{
		perror("Couldn't open log file");
		exit(APPERROR);			
	}	
	if (!setup_sdlgl())
	{
		perror("Couldn't initialize video");
		exit(APPERROR);
	}
	if (!setup_opengl())
	{
		perror("Couldn't initialize video");
		exit(APPERROR);
	}
	if (!(ball = LoadTexture(imgfile)))
	{
		perror("Couldn't load texture");
		exit(APPERROR);
	}
}

//------------------------------------------------------------  OnExit()
//
void OnExit() {
	
	fclose(data);
   	WacomClose();
	CloseErrorLog();
	SDL_Quit();
    exit(APPSUCCESS);
}


//------------------------------------------------------------  main()
//
int main(int argc, char **argv)
{	
	OnInit();
	main_loop(); 
	OnExit();
	return(APPSUCCESS);
}

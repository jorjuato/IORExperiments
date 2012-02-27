//////////////////////////////////////////////////////////////////
//  sdlglsnake.c			
//							
//
// Copyleft (L)		Noviembre 2007		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////


//Cabecera principal
#include "sdlgl.h"
//Cabeceras con definiciones del API Wacom
#include "wacom.h"

#define MAXPUNTOS	3
#define TICK_INTERVAL 10

////////////////////////////////////////////////////   SDL-GL GLOBALS	
SDL_Surface *screen; 
FILE* archivo;
static Uint32 next_time,last_time,init_time;					   




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
   	int i;
   	
   	static int contador=0;
	static int g_bufferx[MAXPUNTOS];
	static int g_buffery[MAXPUNTOS];
	
	if (gAbsState[WACOMFIELD_PRESSURE].nValue == 0) 
	{
		contador=0;
		return;
	}
	if (contador<MAXPUNTOS-1) 
	{ 	
		for (i=1; i<contador-1; i++)
		{	
			g_bufferx[i-1]=g_bufferx[i]; 
			g_buffery[i-1]=g_buffery[i]; 
		}
		g_bufferx[contador]=gAbsState[WACOMFIELD_POSITION_X].nValue * X_FACTOR; 
		g_buffery[contador]=gAbsState[WACOMFIELD_POSITION_Y].nValue * Y_FACTOR;
		contador++;
		return;
	}
	for (i=1; i<MAXPUNTOS; i++)
	{	
		g_bufferx[i-1]=g_bufferx[i]; 
		g_buffery[i-1]=g_buffery[i]; 
	}
	
	g_bufferx[contador]=gAbsState[WACOMFIELD_POSITION_X].nValue * X_FACTOR; 
	g_buffery[contador]=gAbsState[WACOMFIELD_POSITION_Y].nValue * Y_FACTOR;
	
	fprintf(archivo,"%d \t %d  \t %d \t %d \t %d \t %d \n", g_bufferx[contador],
															g_buffery[contador],
															gAbsState[WACOMFIELD_POSITION_X].nValue,
															gAbsState[WACOMFIELD_POSITION_Y].nValue,
															gAbsState[WACOMFIELD_PRESSURE].nValue,
															SDL_GetTicks());
	

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_MODELVIEW_MATRIX );
	glLoadIdentity();		
	//glColor3f((double)gAbsState[WACOMFIELD_PRESSURE].nValue/1024, (double)gAbsState[WACOMFIELD_PRESSURE].nValue/1024, 1);  
	SetColor(3);
	glLineWidth(5);
 	glBegin(GL_LINES);
 		for (i=0; i<MAXPUNTOS-1; i++)
 	 		glVertex2i(g_bufferx[i], g_buffery[i]);
	glEnd();
	
	SetColor(5);
	glRecti(500, 0, 700, 100);
	glRecti(500, 768, 700, 668);
	glRecti(0, 250, 300, 550);
	SDL_GL_SwapBuffers();

}
//------------------------------------------------------------  main_loop()
//
static void main_loop() 
{
    SDL_Event event;

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
        	    break;
        	}            
		}
	}
}


//------------------------------------------------------------  main()
//
int main(int argc, char **argv)
{	
	SDL_Surface *tux;
	char *imgfile="/home/jorge/glutlinuxinput/pelota.bmp";
	char *logfile="flash.log";
	char *datafile="data.raw";

	
	WacomInit(WACOM_SCANMODE_NOCALLBACK, NULL);	
	
	if ( !(archivo = fopen(datafile, "w")))
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

	main_loop(); 
	
    fclose(archivo);
   	WacomClose();
	CloseErrorLog();
    exit(APPSUCCESS);
}

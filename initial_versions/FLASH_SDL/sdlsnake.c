//////////////////////////////////////////////////////////////////
//  sdlglsnake.c			
//							
//
// Copyleft (L)		Noviembre 2007		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////


//Cabecera principal
#include "sdlgl.h"
#include "SDL_gfxPrimitives.h"
//Cabeceras con definiciones del API Wacom
#include "wacom.h"

#define MAXPUNTOS	10
#define TICK_INTERVAL 30

////////////////////////////////////////////////////   SDL-GL GLOBALS	
SDL_Surface *screen; 
FILE* data;
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
	
	fprintf(data,"%d \t %d  \t %d \t %d \t %d \t %d \n", g_bufferx[contador],
															g_buffery[contador],
															gAbsState[WACOMFIELD_POSITION_X].nValue,
															gAbsState[WACOMFIELD_POSITION_Y].nValue,
															gAbsState[WACOMFIELD_PRESSURE].nValue,
															SDL_GetTicks());
	

	//SDL_FillRect(screen, NULL, 0);			
	for (i=0; i<MAXPUNTOS-2; i++)
 	 	lineColor(screen, (Sint16)g_bufferx[i], (Sint16)g_buffery[i],(Sint16)g_bufferx[i+1], (Sint16)g_buffery[i+1], 5000);
	SDL_Flip(screen);


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


//------------------------------------------------------------  OnDraw()
//
void OnDraw() {
}

//------------------------------------------------------------  OnInit()
//
void OnInit() {

	char *logfile="flash.log";
	char *datafile="data.raw";
	
	WacomInit();
	
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
	if (!(screen = setup_sdl()) )
	{
		perror("Couldn't initialize video");
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
	
    exit(APPSUCCESS);
}

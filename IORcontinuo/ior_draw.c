//////////////////////////////////////////////////////////////////
//  sdl_ior.c			
//							
//
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////

//Cabeceras con definiciones del API Wacom
//#include "wacom.h"

//Cabecera principal
#include "SDL/SDL.h" 
#include "SDL/SDL_opengl.h" 
#include "SDL/SDL_framerate.h"
#include "SDL/SDL_gfxPrimitives.h"
//#include "SDL/SDL_gfxBlitFunc.h"
#define __INCLUDESDL
//Cabeceras con definiciones para el experimento Flash Lag
#include "display.h"
#include "colors.h"
#include "ior.h"
#include "ior_draw.h"


//////////////////////////////////////////////////// MAIN GLOBALS
extern SDL_Surface *screen;					// Puntero a la pantalla completa. Reside en sdlgl_control.c
extern SDL_Surface *target;					// Puntero a la imagen del target
extern struct TRIAL Resultados[DIMENSION];	// Matriz que contiene los resultados {type,ctoa,ctd y rt} en TRIALS

//////////////////////////////////////////////////// IOR GLOBAL STATE VARIABLES
extern char* g_trial_type;							// Actual type of trial, value from enum TRIAL_TYPE
extern Uint8 g_trial_number;						// Index of the actual number of trial in matrix Resultados


//------------------------------------------------------------  UpdateScreen()
//
void UpdateScreen()
{
	SDL_Flip(screen);
}	
	
//------------------------------------------------------------  ShowFixation()
//
 void ShowFixation()
{
	//-TODO- Sustituir este metodo por uno basado en pintar rectángulos
	// de ancho configurable por una constante en ior.h

	hlineColor(screen,  (int)(FIXATION_X - FIXATION_WIDTH / 2), \
			   			(int)(FIXATION_X + FIXATION_WIDTH / 2), \
			   			FIXATION_Y,  RGBA_White);
	vlineColor(screen,  FIXATION_X,
			   			(int)(FIXATION_Y - FIXATION_HEIGHT / 2), \
			   			(int)(FIXATION_Y + FIXATION_HEIGHT / 2), \
			   			 RGBA_White);
}


//------------------------------------------------------------  ShowCue()
//
 void ShowCue()	
{
	static SDL_Rect cue_extrect, cue_intrect;
	
	//Primero, preparamos los rectangulos donde pintaremos el cue:
	//uno exterior de blanco y otro interior del color de fondo, 
	//con un ancho que varia con el tiempo -TODO-
	if (g_trial_type == "LL" || g_trial_type == "LR" )
	{	
		cue_extrect.x = (int) (CUE_LEFT_X - CUE_EXT_SIZE / 2);
		cue_extrect.y = (int) (CUE_Y - CUE_EXT_SIZE / 2);
		cue_extrect.w = CUE_EXT_SIZE;
		cue_extrect.h = CUE_EXT_SIZE;
		
		cue_intrect.x = (int) (CUE_LEFT_X - CUE_INT_SIZE / 2);
		cue_intrect.y = (int) (CUE_Y - CUE_INT_SIZE / 2);
		cue_intrect.w = CUE_INT_SIZE;
		cue_intrect.h = CUE_INT_SIZE;
	}
	else
	{	
		cue_extrect.x = (int) (CUE_RIGHT_X - CUE_EXT_SIZE / 2);
		cue_extrect.y = (int) (CUE_Y - CUE_EXT_SIZE / 2);
		cue_extrect.w = CUE_EXT_SIZE;
		cue_extrect.h = CUE_EXT_SIZE;
		
		cue_intrect.x = (int) (CUE_RIGHT_X - CUE_INT_SIZE / 2);
		cue_intrect.y = (int) (CUE_Y - CUE_INT_SIZE / 2);
		cue_intrect.w = CUE_INT_SIZE;
		cue_intrect.h = CUE_INT_SIZE;
	}
	//Ahora lo presentamos en pantalla
	SDL_FillRect(screen, &cue_extrect, RGB_White);
	SDL_FillRect(screen, &cue_intrect, RGB_Black);
}




//------------------------------------------------------------  ShowTarget()
//
 void ShowTarget()
{
	SDL_Rect src, dst;	

	//Primero, preparamos los rectangulos donde pintaremos el target:
	src.x = 0;  src.y = 0;  src.w = target->w;  src.h = target->h;
	
	if (g_trial_type == "LL" || g_trial_type == "RL")
	{		
		dst.x = (int) (CUE_LEFT_X - src.w / 2) + Resultados[g_trial_number].ctd;
		dst.y = (int) (CUE_Y - src.h / 2);  
		dst.w = src.w; 
		dst.h = src.h;	
	}
	else
	{		
		dst.x = (int) (CUE_RIGHT_X - src.w / 2) + Resultados[g_trial_number].ctd;
		dst.y = (int) (CUE_Y - src.h / 2);  
		dst.w = src.w; 
		dst.h = src.h;	
	}
	//Ahora lo presentamos en pantalla
	SDL_BlitSurface(target, &src, screen, &dst);
			
}

//------------------------------------------------------------  ShowBackground()
//
 void ShowBackground(Uint32 color)
{
SDL_FillRect(screen, NULL, color);		
}



//------------------------------------------------------------ ShowMesagge()
//
void ShowMessage(){
exit(0);

}


//------------------------------------------------------------  TimeLeft()
//
 int TimeLeft(void)	// En este experimento no se usa porque no es muy util.
{						 	// Es útil en experimentos con objetos animados.	
	static Uint32 now, next_time=0;  
    
	if( next_time <= (now = SDL_GetTicks()) )
	{
		next_time = now + TICK_INTERVAL;
        return 0;
	}
    else    
		return(next_time - now);
}


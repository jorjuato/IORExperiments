//////////////////////////////////////////////////////////////////
//  ior_clasico.c			
//							
//
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////

//Cabeceras con definiciones del API Wacom
//#include "wacom.h"

//Cabeceras de la libreria SDL
#include "SDL/SDL.h"
#define __INCLUDESDL

//Cabeceras estandar del SO
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>     
#include <math.h> 

//Cabecera principal
#include "display.h" 
#include "colors.h"
#include "ior.h"
#include "ior_draw.h"
#include "main.h"
#include "parser.h"

//////////////////////////////////////////////////// SDL GLOBALS
extern SDL_Surface *screen;							// Puntero a la pantalla completa. Se define en sdlgl_control.c
SDL_Surface *target;								// Puntero a la imagen del target
char *imgfile="../misc/ball_white_small.bmp";		// Nombre de archivo de la imagen del target
char data_base[128]="../datos/rawdata/ior_clasico";		// Nombre del archivo donde se guardarán los resultados
const char *subject_name=NULL;


//////////////////////////////////////////////////// IOR GLOBAL STATE VARIABLES
char*  g_trial_type;								// Actual type of trial, value from enum TRIAL_TYPE
Uint8 g_trial_state = TRIAL_STATE_TAKE_A_REST;	// Actual state of trial, value from enum TRIAL_STATE
Uint8 g_trial_number = 0;						// Index of the actual number of trial in matrix Resultados
Uint32 g_state_init_time = 0;					// Absolute (in ms from beggining) actual state's stating time
Uint8 g_bDrawn = FALSE;							// Flag, sets an state as already drawn
Uint8 g_bKeyStroke = FALSE;						// Flag, sets the onset of an keyboard user event
struct TRIAL Resultados[DIMENSION];				// Matriz que contiene los resultados {type,ctoa,ctd y rt} en TRIALS

//------------------------------------------------------------  main()
//
int main(int argc, char **argv)
{	
	if ( !(subject_name = Parser(argc, argv)) ) 		// Parsea la linea de comandos: 	parser.c
		exit (1);			
	
	OnInit();						//Inicializa todo lo inicializable: sdlgl_control.h	
	
	ExperimentSetup(); 				//Configura el experimento
	MainLoop();						//Lanza el experimento propiamente dicho
	ExperimentSave();				//Salva los resultados en un archivo
	
	OnExit();						//Cierra limpiamente todico: sdlgl_control.h
	
	return APPSUCCESS;
}

//------------------------------------------------------------  ExperimentSetup()
//
static void ExperimentSetup() 
{
	if (!(target = LoadImage(imgfile))) //Cargamos la imagen del target
	{
		perror("Couldn't load image");
		exit(APPERROR);
	}
	else
	{
		ExperimentEventMask(); 			//Crea la mascara de eventos 
		ExperimentRandomize();			//Aleatoriza los trials		
		SDL_ShowCursor(FALSE);			//Escondemos el cursor del raton
	}
}


//------------------------------------------------------------  ExperimentEventMask()
//
static void ExperimentEventMask() 
{	
	// Ignorar todos los eventos que no van a usarse
	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
	SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);
	SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
	SDL_EventState(SDL_VIDEORESIZE, SDL_IGNORE);
	SDL_EventState(SDL_USEREVENT, SDL_IGNORE);
	
}


//------------------------------------------------------------  ExperimentRandomize()
//
static int ExperimentRandomize()
{	
	int i,j,k,l;
	int bTrial_numbers[DIMENSION], trial=0;
	float number,prev;
	
	//Inicializamos la semilla del generador de numeros aleatorios
	srand(time(0));
	
	//Inicializamos el vector que contea el orden de los trials
	for(i=0;i<DIMENSION;i++)
	{
		bTrial_numbers[i] = 0;
		printf("Indice:  %d, Trial_numers: %d\n", i, bTrial_numbers[i]);
	}
	
	//Rellenamos la matriz de resultados primero con los TrainTrials
	for(i=0; i < CTOA_MAX; i++)
	{
		//for(j=0; j < CTD_MAX; j++)
		{	
			for(k=0; k < TRIAL_TYPE_MAX; k++)
			{	
				for(l=0; l < TRAIN_REPLICATION; l++)
				{	
					if (trial < TRIAL_TRAIN_NUMBER)
					{
						Resultados[trial].bTraining = TRUE;
						Resultados[trial].ctoa = ctoa_val[i]; 
						Resultados[trial].ctd.value  = 0 ;
						Resultados[trial].ctd.name  = "equal" ;
						Resultados[trial].type = trial_type_name[k] ;
						/* 
						// Esta secuencia condicional nos lateraliza el experimento
						if (trial_type_name[k] == "LL" || trial_type_name[k]== "RR")
						{
							Resultados[trial].ctd.value  = ctd_val[j] ;
							Resultados[trial].ctd.name  = ctd_code[j] ;	
						}
						else
						{
							Resultados[trial].ctd.value  = 0 ;
							Resultados[trial].ctd.name  = "equal" ;
						}
						*/
						while(TRUE)
						{
							//Generamos un num.rnd para el orden del trial
							prev = (float)rand()/(float)(RAND_MAX+1.0);
							number = prev * TRIAL_TRAIN_NUMBER;
							
							//Si el numero esta sin ocupar todavia...
							if (bTrial_numbers[(int)number] == FALSE) 
							{
								Resultados[trial].order = (int)number;
								bTrial_numbers[(int)number] = TRUE;
								trial++;
								break;
							}	
						} 	//END_WHILE
					} 		//END_IF
				}			//END_FORs
			}				//
		}					//	
	}						//END_FUNC
	
	//Rellenamos la matriz de resultados con los trials
	for(i=0;i < CTOA_MAX;i++)
	{
		//for(j=0; j < CTD_MAX; j++)
		{	
			for(k=0; k < TRIAL_TYPE_MAX; k++)
			{	
				for(l=0; l < TRIAL_REPLICATION; l++)
				{
					Resultados[trial].bTraining = FALSE;
					Resultados[trial].ctoa = ctoa_val[i]; 
					Resultados[trial].ctd.value  = 0 ;
					Resultados[trial].ctd.name  = "equal" ;
					Resultados[trial].type = trial_type_name[k] ;
					/*
					if (trial_type_name[k] == "LL" || trial_type_name[k]== "RR")
					{
						Resultados[trial].ctd.value  = ctd_val[j] ;
						Resultados[trial].ctd.name  = ctd_code[j] ;	
					}
					else
					{
						Resultados[trial].ctd.value  = 0 ;
						Resultados[trial].ctd.name  = "equal" ;
					}
					*/
					while(TRUE)
					{
						//Generamos un num.rnd para el orden del trial
						prev = (float)rand()/(float)(RAND_MAX+1.0);
						number = prev * DIMENSION;
						
						//Si el numero esta sin ocupar todavia y no es un entrenamiento...
						if (bTrial_numbers[(int)number] == FALSE && number >= TRIAL_TRAIN_NUMBER)
						{
							Resultados[trial].order = (int)number;
							bTrial_numbers[(int)number] = TRUE;
							trial++;
							break;
						}	
					}						
				}
			}
		}
	}
	
	return TRUE;
}				



//------------------------------------------------------------  MainLoop()
//
static int MainLoop() 
{
    SDL_Event event;	
	int i;
	
	//Buscamos el indice del primer trial
	for(i=0;i<DIMENSION;i++)
	{
		if (Resultados[i].order == 0)
		{
			g_trial_number = i; 
			break;
		}
	}
	
	//Bucle indefinido que lleva a cabo el experimento		
    while(TRUE) 
    {
        //Funcion principal para regular los estados del experimento
        ExperimentTimer();
           
        while( SDL_PollEvent(&event)) 
        {
			switch(g_trial_state)///////////////////////////////////////////switch
			{	
				case TRIAL_STATE_SHOW_TARGET:///////////////////////////////////
					if (event.type == SDL_KEYDOWN) 
					{
						if (event.key.keysym.sym == SDLK_LEFT \
						 || event.key.keysym.sym == SDLK_RIGHT )
						{	
							Resultados[g_trial_number].rt = SDL_GetTicks() - g_state_init_time;   
							Resultados[g_trial_number].keypressed = event.key.keysym.sym;
							g_bKeyStroke = TRUE;
						}
						else if (event.key.keysym.sym == SDLK_ESCAPE)
							EndExperiment();
					}
					else if (event.type == SDL_QUIT) 
						EndExperiment();			
					break;
				case TRIAL_STATE_TAKE_A_REST:///////////////////////////////////
					if (event.type == SDL_KEYDOWN) 
					{							
						if (event.key.keysym.sym == SDLK_ESCAPE)
							EndExperiment();
						else
							g_bKeyStroke = TRUE;
					}
					else if (event.type == SDL_QUIT) 
						EndExperiment();	
					break;				
				default:////////////////////////////////////////////////////////
					switch(event.type) 
					{
						case SDL_KEYDOWN:
							if (event.key.keysym.sym == SDLK_ESCAPE)
								EndExperiment();								
							else if (event.key.keysym.sym == SDLK_LEFT ||\
									 event.key.keysym.sym == SDLK_RIGHT )
							{
								g_trial_state = TRIAL_STATE_TAKE_A_REST;							
								g_bDrawn = FALSE;
							}
						break;
						
						case SDL_QUIT:
						   EndExperiment();
						break;
						
						default:
						break;
					}
				
			}///////////////////////////////////////////////////////////end_switch
			
		}///////////////////////////////////////////////////////////////end_while(event)
		
    }///////////////////////////////////////////////////////////////////end_while(1)
	return FALSE;
}


//------------------------------------------------------------  ExperimentTimer()
//
static int ExperimentTimer()
{
	//Actualizamos los valores de variables temporales
	Uint32 now = SDL_GetTicks(); 	
	Uint32 time_inc = now - g_state_init_time;
	static double ctoa;
	
	//Automata de estados, bifurca el flujo del programa
	//Es de diseño unificado, sencillo y bastante autoexplicativo
	//Solo se comentan los detalles importantes para el experimento
	switch(g_trial_state)
	{
		case TRIAL_STATE_TAKE_A_REST:///////////////////////////////////////////						
			//Si no esta pintado el estado, lo pintamos e inicimos a contar el t.
			if (!g_bDrawn)	
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
				g_state_init_time = now;
			}
			//Comprobamos la condicion de salida del estado.
			//Son eventos o temporales o procedentes de la interaccion
			//del sujeto (teclas pulsadas y demas)
			if(g_bKeyStroke)
			{
				g_trial_state = TRIAL_STATE_INTER_TRIAL;
				g_bDrawn = FALSE;
				g_bKeyStroke = FALSE;
				// Ahora, espera hasta que se pulse alguna 
				// tecla en MainLoop(). No espera a que se 
				// suelte para iniciar el experimento.
			}
			break;
		case TRIAL_STATE_INTER_TRIAL:///////////////////////////////////////////						
			if (!g_bDrawn)
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
				ctoa = Resultados[g_trial_number].ctoa;
				g_state_init_time = now;
			}
			else if (time_inc >= INTER_TRIAL_TIME)
			{
				g_trial_state = TRIAL_STATE_INIT_FIXATION;
				g_bDrawn = FALSE;
			}
			break;
		case TRIAL_STATE_INIT_FIXATION://///////////////////////////////////////
			if (!g_bDrawn)
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
				g_state_init_time = now;
			}
			else if (time_inc < INITIAL_FIXATION_FLASH_TIME)
			{
				ExperimentGraphics(time_inc);
			}
			else
			{
				g_trial_state = TRIAL_STATE_INTER_FIX_CUE;
				g_bDrawn = FALSE;
			}
			break;		
		case TRIAL_STATE_INTER_FIX_CUE://///////////////////////////////////////
			if (!g_bDrawn)
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
				g_state_init_time = now;
			}
			else if (time_inc >= INTER_FIX_CUE_TIME)
			{
				g_trial_state = TRIAL_STATE_SHOW_CUE;
				g_bDrawn = FALSE;
			}
			break;		
		case TRIAL_STATE_SHOW_CUE://////////////////////////////////////////////
			if (!g_bDrawn)
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
				g_state_init_time = now;
			}
			else if (time_inc < CUE_FLASH_TIME)
			{
				ExperimentGraphics(time_inc);
			}
			else
			{
				g_trial_state = TRIAL_STATE_INTER_CUE_FIX;
				g_bDrawn = FALSE;
			}
			break;
		case TRIAL_STATE_INTER_CUE_FIX://///////////////////////////////////////
			if (!g_bDrawn)
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
			}
			else if (time_inc >= INTER_CUE_FIX_TIME + CUE_FLASH_TIME)
			{
				g_trial_state = TRIAL_STATE_RETURN_FIXATION;
				g_bDrawn = FALSE;
			}
			break;		
		case TRIAL_STATE_RETURN_FIXATION:///////////////////////////////////////
			if (!g_bDrawn)
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
			}
			else if (time_inc >= Resultados[g_trial_number].ctoa)
			{
				g_trial_state = TRIAL_STATE_SHOW_TARGET;
				g_bDrawn = FALSE;
			}
			break;	
		case TRIAL_STATE_SHOW_TARGET:///////////////////////////////////////////			
			if(g_bKeyStroke) //Primero comporbamos que no se haya pulsado tecla
			{
				g_bKeyStroke = FALSE;
				g_bDrawn = FALSE;
				
				//Si se terminan los trials, termina el exp.	
				if (!CalcTrialNumber())	
					EndExperiment();
							
				//Comprobamos si ha llegado el descanso
				if((Resultados[g_trial_number].order % 60) == 0 )
					g_trial_state = TRIAL_STATE_TAKE_A_REST;
				else
					g_trial_state = TRIAL_STATE_INTER_TRIAL; 								
			}
			else if (!g_bDrawn) //Despues comprobamos que se haya iniciado el estado
			{
				ExperimentGraphics(0);
				g_bDrawn = TRUE;
				g_state_init_time = now;
			}
			break;//////////////////////////////////////////////////////////////
		default:
			exit(APPERROR);
			break;
	} //end_switch
	return TRUE;
}	//end_function



//------------------------------------------------------------  ExperimentHandler()
//
static int ExperimentHandler(void){
	return FALSE;
}

//------------------------------------------------------------  EndExperiment()
//
static int EndExperiment(void){
	ShowBackground(RGB_Blue);
	UpdateScreen();
	sleep(2);
	ExperimentSave();
	exit (APPSUCCESS);
}
//------------------------------------------------------------  ExperimentGraphics()
//
static void ExperimentGraphics(Uint32 time_inc) {
	switch(g_trial_state)
	{
		case TRIAL_STATE_TAKE_A_REST:///////////////////////////////////////////						
			ShowBackground(RGB_Grey);
			//ShowMessage();			
			break;
					
		case TRIAL_STATE_INTER_TRIAL:///////////////////////////////////////////						
			ShowBackground(RGB_Black);
			//ShowMessage();			
			break;
			
		case TRIAL_STATE_INTER_FIX_CUE:
		case TRIAL_STATE_INTER_CUE_FIX:
			ShowBackground(RGB_Black);
			break;
			
		case TRIAL_STATE_INIT_FIXATION://///////////////////////////////////////
			ShowFixation();				
			break;
			
		case TRIAL_STATE_SHOW_CUE://////////////////////////////////////////////
			ShowCue();
			//ShowFixation();
			break;
				
		case TRIAL_STATE_RETURN_FIXATION:///////////////////////////////////////
			ShowBackground(RGB_Black);	
			ShowFixation();
			break;
			
		case TRIAL_STATE_SHOW_TARGET:///////////////////////////////////////////
			ShowTarget();
			ShowFixation();
			break;
											
		default:
			exit(APPERROR);
			break;
	} 
	UpdateScreen();	
}


//------------------------------------------------------------ CalcTrialNumber()
//
static int CalcTrialNumber(){
	int i;
	
	if (Resultados[g_trial_number].order == DIMENSION - 1)
		return FALSE;
		
	for(i=0;i<DIMENSION;i++)
	{
		if (Resultados[i].order == Resultados[g_trial_number].order + 1)
		{
			g_trial_number = i; 
			g_trial_type = Resultados[g_trial_number].type;
			break;
		}
	}
	return TRUE;
}


/**
	
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C":
	
 */
	
void strreverse(char* begin, char* end) 
{	
	char aux;
	while(end>begin)
		aux=*end, *end--=*begin, *begin++=aux;	
}
	
void itoa(int value, char* str, int base) {
	
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char* wstr=str;
	int sign;
	
	// Validate base
	if (base<2 || base>35){ *wstr='\0'; return; }
		
	// Take care of sign
	if ((sign=value) < 0) value = -value;
		
	// Conversion. Number is reversed.
	do *wstr++ = num[value%base]; while(value/=base);
	if(sign<0) *wstr++='-';
	*wstr='\0';
		
	// Reverse string
	
	strreverse(str,wstr-1);
	
}

//------------------------------------------------------------  ExperimentSave()
//
static void ExperimentSave() {
	int i;
	FILE* data = NULL;
	time_t tim=time(NULL);
	struct tm *now=localtime(&tim);
	char year[5], month[3], day[3], date[16];
	
	itoa(now->tm_year+1900, year ,10);
	itoa(now->tm_mon+1,month,10);
	itoa(now->tm_mday,day,10);
	
	strcpy(date,"_");
	strcat(date,day);
	strcat(date,"_");
	strcat(date,month);
	strcat(date,"_");
	strcat(date,year);
	strcat(date,"_");

	strcat(data_base, date);
	strcat(data_base, subject_name);
	
	if ( !(data = fopen(data_base, "w")))
	{
		perror("Couldn't open file, I'll try again");
		ExperimentSave();
	}
	else
	{
		fprintf(data, "\n\n#! index\t\tTrOrder\t\tTrType\t\t\tCTOA\t\tCTD\t\t\tRT\t\tKeyPressed\n");
		
		for(i=0;i<DIMENSION;i++)
			fprintf(data, "\t%d\t\t\t%d\t\t\t%s\t\t\t%d\t\t\t%s\t\t\t%d\t\t\t\t%d  \n",i 
														,(int)Resultados[i].order
														,Resultados[i].type 
														,(int)Resultados[i].ctoa  
														,Resultados[i].ctd.name 
														,(int)Resultados[i].rt
														,(int)Resultados[i].keypressed);
	}
	if(data)
		fclose(data);
}


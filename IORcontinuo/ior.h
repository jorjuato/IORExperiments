//////////////////////////////////////////////////////////////////
//  ior.h			
//							
//	Cabeceras para definir parámetros del experimento 
//				Inhibition of Return
//
//
//
//  
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////



//GLOBAL EXPERIMENT CONSTANTS
//#define APP_NAME				"SDLGL IOR Experiment" 
//#define APP_VERSION				"0.0.0.0.0"

#define TICK_INTERVAL  			5
#define DIMENSION				250
#define MIN_CTOA_TIME			200.00
#define	MAX_CTOA_TIME			800.00  //Antes era 1000!!!! Primeros 20pico experimentos
#define CTOA_INTERVAL			(int) (MAX_CTOA_TIME - MIN_CTOA_TIME)	
		
//INTERFLASHES TIMES, COUNTED SINCE STIMULUS OFFSET
#define RESTING_TIME			60000 // Un minuto de descanso cada 100 trials
#define	INTER_TRIAL_TIME		1000
#define	INTER_FIX_CUE_TIME		250
#define INTER_CUE_FIX_TIME		50


//FLASHES SHOWING TIMES
#define	INITIAL_FIXATION_FLASH_TIME	1000
#define	CUE_FLASH_TIME				150
//#define	RETURN_FIXATION_FLASH_TIME	50


//SPATIAL PROPERTIES OF STIMULI
#define	FIXATION_X				(int) (WIDTH / 2)
#define	FIXATION_Y				(int) (HEIGHT / 2)
#define FIXATION_WIDTH			90
#define FIXATION_HEIGHT			80
#define FIXATION_LINE_WIDTH		10
#define	CUE_LEFT_X				(int) (WIDTH / 7)
#define CUE_RIGHT_X				(int) (WIDTH * 6 / 7)
#define CUE_Y					(int) (HEIGHT / 2)
#define CUE_BORDER				7
#define CUE_EXT_SIZE			100
#define	CUE_INT_SIZE			(int) (CUE_EXT_SIZE - 2 * CUE_BORDER)
#define CUE_FIX_DISTANCE		(int) (FIXATION_X - CUE_LEFT_X)

////////////////////////////////////////////////////////////
//		DISPOSICION DE LOS ESTIMULOS EN LA PANTALLA
//		LA POSICION DEL TARJET VARIA EN TORNO A LA DEL CUE
//		________________________________
//		|								|
//		|								|
//		|	#	#	#	#	#	#	#	|
//		|  CueL		   Fix		  CueR	|
//		|								|
//		---------------------------------
//
////////////////////////////////////////////////////////////

		
//------------------------------------------------------------------------------//
//																				//
//				ESTRUCTURAS DE DATOS Y CONSTANTES DE ESTADO						//
//							DEL EXPERIMENTO IOR									//
//																				//
//------------------------------------------------------------------------------//

typedef enum
{
	TRIAL_STATE_TAKE_A_REST,
	TRIAL_STATE_INTER_TRIAL,
	TRIAL_STATE_INIT_FIXATION,
	TRIAL_STATE_INTER_FIX_CUE,
	TRIAL_STATE_SHOW_CUE,
	TRIAL_STATE_INTER_CUE_FIX,
	TRIAL_STATE_RETURN_FIXATION,
	TRIAL_STATE_SHOW_TARGET,
	TRIAL_STATE_MAX
} 	TRIAL_STATE;

typedef enum
{
	TRIAL_LEFT_LEFT,
	TRIAL_LEFT_RIGHT,
	TRIAL_RIGHT_LEFT,
	TRIAL_RIGHT_RIGHT,
	TRIAL_TYPE_MAX,
} 	TRIAL_TYPE;

struct TRIAL
{
	Uint8 keypressed, bTraining;
	double rt;
	int ctoa, ctd;
	char* type;
};



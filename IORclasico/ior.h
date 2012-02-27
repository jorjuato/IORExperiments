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
#define TRIAL_REPLICATION 		6
#define TRAIN_REPLICATION 		1
#define FALSE_TRIALS_PROPORTION 0
#define TRIAL_TRAIN_NUMBER		CTOA_MAX  * TRIAL_TYPE_MAX * TRAIN_REPLICATION
#define DIMENSION 				CTOA_MAX  * TRIAL_TYPE_MAX * (TRIAL_REPLICATION + TRAIN_REPLICATION)
								// 3 		*       5 		*   (8 + 1) = 420
								
//INTERFLASHES TIMES, COUNTED SINCE STIMULUS OFFSET
#define RESTING_TIME			60000 // Un minuto de descanso cada 100 trials
#define	INTER_TRIAL_TIME		200
#define	INTER_FIX_CUE_TIME		250
#define INTER_CUE_FIX_TIME		100


//FLASHES SHOWING TIMES
#define	INITIAL_FIXATION_FLASH_TIME	1000
#define	CUE_FLASH_TIME				200
#define	RETURN_FIXATION_FLASH_TIME	100


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


typedef enum
{
	CTOA_300,
	CTOA_500,
	CTOA_700,
	CTOA_MAX
} 	CTOA_VALUES;
/*
typedef enum
{
	CTD_D_0,
	CTD_LEFT_D_8,
	CTD_LEFT_D_4,
	CTD_RIGHT_D_8,
	CTD_RIGHT_D_4,
	CTD_MAX
} 	CTD_VALUES;
*/
typedef struct {
	int value;
	char* name;
} CTD;

struct TRIAL
{
	Uint8 keypressed, bTraining;
	Uint16 order;
	double ctoa, rt;
	CTD ctd;
	char* type;
};


								


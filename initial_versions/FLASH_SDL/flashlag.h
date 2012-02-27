//////////////////////////////////////////////////////////////////
//  flashlag.h			
//							
//	Cabeceras para definir parámetros del experimento flashlag
//
//
//
//  
// Copyleft (L)		Noviembre 2007		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////



#define TICK_INTERVAL   30
#define INIT_X			150	
#define	INIT_Y			600
#define RADIUS			20
#define ERR_RADIUS		80
#define FLASH_X			800
#define FLASH_Y			150
#define SPEED			300.00
#define TOTAL_END_TIME	( ( 1600 / SPEED )*1000 - 2 * SPEED )
#define FLASH_INIT_TIME ( ( TOTAL_END_TIME / 2 ) - SPEED )
#define FLASH_END_TIME	FLASH_INIT_TIME + 200

typedef enum
{
	EXP_STATE_PRE,
	EXP_STATE_SEGUIMIENTO1,
	EXP_STATE_FLASH,
	EXP_STATE_SEGUIMIENTO2,
	EXP_STATE_RESPUESTA,
	EXP_STATE_ERROR,
	EXP_STATE_MAX
} EXP_STATE;



////////////////////////////////////////// Prototype definitions

void GraphicOutput();

int CheckError(void);

void GrabarDatos(void);

int time_left(void);

static void update();

void DrawCircle(int x_center, int y_center);

static void main_loop();

void OnExit();

void OnInit();

void OnDraw();

void OnReshape(int w, int h);

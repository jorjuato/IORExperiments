//////////////////////////////////////////////////////////////////
//  main.h			
//							
//
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////


int ctoa_val[] = {400, 600, 800};

float ctd_val[] = { 				  0, \
					-CUE_FIX_DISTANCE/4, \
					-CUE_FIX_DISTANCE/3, \
					 CUE_FIX_DISTANCE/4, \
					 CUE_FIX_DISTANCE/3 };
					 
char *ctd_code[] = {"equal", "-near", "-far", "near", "far" } ;

char *trial_type_name[] = {"LL", "LR", "RL", "RR"};
	


// SDL KEY codes
	//19 = RIGHT
	//20 = LEFT					 
//------------------------------------------------------------------------------//
//																				//
//							 Prototype definitions								//
//																				//
//------------------------------------------------------------------------------//

void OnExit();

void OnInit();

SDL_Surface* LoadImage(char *file);

static int MainLoop(void);

static void ExperimentSetup();

static void ExperimentEventMask();

static int ExperimentRandomize(void);

static int ExperimentTimer();

static int ExperimentHandler(void);

static void ExperimentGraphics(Uint32 time_inc);

static int EndExperiment(void);

static void ExperimentSave(void);

static int CalcTrialNumber(void);
/*
int TimeLeft(void);

void ShowFixation(void);

void ShowCue();

void ShowTarget();

void ShowBackground(Uint32 color);

void UpdateScreen();
*/



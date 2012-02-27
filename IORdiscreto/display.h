//////////////////////////////////////////////////////////////////
//  display.h	
//							
//
// Copyleft (L)		Febrero 2008		Jorge Ibáñez  						
//
//////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// (0,0)														(0,WIDTH)//
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
//					SDL COORDINATE REFERENCE SYSTEM						 //
//								( x , y )								 //
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
//																		 //
// (HEIGHT,0)										       (HEIGHT,WIDTH)//
///////////////////////////////////////////////////////////////////////////


// Definiciones de valores de la configuracion física de la tableta

#define X_RES			1600.00
#define Y_RES			1200.00
//#define X_RES			1280.00
//#define Y_RES			1024.00
//#define X_RES			1024
//#define Y_RES			768
#define WIDTH			X_RES
#define HEIGHT			Y_RES
#define X_AXE_RANG		87200.00
#define Y_AXE_RANG		65600.00
#define PRESS_FACTOR 	1024
#define X_FACTOR		( (X_RES) / (X_AXE_RANG) )
#define Y_FACTOR		( (Y_RES) / (Y_AXE_RANG) )
#define ASPECT_RATIO 	(WIDTH / HEIGHT )
#define GAMEMODESTRING 	"1600x1200:24@60" 

//Definicion de verdad y falsedad, jeje
#define true 		1
#define false 		0 
#define TRUE		true 
#define FALSE		false
#define APPERROR	true
#define APPSUCCESS	false
#define ERROR		false
#define SUCCESS 	true



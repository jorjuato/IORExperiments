/************************************************************************##
** 										libparser						 ##
**																		 ##
**						Jorge Ibáñez				Diciembre 2006		 ##	
**																		 ##
**																		 ##
**																		 ##
**  Libreria que contiene funciones para parsear la linea de comando y	 ##
**  responder apropiadamente al usuario. Muy básico, sirve de referencia ##
**																		 ##
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "parser.h"
#define IOR_VERSION "0.1.0"

//------------------------------------------------------------   int Parser()
//

const char* Parser(int argc, char** argv) {
	const char* pa;
	const char* subject_name=NULL;
	
	++argv;
	
	while ((pa = *(argv++)) != NULL) 
	{	
		if (pa[0] == '-')	
		{
			if ((strcmp(pa,"-h") == 0) || (strcmp(pa,"--help") == 0))
				Usage(0);
			else if ((strcmp(pa,"-V") == 0) || (strcmp(pa,"-v") == 0) || (strcmp(pa,"--version") == 0))
				{ Version(); Usage(0); exit(0); }
			else
				{ Usage(0); Fatal("Unknown option %s\n",pa);}
				
		}
		else if (!subject_name)
			subject_name = pa;
		else
			{ Usage(0); Fatal("Unknown argument %s\n",pa);}
	}		
	return (subject_name);
}

//------------------------------------------------------------   void Usage(int rtn)
//
void Usage(int rtn)
{
	FILE* f = rtn ? stderr : stdout;

	fprintf(f, "Usage: ior [options] subject_name\n"
			"  -h, --help                - usage\n"
			"  -V, --version             - version\n"
			"\n"
			"Use --list option for input_device choices\n");
	exit(rtn);
}

//------------------------------------------------------------   void Version(void)
//
void Version(void)
{
	fprintf(stdout,"%s\n",IOR_VERSION);
}

//------------------------------------------------------------   void Fatal(const char*)
//
void Fatal(const char* pszFmt, ...)
{
	va_list args;
	va_start(args,pszFmt);
	vfprintf(stderr,pszFmt,args);
	va_end(args);
	exit(1);
}



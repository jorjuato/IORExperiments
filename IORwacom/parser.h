/************************************************************************##
** 										libparser						 ##
**																		 ##
**						Jorge Ib��ez				Diciembre 2006		 ##	
**																		 ##
**																		 ##
**																		 ##
**  Libreria que contiene funciones para parsear la linea de comando y	 ##
**  responder apropiadamente al usuario. Muy b�sico, sirve de referencia ##
**																		 ##
**************************************************************************/



//////////////////////////////////////////////////////////////////
//		PROTOTIPOS DE LAS FUNCIONES							///
//////////////////////////////////////////////////////////////////

	
	const char* Parser(int argc, char** argv);  
	
		void Version();
	
		void Usage(int rtn);
	
		void Fatal(const char* pszFmt, ...);

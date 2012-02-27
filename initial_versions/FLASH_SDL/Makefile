CXX= gcc
CXXFLAGS = -Wall -O3 `sdl-config --cflags --libs` 
PROGS= glflash sdlflash
LIBS1 = -L. -lGL -lGLU -lglut -lpthread -lwacom
LIBS2 = -L. -lpthread -lwacom
#INC = 
MODULES = sdlgl_stuff.c
all: $(PROGS)

glflash: 
	@ echo
	@ echo
	@ echo "	######################################"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#  COMPILANDO...  glflash            #"	
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#         DEBIAN 4.0                 #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	######################################"
	@ echo 
	$(CXX)  sdlglflash.c $(MODULES) $(CXXFLAGS) $(LIBS1) -o glflash
	@ echo 
	@ echo 

	
sdlflash: 
	@ echo
	@ echo
	@ echo "	######################################"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#  COMPILANDO...  sdlflash	         #"	
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#         DEBIAN 4.0                 #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	######################################"
	@ echo 	
	$(CXX)  sdlflash.c $(MODULES) $(CXXFLAGS) $(LIBS1) -o sdlflash

sdlsnake: 
	@ echo
	@ echo
	@ echo "	######################################"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#  COMPILANDO...  sdlsnake            #"	
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#         DEBIAN 4.0                 #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	######################################"
	@ echo 
	$(CXX)  sdlsnake.c $(MODULES) $(CXXFLAGS) $(LIBS1) -lSDL_gfx -o sdlsnake
	@ echo 
	@ echo 



clean: 
	rm -f *.o sdlflash glflash flash.log data.raw

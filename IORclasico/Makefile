

CXX = gcc-4.1
CXXFLAGS = -g -Wall -O3
#CXXFLAGS = -g -Wall -O3 `sdl-config --cflags --libs` -lSDL_gfx

LIBS = -L/usr/lib -lSDL -lSDL_gfx
LIBS1 = -L. -lGL -lGLU -lglut -lpthread -lwacom 
LIBS2 = -L. -lpthread -lwacom -lSDL_gfx
INC = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
MODULES = ior_draw.c sdlgl_control.c parser.c


PROGS = ior_clasico

all: $(PROGS)

ior_clasico: 
	@ echo
	@ echo
	@ echo "	######################################"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#  COMPILANDO...  IOR	             #"	
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	######################################"
	@ echo 
	$(CXX) $(CXXFLAGS) $(INC) main.c  $(MODULES) $(LIBS)   -o ior_clasico

clean: 
	rm -f *.o ior_clasico ior.log 
	
	
	
	
	

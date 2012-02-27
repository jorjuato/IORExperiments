

IOR_DIR = ./IOR
IOR_CLASICO_DIR =  ./IORclasico
CXX = gcc-4.1
CXXFLAGS = -g -Wall -O3
#CXXFLAGS = -g -Wall -O3 `sdl-config --cflags --libs` -lSDL_gfx

LIBS = -L/usr/lib -lSDL -lSDL_gfx
LIBS1 = -L. -lGL -lGLU -lglut -lpthread -lwacom 
LIBS2 = -L. -lpthread -lwacom -lSDL_gfx
INC = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
MODULES = ior_draw.c sdlgl_control.c

##########################
# Define local variables #
##########################
DIRS = \
	src     $(IOR_DIR)\
	target  ./IORclasico

#####################
# Local Build Rules #
#####################
$(PRODUCT):
	@$(ECHO) " _______________________________________________________"
	@$(ECHO) "|"
	@$(ECHO) "| Building System $@"
	@$(ECHO) "|"
	@$(ECHO) "|_______________________________________________________"
	@$(TEST) -d target || $(ECHO) "DIRECTORY target DOES NOT EXIST"
	cd target && "$(MAKE)"
all: $(PROGS)

ior: 
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
	cd target && $(CXX) $(CXXFLAGS) $(INC) main.c  $(MODULES) $(LIBS)   -o ior
	
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
	cd $(IOR_CLASICO_DIR)
	$(CXX) $(CXXFLAGS) $(INC) main.c  $(MODULES) $(LIBS)   -o ior_clasic

clean: 
	rm -f *.o ior_clasic ior ior.log 
	
	
	
	
	

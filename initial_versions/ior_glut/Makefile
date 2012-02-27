CXX= gcc
CXXFLAGS = -O3 
PROGS= ior snake
LIBS =  -L./libwacom -lGL -lGLU -lglut -lpthread -lwacom
#INC = 
MODULES = 
all: $(PROGS)

ior: 
	@ echo
	@ echo
	@ echo "	######################################"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#  COMPILANDO...  ior                #"	
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#         DEBIAN 4.0                 #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	######################################"
	@ echo 
	$(CXX) ior.c drawingfunctions.c glutcontrol.c -Wall $(CXXFLAGS) $(LIBS)  $(MODULES)  -o ior
	@ echo 
	@ echo 
	@ echo 


snake:
	@ echo
	@ echo "	######################################"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#  COMPILANDO...  snake	             #"	
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	#         DEBIAN 4.0                 #"
	@ echo "	#                                    #"
	@ echo "	#                                    #"
	@ echo "	######################################"
	@ echo 
	$(CXX) snake_threaded.c -Wall $(CXXFLAGS) $(LIBS) $(MODULES)  -o snake
	@ echo 
	@ echo 

clean: 
	rm -f flashlag snake datos_flash

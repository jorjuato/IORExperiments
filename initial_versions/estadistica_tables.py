#!/usr/bin/env python
# -*- coding: utf-8 -*-


import scipy as s
import numpy
import tables 

class Trial(tables.IsDescription):
	index 	= tables.UInt16Col()
	order 	= tables.UInt16Col()
	type 	= tables.UInt16Col()
	ctoa 	= tables.UInt16Col()
	ctd 	= tables.Int16Col()
	rt 		= tables.UInt16Col()
	key 	= tables.UInt8Col()
	
def load_data():
	"""
		Funcion que lee los datos de salida del programa C  
	"""

	file = open("./data.txt", "r")

	h5file = tables.openFile("iordata.h5", mode = "w", title = "IOR data results")
	group = h5file.createGroup("/", 'sujeto1', 'Data from subject 1')
	table = h5file.createTable(group, 'rawdata', Trial, "Raw data from IOR experiment")
	
	datablock = 0 	#Flag que marca la lectura del bloque de datos

	
	for line in file:
		campos = line.split()
		
		if campos.__len__() == 0:	#Si la linea esta vacia 
			continue
		elif campos[0] == "#?" : 	#Si es un texto de ayuda
			continue	
		elif campos[0] == "#$" :	#Si es el valor de un parametro
			if  campos[1] == "TRIAL_LEFT_LEFT":
				table.attrs.TRIAL_LEFT_LEFT 	= int(campos[3])
			elif campos[1] == "TRIAL_LEFT_RIGHT":
				table.attrs.TRIAL_LEFT_RIGHT 	= int(campos[3])
			elif campos[1] == "TRIAL_RIGHT_LEFT":
				table.attrs.TRIAL_RIGHT_LEFT 	= int(campos[3])
			elif campos[1] == "TRIAL_RIGHT_RIGHT":
				table.attrs.TRIAL_RIGHT_RIGHT 	= int(campos[3])
			elif campos[1] == "TRIAL_TRAIN_NUMBER":
				table.attrs.TRIAL_TRAIN_NUMBER 	= int(campos[3])
			elif campos[1] == "TRIAL_TYPE_MAX":
				table.attrs.TRIAL_TYPE_MAX 		= int(campos[3])
			elif campos[1] == "TRIAL_REPLICATION":
				table.attrs.TRIAL_REPLICATION 	= int(campos[3])
			elif campos[1] == "DIMENSION":
				table.attrs.DIMENSION 			= int(campos[3])
		elif campos[0] == "#!":		#Si empezamos el datablock
			datablock = 1
		elif campos[0] == "#¡":		#Si terminamos el datablock
			datablock = 0			
		elif datablock == 1:		#Si no es ninguna de las anteriores, es un datablock
			trial = table.row
			trial['index'] 	= int(campos[0])
			trial['order'] 	= int(campos[1])
			trial['type'] 	= int(campos[2])
			trial['ctoa'] 	= int(campos[3])
			trial['ctd'] 	= int(campos[4])
			trial['rt'] 	= int(campos[5])
			trial['key'] 	= int(campos[6])
			trial.append()
			table.flush()
						
	return h5file
	
	
def crear_listas(h5file):
	# Ahora toca jugar con los datos. Creare una serie de sublistas
	table = h5file.root.sujeto1.rawdata
	
	rt_cued_300 	= [ x['rt'] for x in table.iterrows()
						if (x['type'] == 0 or x['type'] == 3) and x['ctoa'] == 300]
						
	rt_uncued_300 	= [ x['rt'] for x in table.iterrows()
						if (x['type'] == 1 or x['type'] == 2) and x['ctoa'] == 300]
						
	rt_cued_500 	= [ x['rt'] for x in table.iterrows()
						if (x['type'] == 0 or x['type'] == 3) and x['ctoa'] == 500]
						
	rt_uncued_500 	= [ x['rt'] for x in table.iterrows()
						if (x['type'] == 1 or x['type'] == 2) and x['ctoa'] == 500]
						
	rt_cued_700 	= [ x['rt'] for x in table.iterrows()
						if (x['type'] == 0 or x['type'] == 3) and x['ctoa'] == 700]
						
	rt_uncued_700 	= [ x['rt'] for x in table.iterrows()
						if (x['type'] == 1 or x['type'] == 2) and x['ctoa'] == 700]
	listas = []
	listas.append(rt_cued_300)
	listas.append(rt_uncued_300)
	listas.append(rt_cued_500)
	listas.append(rt_uncued_500)
	listas.append(rt_cued_700)
	listas.append(rt_uncued_700)
	return listas


#Este es el punto inicial del script si es llamado desde linea de comandos
#con una orden del tipo: "python estadistica_tables.py". Es como la funcion main() en C
#Esta cuestion requiere un poco mas de explicacion, pero bueno...
if __name__ == "__main__":

	import scipy as s 
	
	h5file = load_data()
	listas = crear_listas(h5file)
	stats = []
	
	for item in listas:
		temp = []
		temp.append(s.mean(item))
		temp.append(s.std(item))
		stats.append(temp)
	print stats
	
	h5file.close()	
    	
    	
    	
    	
    		
    	

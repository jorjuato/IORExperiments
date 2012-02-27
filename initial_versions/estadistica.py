#!/usr/bin/env python
# -*- coding: utf-8 -*-


import scipy as s
import numpy 

class Trial:
	def __init__(self, campos):
		self.index = int(campos[0])
		self.order = int(campos[1])
		self.type = int(campos[2])
		self.ctoa = int(campos[3])
		self.ctd = int(campos[4])
		self.rt = int(campos[5])
		self.key = int(campos[6])

class Conf:
	pass
	
def load_data():
	"""
		Funcion que lee los datos de salida del programa C  
	"""

	file = open("./data.txt", "r")

	datablock = 0 	#Flag que marca la lectura del bloque de datos
	resultados = [] #Lista que contendra los trials
	conf = Conf()
	
	for line in file:
		campos = line.split()
		
		if campos.__len__() == 0:	#Si la linea esta vacia 
			continue
		elif campos[0] == "#?" : 	#Si es un texto de ayuda
			continue	
		elif campos[0] == "#$" :	#Si es un valor de un parametro
			if  campos[1] == "TRIAL_LEFT_LEFT":
				conf.TRIAL_LEFT_LEFT = int(campos[3])
			elif campos[1] == "TRIAL_LEFT_RIGHT":
				conf.TRIAL_LEFT_RIGHT = int(campos[3])
			elif campos[1] == "TRIAL_RIGHT_LEFT":
				conf.TRIAL_RIGHT_LEFT = int(campos[3])
			elif campos[1] == "TRIAL_RIGHT_RIGHT":
				conf.TRIAL_RIGHT_RIGHT = int(campos[3])
			elif campos[1] == "TRIAL_TRAIN_NUMBER":
				conf.TRIAL_TRAIN_NUMBER = int(campos[3])
			elif campos[1] == "TRIAL_TYPE_MAX":
				conf.TRIAL_TYPE_MAX = int(campos[3])
			elif campos[1] == "TRIAL_REPLICATION":
				conf.TRIAL_REPLICATION = int(campos[3])
			elif campos[1] == "DIMENSION":
				conf.DIMENSION = int(campos[3])
		elif campos[0] == "#!":		#Si empezamos el datablock
			datablock = 1
		elif campos[0] == "#¡":		#Si terminamos el datablock
			datablock = 0			
		elif datablock == 1:		#Si no es ninguna de las anteriores, es un datablock
			resultados.append(Trial(campos))
	return resultados , conf

if __name__ == "__main__":
	import pylab 
	res, conf= load_data()
	

    	
    	

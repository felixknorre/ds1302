#
# Makefile for a linux user app and wiringPi
#
# Copyright 2020 Felix Knorre  <felix-knorre@hotmail.de>
#

all : setTime getTime

setTime : setTime.c
	gcc -Wall -o setTime setTime.c -lwiringPi -lwiringPiDev
	
getTime : getTime.c
	gcc -Wall -o getTime getTime.c -lwiringPi -lwiringPiDev
		
clean : 
	rm setTime getTime

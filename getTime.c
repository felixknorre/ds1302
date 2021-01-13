/*
 * getTime.c
 * 
 * Copyright 2021  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <wiringPi.h>
#include <ds1302.h>
#include <time.h>


#define BUFFER_SIZE 32

#define CLK_PIN 4 // GPIO 23
#define IO_PIN 5 // GPIO 24
#define CE_PIN 6 // GPIO 25


int bcdToD(int b){
	return (((b>>4)*10) + (b &0xF));
}

int main(int argc, char **argv)
{
	struct  tm curr_time;
	char buff[BUFFER_SIZE];
	int clock[8];
	
	// setup
	wiringPiSetup();
	ds1302setup(CLK_PIN, IO_PIN, CE_PIN);
	
	// read time from register
	ds1302clockRead(clock);
	
	// convert time to decimal
	curr_time.tm_sec = bcdToD(clock[0]);
	curr_time.tm_min = bcdToD(clock[1]);
	curr_time.tm_hour = bcdToD(clock[2]);
	curr_time.tm_mday = bcdToD(clock[3]);
	curr_time.tm_mon = bcdToD(clock[4]);
	curr_time.tm_wday = bcdToD(clock[5]);
	curr_time.tm_year = bcdToD(clock[6]);
	
	strftime(buff, sizeof(buff), "%a, %d-%m-%Y %X", &curr_time);
	printf("%s\n", buff);
	
	return 0;
}

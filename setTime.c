/*
 * setTime.c
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

int dToBcd(int d){
	return (((d/10) << 4) | (d %10));	
}

int main(int argc, char **argv)
{
	struct  tm * curr_time;
	time_t u_time;
	char buff[BUFFER_SIZE];
	int clock[8];
	
	// setup
	wiringPiSetup();
	ds1302setup(CLK_PIN, IO_PIN, CE_PIN);
	
	
	// get current time
	time(&u_time);
	curr_time = localtime(&u_time);
	
	strftime(buff, sizeof(buff), "%a, %d-%m-%Y %X", curr_time);
	printf("%s\n", buff);
	
	
	// decimal to binary coded decimal
	clock[0] = dToBcd(curr_time->tm_sec);
	clock[1] = dToBcd(curr_time->tm_min);
	clock[2] = dToBcd(curr_time->tm_hour);
	clock[3] = dToBcd(curr_time->tm_mday);
	clock[4] = dToBcd(curr_time->tm_mon);
	clock[5] = dToBcd(curr_time->tm_wday);
	clock[6] = dToBcd(curr_time->tm_year - 100);
	clock[7] = 0;
	
	// wriet time to ds1302
	ds1302clockWrite(clock);

	printf("DS1303 set time...\n");

	return 0;
}


/*
 * spot.c
 *
 *  Created on: May 26, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "spot.h"

spots_t* spots_init(int total)
{
	spots_t *my_spots;

	my_spots = (spots_t*)malloc(sizeof(spots_t));
	my_spots->x = (int*)malloc(sizeof(int) * total);
	my_spots->y = (int*)malloc(sizeof(int) * total);

	my_spots->total = total;

	return my_spots;

}

void spots_destroy(spots_t* my_spots)
{
	free(my_spots->x);
	free(my_spots->y);
	free(my_spots);
}

void spots_print(spots_t* my_spots)
{
	int i;

	printf("\nPrinting spots...\n");

	for(i = 0; i < my_spots->total; i++)
	{
		printf("spot %d: x: %d y: %d \n", i, my_spots->x[i], my_spots->y[i]);
	}

}

float spots_distance(spots_t* my_spots, int src_spot, int dst_spot)
{
	float x_delta, y_delta;

	x_delta = my_spots->x[dst_spot] - my_spots->x[src_spot];
	y_delta = my_spots->y[dst_spot] - my_spots->y[src_spot];


	return 1.0;
	//return sqrtf( (x_delta * x_delta) + (y_delta * y_delta) );
}



/*
 * spot.h
 *
 *  Created on: May 26, 2013
 *      Author: emanuel
 */

#ifndef SPOT_H_
#define SPOT_H_

typedef struct
{
	int *x;
	int *y;
	int total;

}spots_t;

spots_t* spots_init(int total);
void spots_destroy(spots_t* my_spots);
void spots_print(spots_t* my_spots);
float spots_distance(spots_t* my_spots, int src_spot, int dst_spot);


#endif /* SPOT_H_ */

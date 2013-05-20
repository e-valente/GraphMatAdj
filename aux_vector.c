/*
 * aux_vector_t.c
 *
 *  Created on: May 19, 2013
 *      Author: emanuel
 */


#include <stdlib.h>
#include "aux_vector.h"

aux_vector_t *aux_vector_init(int total)
{
	aux_vector_t *my_auxvector;

	my_auxvector = (aux_vector_t*)malloc(sizeof(aux_vector_t));

	my_auxvector->total = total;

	my_auxvector->vertex = (int*)malloc(sizeof(int) * total);
	my_auxvector->cost = (int*)malloc(sizeof(int) * total);
	my_auxvector->predec = (int*)malloc(sizeof(int) * total);
	my_auxvector->isvalid = (int*)malloc(sizeof(int) * total);

	return my_auxvector;
}

void aux_vector_destroy(aux_vector_t *my_auxvector)
{
	free(my_auxvector->vertex);
	free(my_auxvector->cost);
	free(my_auxvector->predec);
	free(my_auxvector->isvalid);

	free(my_auxvector);


}

void aux_vector_addvertex(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->vertex[pos] = value;
	my_auxvector->isvalid[pos] = 1;
}

void aux_vector_addcost(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->cost[pos] = value;
}

void aux_vector_addpredec(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->predec[pos] = value;
}


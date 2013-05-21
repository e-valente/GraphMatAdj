/*
 * aux_vector_t.c
 *
 *  Created on: May 19, 2013
 *      Author: emanuel
 */


#include <stdlib.h>
#include <stdio.h>
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
	my_auxvector->min_cost = (int*)malloc(sizeof(int) * total);

	return my_auxvector;
}

void aux_vector_destroy(aux_vector_t *my_auxvector)
{
	free(my_auxvector->vertex);
	free(my_auxvector->cost);
	free(my_auxvector->predec);
	free(my_auxvector->isvalid);
	free(my_auxvector->min_cost);

	free(my_auxvector);


}

void aux_vector_addvertex(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->vertex[pos] = value;
	my_auxvector->isvalid[pos] = 1;
}

void aux_vector_addcost(aux_vector_t *my_auxvector, int pos, int value)
{
	if(value != 0)
		my_auxvector->cost[pos] += value;

	else my_auxvector->cost[pos] = value;

}

void aux_vector_addpredec(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->predec[pos] = value;
}

void aux_vector_addmincost(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->min_cost[pos] = value;
}

void aux_vector_print(aux_vector_t *my_auxvector)
{
	int i;
	printf("Printing aux vector...\n\n");

	printf("Printing vertexes...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->vertex[i]);

	}

	printf("\n");

	printf("Printing costs...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->cost[i]);

	}

	printf("\n");

	printf("Printing predecs...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->predec[i]);

	}

	printf("\n");


	printf("Printing isvalid?...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->isvalid[i]);

	}

	printf("\n");

	printf("Printing mincost...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->min_cost[i]);

	}


	printf("\n");



}

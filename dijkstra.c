/*
 * dijkstra.c
 *
 *  Created on: May 20, 2013
 *      Author: emanuel
 */

#include "graph_mat_adj.h"
#include "aux_vector.h"
#include "dijkstra.h"

void dijkstra(GRAPH_MAT_ADJ *mygraph, int posvertex_ini, int posvertex_end, aux_vector_t* my_auxvector)
{
	int i;
	//preenche o vetor de predec
	dijkstra_init(mygraph, my_auxvector);

	printf("Arestas:..\n");
	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		printf("%d ", mygraph->edge[posvertex_ini][i]);

		//ecoar p/ aux vector
		aux_vector_addcost(my_auxvector, i, mygraph->edge[posvertex_ini][i]);
		//após isso, internamente addcost chama calc mincost


	}

	aux_vector_calcmincost(my_auxvector);

	printf("\n");

}

void dijkstra_init(GRAPH_MAT_ADJ *mygraph, aux_vector_t* my_auxvector)
{
	int i;
	int total = mygraph->total_vertexes;

	for(i = 0; i < total; i++)
	{
		aux_vector_addvertex(my_auxvector, i, mygraph->vertex[i]);
		aux_vector_addcost(my_auxvector, i, 0);
		aux_vector_addpredec(my_auxvector, i, -1);
		aux_vector_addmincost(my_auxvector, i, 0);


	}

}

void aux_vector_calcmincost(aux_vector_t *my_auxvector)
{
	int i, min_pos, min_cost;



	min_cost = my_auxvector->cost[0];

	for(i = 1, min_pos = 0; i < my_auxvector->total; i++)
	{
		if(my_auxvector->cost[i] < min_cost)
		{
			min_cost = my_auxvector->cost[i];
			min_pos = i;
		}

	}

	printf("menor custo: %d na posicao: %d\n", min_cost, min_pos);
}

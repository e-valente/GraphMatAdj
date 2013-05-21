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
	//preenche o vetor de predec
	dijkstra_init(mygraph, my_auxvector);

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


	}

}

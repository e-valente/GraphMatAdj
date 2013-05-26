/*
 * dijkstra.c
 *
 *  Created on: May 20, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include "graph_mat_adj.h"
#include "aux_vector.h"
#include "dijkstra.h"

void dijkstra(GRAPH_MAT_ADJ *mygraph, int posvertex_ini, aux_vector_t* my_auxvector)
{
	int i;
	int pos, pos_parent_on_tree, pos_child_on_tree;
	//preenche o vetor de predec
	dijkstra_init(mygraph, my_auxvector);



	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		//ecoar p/ aux vector
		aux_vector_addcost(my_auxvector, i, mygraph->edge[posvertex_ini][i]);
		aux_vector_update_predec(my_auxvector, i, -1);



	}


	//insiro o primeiro elemento na árvore
	pos = posvertex_ini;
	aux_vector_addcost(my_auxvector, pos, 0);
	aux_vector_updatecost_prim(my_auxvector, mygraph, pos);
	aux_vector_update_isvalid(my_auxvector, pos, 0);

	while(aux_vector_has_valid_elems(my_auxvector) == 1 && pos != -1)
	{
		//insere segundo elemento
		//pos -> será o primeiro elemento
		aux_vector_updatecost_dijkstra(my_auxvector, mygraph, pos);
		pos = aux_vector_calcmincost(my_auxvector);

		if(pos != -1){
			aux_vector_next_insert_on_tree(my_auxvector, &pos_parent_on_tree, &pos_child_on_tree);
			aux_vector_update_isvalid(my_auxvector, pos, 0);

		}


	}

}

void dijkstra_init(GRAPH_MAT_ADJ *mygraph, aux_vector_t* my_auxvector)
{
	int i;
	int total = mygraph->total_vertexes;

	for(i = 0; i < total; i++)
	{
		aux_vector_addvertex(my_auxvector, i, mygraph->vertex[i]);
		aux_vector_addcost(my_auxvector, i, 0);
		aux_vector_update_predec(my_auxvector, i, -1);
		aux_vector_addmincost(my_auxvector, i, 0);


	}

}

void dijkstra_travel_tree(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end)
{
	my_auxvector_travel_tree(mygraph, my_auxvector, pos_start, pos_end);
}

int dijkstra_travel_tree_and_return_min_cost(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end)
{
	return my_auxvector_travel_tree_and_return_min_cost_dijkstra(mygraph, my_auxvector, pos_start, pos_end);

}


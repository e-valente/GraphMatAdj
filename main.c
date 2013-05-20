/*
 * main.c
 *
 *  Created on: May 15, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>

#include "graph_mat_adj.h"
#include "aux_vector.h"

int main(int argc, char *argv[])
{
	GRAPH_MAT_ADJ *mygraph;
	aux_vector_t *my_auxvector;

	mygraph = graph_mat_adj_init(30);

	printf("grafo criado...\n");


	graph_mat_adj_insert_vertex(mygraph, 0, 2);

	graph_mat_adj_print_vertexes(mygraph);

	graph_mat_adj_insert_edge(mygraph, -2, 3, 20);

	graph_mat_adj_print_edges(mygraph);


	graph_mat_adj_destroy(mygraph);

	my_auxvector = aux_vector_init(100);
	aux_vector_destroy(my_auxvector);

	return 0;
}

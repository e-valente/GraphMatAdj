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
#include "tree.h"
#include "dijkstra.h"

int main(int argc, char *argv[])
{
	GRAPH_MAT_ADJ *mygraph;
	aux_vector_t *my_auxvector;
	Tree *mytree;

	mygraph = graph_mat_adj_init(5);
	my_auxvector = aux_vector_init(5);
	mytree = buildTree();

	printf("grafo criado...\n");


	graph_mat_adj_insert_vertex(mygraph, 0, 1);
	graph_mat_adj_insert_vertex(mygraph, 1, 2);
	graph_mat_adj_insert_vertex(mygraph, 2, 3);
	graph_mat_adj_insert_vertex(mygraph, 3, 4);
	graph_mat_adj_insert_vertex(mygraph, 4, 5);

	//graph_mat_adj_print_vertexes(mygraph);

	graph_mat_adj_insert_edge(mygraph, 0, 1, 20);
	graph_mat_adj_insert_edge(mygraph, 0, 2, 40);
	graph_mat_adj_insert_edge(mygraph, 0, 4, 150);
	graph_mat_adj_insert_edge(mygraph, 1, 3, 60);
	graph_mat_adj_insert_edge(mygraph, 2, 3, 10);
	graph_mat_adj_insert_edge(mygraph, 3, 4, 20);


	graph_mat_adj_print_edges(mygraph);

	dijkstra(mygraph, 0, 4, my_auxvector);

	aux_vector_print(my_auxvector);


	//destroy graph and aux vector
	graph_mat_adj_destroy(mygraph);
	aux_vector_destroy(my_auxvector);
	destroyTree(mytree);

	return 0;
}

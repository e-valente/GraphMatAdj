/*
 * main.c
 *
 *  Created on: May 15, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "graph_mat_adj.h"
#include "aux_vector.h"
#include "dijkstra.h"
#include "prim.h"

int main(int argc, char *argv[])
{
	GRAPH_MAT_ADJ *mygraph;
	aux_vector_t *my_auxvector;
	int max_cost;

	//entrada lab3 - exer2
	/*
	int nvertex, nedges, src_vertex, dst_vertex, weight;
	int max_cost, trips;
	int i;

	scanf("%d", &nvertex);
	scanf("%d", &nedges);



	mygraph = graph_mat_adj_init(nvertex);
	my_auxvector = aux_vector_init(nvertex);

	//insere vertices
	for(i = 0; i < nvertex; i++)
	{
		graph_mat_adj_insert_vertex(mygraph, i, i);

	}


	//insere arestas
	for(i = 0; i < nedges; i++)
	{
		scanf("%d %d %d", &src_vertex, &dst_vertex, &weight);
		graph_mat_adj_insert_edge(mygraph, src_vertex, dst_vertex, weight);
		graph_mat_adj_insert_edge(mygraph, dst_vertex, src_vertex, weight);

	}


	scanf("%d", &trips);

	for(i = 0; i< trips; i++)
	{
		scanf("%d %d", &src_vertex, &dst_vertex);
		dijkstra(mygraph, src_vertex, my_auxvector);
		max_cost = dijkstra_travel_tree_and_return_min_cost_dijkstra(mygraph, my_auxvector, src_vertex, dst_vertex);

		if(max_cost < 0 || max_cost == INT_MAX)
			printf("no path\n");
		else printf("%d\n", max_cost);

	}

	 */

	//dijkstra(mygraph, src_vertex, my_auxvector);




	mygraph = graph_mat_adj_init(5);
	my_auxvector = aux_vector_init(5);

	printf("grafo criado...\n");


	graph_mat_adj_insert_vertex(mygraph, 0, 0);
	graph_mat_adj_insert_vertex(mygraph, 1, 1);
	graph_mat_adj_insert_vertex(mygraph, 2, 2);
	graph_mat_adj_insert_vertex(mygraph, 3, 3);
	graph_mat_adj_insert_vertex(mygraph, 4, 4);

	//graph_mat_adj_print_vertexes(mygraph);

	graph_mat_adj_insert_edge(mygraph, 0, 1, 20);
	graph_mat_adj_insert_edge(mygraph, 0, 2, 40);
	graph_mat_adj_insert_edge(mygraph, 0, 4, 150);
	graph_mat_adj_insert_edge(mygraph, 1, 3, 60);
	graph_mat_adj_insert_edge(mygraph, 2, 3, 10);
	graph_mat_adj_insert_edge(mygraph, 3, 4, 20);



	//dijkstra(mygraph, 0, 4, my_auxvector);
	//dijkstra_travel_tree(mygraph, my_auxvector, 0, 4);

	prim(mygraph, 0, my_auxvector);

	aux_vector_print(my_auxvector);

	max_cost = prim_travel_tree_and_return_max_cost(mygraph, my_auxvector, 0, 3);

	if(max_cost < 0 || max_cost == INT_MAX)
		printf("no path\n");
	else printf("%d\n", max_cost);

	//destroy graph and aux vector
	graph_mat_adj_destroy(mygraph);
	aux_vector_destroy(my_auxvector);

	return 0;
}

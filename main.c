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
//#include "dijkstra.h"
//#include "prim.h"
#include "spot.h"

int main(int argc, char *argv[])
{
	GRAPH_MAT_ADJ *mygraph;
	aux_vector_t *my_auxvector;
	spots_t *my_spots;



	//entrada T3 - grafos
	int nspots, nsat_channels;
	int x_spot, y_spot, weight;
	int i, j;

	scanf("%d %d", &nsat_channels, &nspots);


	//inicia grafos
	mygraph = graph_mat_adj_init(nspots);
	my_auxvector = aux_vector_init(nspots);
	my_spots = spots_init(nspots);

	//obtem postos e cria vertices
	for(i = 0; i < nspots; i++)
	{
		//coordenada de cada posto (spot)
		scanf("%d %d", &x_spot, &y_spot);
		my_spots->x[i] = x_spot;
		my_spots->y[i] = y_spot;

		//cria vertices
		graph_mat_adj_insert_vertex(mygraph, i, i);

	}

	//spots_print(my_spots);

	//cria as arestas
	for(i = 0; i < nspots -1; i++)
	{
		for(j = i+1; j < nspots; j++)
		{

			weight = spots_distance(my_spots, i, j);
			graph_mat_adj_insert_edge(mygraph, i, j, weight);

		}

	}


	//TODO -> calcular grau de cada vertice e armazenar
	//na estrutura de cada vertice..





	/*
	//entrada lab3 - exer1
	int nvertex, nedges, src_vertex, dst_vertex, weight;
	int min_cost, trips;
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

		//se o grafo nao for direcionado
		graph_mat_adj_insert_edge(mygraph, dst_vertex, src_vertex, weight);

	}


	scanf("%d", &trips);

	//encontra arvore geradora
	//prim(mygraph, 1, my_auxvector);

	for(i = 0; i< trips; i++)
	{
		scanf("%d %d", &src_vertex, &dst_vertex);


		//printf("comecando do %d\n", src_vertex);
		dijkstra(mygraph, src_vertex, my_auxvector);
		min_cost = dijkstra_travel_tree_and_return_min_cost(mygraph, my_auxvector, src_vertex, dst_vertex);
		//aux_vector_print(my_auxvector);

		//aux_vector_print(my_auxvector);

		if(min_cost == INT_MAX || min_cost < 0)
			printf("no path\n");
		else printf("%d\n", min_cost);


	}

	 */

	/*
	//entrada lab3 - exer2
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

		//se o grafo nao for direcionado
		graph_mat_adj_insert_edge(mygraph, dst_vertex, src_vertex, weight);

	}


	scanf("%d", &trips);

	//encontra arvore geradora
	//prim(mygraph, 1, my_auxvector);

	for(i = 0; i< trips; i++)
	{
		scanf("%d %d", &src_vertex, &dst_vertex);


		//printf("comecando do %d\n", src_vertex);
		prim(mygraph, src_vertex, my_auxvector);
		max_cost = prim_travel_tree_and_return_max_cost(mygraph, my_auxvector, src_vertex, dst_vertex);
		//aux_vector_print(my_auxvector);

		//aux_vector_print(my_auxvector);

		if(max_cost < 0 || max_cost == INT_MAX)
			printf("no path\n");
		else printf("%d\n", max_cost);


	}

	 */




	//destroy graph and aux vector
	spots_destroy(my_spots);
	graph_mat_adj_destroy(mygraph);
	aux_vector_destroy(my_auxvector);

	return 0;
}



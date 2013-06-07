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
#include "kcore.h"

//#include "aux_vector.h"
//#include "dijkstra.h"
//#include "prim.h"
//#include "spot.h"


int compare_vkcore_byindex_qsort(void const *a, void const *b);

int main(int argc, char *argv[])
{
	GRAPH_MAT_ADJ *mygraph;
	INFO_VERTEXES *mygraph_info;
	vkcore_t *myvkcore;
	int nvertex, nedges, src_vertex, dst_vertex, weight;
	int i;


	scanf("%d", &nvertex);
	scanf("%d", &nedges);


	mygraph = graph_mat_adj_init(nvertex);


	//insere vertices
	for(i = 0; i < nvertex; i++)
	{
		graph_mat_adj_insert_vertex(mygraph, i, i);

	}


	//insere arestas
	for(i = 0; i < nedges; i++)
	{
		scanf("%d %d ", &src_vertex, &dst_vertex);
		graph_mat_adj_insert_edge(mygraph, src_vertex, dst_vertex, 1);

		//se o grafo nao for direcionado
		graph_mat_adj_insert_edge(mygraph, dst_vertex, src_vertex, 1);

	}


	mygraph_info = graph_mat_adj_info_init(mygraph);

	//calcular grau de cada vertice
	graph_mat_adj_calc_degrees(mygraph, mygraph_info);



	//Calculo de kcore de cada certice
	myvkcore = NULL;
	myvkcore = vkcore_init(mygraph_info);
	vkcore_calc_for_all_vertexes(myvkcore, mygraph);


	//imprime resposta (k-core de cada vertice)
	//ordena por indice
	qsort(myvkcore, nvertex, sizeof(vkcore_t), compare_vkcore_byindex_qsort);

	for(i = 0; i < nvertex; i++)
	{
		printf("%d ", myvkcore[i].degree);
	}

	//debug
	/*
	graph_mat_adj_print_info(mygraph_info);
	graph_mat_adj_print_edges(mygraph);*/



	//destroy graph and aux vector
	vkcore_destroy(myvkcore);
	graph_mat_adj_info_destroy(mygraph_info);
	graph_mat_adj_destroy(mygraph);




	return 0;
}

int compare_vkcore_byindex_qsort(void const *a, void const *b)
{

	if( ((vkcore_t*)a)->vertex > ((vkcore_t*)b)->vertex) return 1;
	else return 0;

}


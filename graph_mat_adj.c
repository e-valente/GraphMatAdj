/*
 * graph_mat_adj.c
 *
 *  Created on: May 15, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "graph_mat_adj.h"


GRAPH_MAT_ADJ* graph_mat_adj_init(int total_vertexes)
{
	GRAPH_MAT_ADJ *mygraph;
	int i, j;

	mygraph = (GRAPH_MAT_ADJ*) malloc(sizeof(GRAPH_MAT_ADJ));

	mygraph->total_vertexes = total_vertexes;

	mygraph->vertex = (int*)malloc(sizeof(int) * total_vertexes);

	mygraph->edge = (int**)malloc(sizeof(int*) * total_vertexes);

	for(i = 0; i < total_vertexes; i++)
	{
		mygraph->edge[i] = (int*)malloc(sizeof(int) * total_vertexes);

		for(j = 0; j < total_vertexes; j++)
		{
			if(i != j) mygraph->edge[i][j] = INT_MAX;
			else mygraph->edge[i][j] = 0;
		}
	}

	//memset(mygraph->vertex, 0, total_vertexes * sizeof(int));


	/*fix it!*/
	//memset(mygraph->edge, 0, total_vertexes * total_vertexes * sizeof(int));

	return mygraph;


}



void graph_mat_adj_destroy(GRAPH_MAT_ADJ *mygraph)
{
	int i;

	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		free(mygraph->edge[i]);
	}

	free(mygraph->edge);
	free(mygraph->vertex);
	free(mygraph);



}

void graph_mat_adj_insert_vertex(GRAPH_MAT_ADJ *mygraph, int pos, int value)
{
	if(pos < (mygraph->total_vertexes)
			&& pos >= 0) mygraph->vertex[pos] = value;

	else {
		printf("\"graph_mat_adj_insert_vertex\": Posição %d inválida!\n", pos);
	}
}


void graph_mat_adj_insert_edge(GRAPH_MAT_ADJ *mygraph, int src, int dst, int weight)
{
	if((src > (mygraph->total_vertexes -1) || src < 0) ||
			(dst > (mygraph->total_vertexes -1) || dst < 0))
	{
		printf("\"graph_mat_adj_insert_edge\": "
				"Posição inválida: src: %d dst: %d\n", src, dst);
		return;

	}

	mygraph->edge[src][dst] = weight;

}

void graph_mat_adj_print_vertexes(GRAPH_MAT_ADJ *mygraph)
{
	int i;

	printf("Printing Vertexes..\n");

	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		printf("%d ", mygraph->vertex[i]);
	}

	printf("\n");

}


void graph_mat_adj_print_edges(GRAPH_MAT_ADJ *mygraph)
{
	int i, j;

	printf("Printing Edges..\n");

	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		for(j = 0; j < mygraph->total_vertexes; j++)
		{
			//mygraph->edge[i][j] = 1;
			printf("%d ", mygraph->edge[i][j]);
		}

		printf("\n");
	}

	printf("\n");

}

int is_adj(GRAPH_MAT_ADJ *mygraph, int src_pos_vertex, int dst_pos_vertex)
{


	if(mygraph->edge[src_pos_vertex][dst_pos_vertex] != 0 &&
			mygraph->edge[src_pos_vertex][dst_pos_vertex] != INT_MAX)
		return 1;

	if(mygraph->edge[dst_pos_vertex][src_pos_vertex] != 0 &&
			mygraph->edge[dst_pos_vertex][src_pos_vertex] != INT_MAX)
		return 1;

	//printf("retonei zero de %d para %d\n", src_pos_vertex, dst_pos_vertex);
	return 0;


}

INFO_VERTEXES* graph_mat_adj_info_init(GRAPH_MAT_ADJ *mygraph)
{
	INFO_VERTEXES *my_vertexinfo;
	int total = mygraph->total_vertexes;
	int i;

	my_vertexinfo = (INFO_VERTEXES*)malloc(sizeof(INFO_VERTEXES));
	my_vertexinfo->degree = (int*)malloc(sizeof(int) * total);
	my_vertexinfo->coefagrup = (double*)malloc(sizeof(double) * total);

	my_vertexinfo->total = total;

	for(i = 0; i < total; i++)
	{
		my_vertexinfo->degree[i] = 0;
		my_vertexinfo->coefagrup[i] = 0.0;

	}

	return my_vertexinfo;
}

void graph_mat_adj_calc_degrees(GRAPH_MAT_ADJ *mygraph, INFO_VERTEXES *mygraph_info)
{
	int i, j;
	int nvertexes = mygraph->total_vertexes;

	//calcula o grau de cada vertice
	for(i = 0; i < nvertexes; i++)
	{
		for(j = 0; j < nvertexes; j++)
		{
			if(mygraph->edge[i][j] != 0 &&
					mygraph->edge[i][j] != INT_MAX)
			{
				mygraph_info->degree[j]++;

			}


		}
	}

}

void graph_mat_adj_print_info(INFO_VERTEXES *mygraph_info)
{
	int i;
	int total_vertexes = mygraph_info->total;

	printf("Printing Info (for each vertex) ...\n");

	for(i = 0; i < total_vertexes; i++)
	{
		printf("vertex: %d\nDegree: %d\n\n", i, mygraph_info->degree[i]);


	}



}

void graph_mat_adj_info_destroy(INFO_VERTEXES *my_vertexinfo)
{
	free(my_vertexinfo->degree);
	free(my_vertexinfo->coefagrup);
	free(my_vertexinfo);

}

/*
 * kcore.c
 *
 *  Created on: Jun 7, 2013
 *      Author: emanuel
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph_mat_adj.h"
#include "kcore.h"

vkcore_t * vkcore_init(INFO_VERTEXES *mygraph_info)
{
	vkcore_t *myvkcore;
	int i;
	int total_vertexes = mygraph_info->total;

	myvkcore = (vkcore_t*)malloc(sizeof(vkcore_t) * total_vertexes);

	for(i = 0; i < total_vertexes; i++)
	{
		myvkcore[i].vertex = i;
		myvkcore[i].degree = mygraph_info->degree[i];
	}

	return myvkcore;


}

void vkcore_calc_for_all_vertexes(vkcore_t *myvkcore, GRAPH_MAT_ADJ *mygraph)
{
	int i, j;
	int total_vertexes;
	int index_mygraph;

	total_vertexes = mygraph->total_vertexes;

	//primeira ordenacao (usamos qsort)
	qsort(myvkcore, total_vertexes, sizeof(vkcore_t), compare_vkcore_qsort);


	for(i = 0; i < total_vertexes; i++)
	{
		//laco reponsável por cada
		//vertice adjacente
		index_mygraph = vkcore_index_kcore_to_index_graph(i, myvkcore);
		for(j = 0; j < total_vertexes; j++)
		{

			//testa se há uma aresta entre o vertice i e j
			if(mygraph->edge[index_mygraph][j] < INT_MAX && mygraph->edge[index_mygraph][j] > 0)
			{

				//aqui garanto que há uma aresta entre o vertice i e j
				if(vkcore_test_degree(myvkcore, mygraph->vertex[j], mygraph->vertex[index_mygraph], total_vertexes) == 1)
				{
					//decrementa um grau no vetice j
					vkcore_dec_degree(myvkcore, mygraph->vertex[j], total_vertexes);

					//reordena
					vkcore_insertion_sort(myvkcore, total_vertexes);
					//vkcore_print(myvkcore, total_vertexes);

				}


			}

		}

	}


}



void vkcore_insertion_sort(vkcore_t *myvkcore, int total_vertexes)
{
	int i, j;
	vkcore_t tmp;

	for(i = 1; i < total_vertexes; i++)
	{
		j = i;

		while((j != 0) && (myvkcore[j].degree < myvkcore[j-1].degree))
		{

			tmp.degree = myvkcore[j].degree;
			tmp.vertex = myvkcore[j].vertex;

			myvkcore[j].vertex = myvkcore[j-1].vertex;
			myvkcore[j].degree = myvkcore[j-1].degree;

			myvkcore[j-1].vertex = tmp.vertex;
			myvkcore[j-1].degree = tmp.degree;

			j--;
		}
	}

}
int vkcore_index_kcore_to_index_graph(int index_kcore, vkcore_t *myvkcore)
{

	return myvkcore[index_kcore].vertex;

}
//testa se grau de  mygraph->vertex[i] > mygraph->vertex[j]
int vkcore_test_degree(vkcore_t * myvkcore, int vertex_a, int vertex_b, int total_vertexes)
{
	int k, index_a, index_b;

	for(k = 0; k < total_vertexes; k++)
	{
		if(myvkcore[k].vertex == vertex_a) index_a = k;
		if(myvkcore[k].vertex == vertex_b) index_b = k;

	}

	if(myvkcore[index_a].degree > myvkcore[index_b].degree) return 1;
	else return 0;


}

void vkcore_dec_degree(vkcore_t * myvkcore, int vertex, int total_vertexes)
{
	int k, index_vertex;

	for(k = 0; k < total_vertexes; k++)
	{
		if(myvkcore[k].vertex == vertex)
			index_vertex = k;

	}


	myvkcore[index_vertex].degree--;

}


int compare_vkcore_qsort(void const *a, void const *b)
{

	if( ((vkcore_t*)a)->degree > ((vkcore_t*)b)->degree) return 1;
	else return 0;

}

void vkcore_print(vkcore_t *myvkcore, int length)
{
	int i;

	printf("Printing vkcore vector..\n");

	for(i = 0; i < length; i++)
	{
		printf("vertex: %d degree: %d\n", myvkcore[i].vertex, myvkcore[i].degree);
	}

}

void vkcore_destroy(vkcore_t *myvkcore)
{
	free(myvkcore);
}



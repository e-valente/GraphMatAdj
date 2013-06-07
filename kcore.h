/*
 * kcore.h
 *
 *  Created on: Jun 7, 2013
 *      Author: emanuel
 */

#ifndef KCORE_H_
#define KCORE_H_

#include "graph_mat_adj.h"
typedef struct
{
	int vertex;
	int degree;

}vkcore_t;

vkcore_t * vkcore_init(INFO_VERTEXES *mygraph_info);
void vkcore_destroy(vkcore_t *myvkcore);

void vkcore_calc_for_all_vertexes(vkcore_t *myvkcore, GRAPH_MAT_ADJ *mygraph);
int compare_vkcore_qsort(void const *a, void const *b);
int vkcore_index_kcore_to_index_graph(int index_kcore, vkcore_t *myvkcore);
int vkcore_test_degree(vkcore_t * myvkcore, int vertex_a, int vertex_b, int total_vertexes);
void vkcore_dec_degree(vkcore_t * myvkcore, int vertex, int total_vertexes);
void vkcore_print(vkcore_t *myvkcore, int length);

void vkcore_insertion_sort(vkcore_t *myvkcore, int total_vertexes);


#endif /* KCORE_H_ */

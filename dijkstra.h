/*
 * dijkstra.h
 *
 *  Created on: May 20, 2013
 *      Author: emanuel
 */

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "graph_mat_adj.h"
#include "aux_vector.h"

void dijkstra(GRAPH_MAT_ADJ *mygraph, int posvertex_ini, aux_vector_t* my_auxvector);
void dijkstra_init(GRAPH_MAT_ADJ *mygraph, aux_vector_t* my_auxvector);
void dijkstra_travel_tree(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);

//lab3 exer1
int dijkstra_travel_tree_and_return_min_cost(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);



#endif /* DIJKSTRA_H_ */

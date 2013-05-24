/*
 * prim.h
 *
 *  Created on: May 23, 2013
 *      Author: emanuel
 */

#ifndef PRIM_H_
#define PRIM_H_

#include "graph_mat_adj.h"
#include "aux_vector.h"

void prim(GRAPH_MAT_ADJ *mygraph, int posvertex_ini, aux_vector_t* my_auxvector);
void prim_init(GRAPH_MAT_ADJ *mygraph, aux_vector_t* my_auxvector);
void prim_travel_tree(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);

int prim_travel_tree_and_return_min_cost(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);
int prim_travel_tree_and_return_max_cost(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);

#endif /* PRIM_H_ */

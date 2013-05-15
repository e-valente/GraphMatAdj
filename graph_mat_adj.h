/*
 * graph_mat_adj.h
 *
 *  Created on: May 15, 2013
 *      Author: emanuel
 */

#ifndef GRAPH_MAT_ADJ_H_
#define GRAPH_MAT_ADJ_H_

typedef struct _graph {
	int *vertex;
	int **edge;
	int total_vertexes;
	int total_edges;
}GRAPH_MAT_ADJ;


GRAPH_MAT_ADJ* graph_mat_adj_init(int total_vertexes);
void graph_mat_adj_destroy(GRAPH_MAT_ADJ *graph);
void graph_mat_adj_print_vertexes(GRAPH_MAT_ADJ *mygraph);

void graph_mat_adj_print_edges(GRAPH_MAT_ADJ *mygraph);
void graph_mat_adj_insert_vertex(GRAPH_MAT_ADJ *mygraph, int pos, int value);
void graph_mat_adj_insert_edge(GRAPH_MAT_ADJ *mygraph, int src, int dst, int weight);


#endif /* GRAPH_MAT_ADJ_H_ */

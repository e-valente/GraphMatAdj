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

typedef struct {
	int total;
	int *degree;
	double *coefagrup;
}INFO_VERTEXES;


GRAPH_MAT_ADJ* graph_mat_adj_init(int total_vertexes);
void graph_mat_adj_destroy(GRAPH_MAT_ADJ *graph);
void graph_mat_adj_print_vertexes(GRAPH_MAT_ADJ *mygraph);
INFO_VERTEXES* graph_mat_adj_info_init(GRAPH_MAT_ADJ *mygraph);
void graph_mat_adj_print_info(INFO_VERTEXES *mygraph_info);
void graph_mat_adj_info_destroy(INFO_VERTEXES *my_vertexinfo);
int is_adj(GRAPH_MAT_ADJ *mygraph, int src_pos_vertex, int dst_pos_vertex);

void graph_mat_adj_print_edges(GRAPH_MAT_ADJ *mygraph);
void graph_mat_adj_insert_vertex(GRAPH_MAT_ADJ *mygraph, int pos, int value);
void graph_mat_adj_insert_edge(GRAPH_MAT_ADJ *mygraph, int src, int dst, int weight);

void graph_mat_adj_calc_degrees(GRAPH_MAT_ADJ *mygraph, INFO_VERTEXES *mygraph_info);


#endif /* GRAPH_MAT_ADJ_H_ */

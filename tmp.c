/*
 * tmp.c
 *
 *  Created on: May 24, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

typedef struct _graph {
	int *vertex;
	int **edge;
	int total_vertexes;
	int total_edges;
}GRAPH_MAT_ADJ;

typedef struct aux_vector_t
{
	int *vertex;
	int *cost;
	int *predec;
	int *isvalid;
	int *min_cost;

	int total;

}aux_vector_t;



GRAPH_MAT_ADJ* graph_mat_adj_init(int total_vertexes);
void graph_mat_adj_destroy(GRAPH_MAT_ADJ *graph);
void graph_mat_adj_print_vertexes(GRAPH_MAT_ADJ *mygraph);

void graph_mat_adj_print_edges(GRAPH_MAT_ADJ *mygraph);
void graph_mat_adj_insert_vertex(GRAPH_MAT_ADJ *mygraph, int pos, int value);
void graph_mat_adj_insert_edge(GRAPH_MAT_ADJ *mygraph, int src, int dst, int weight);



aux_vector_t *aux_vector_init(int total);
void aux_vector_destroy(aux_vector_t *my_auxvector);

void aux_vector_addvertex(aux_vector_t *my_auxvector, int pos, int value);
void aux_vector_addcost(aux_vector_t *my_auxvector, int pos, int value);
void aux_vector_addpredec(aux_vector_t *my_auxvector, int pos, int value);
void aux_vector_addmincost(aux_vector_t *my_auxvector, int pos, int value);
int aux_vector_getmincost(aux_vector_t *my_auxvector);

void aux_vector_updatecost_dijkstra(aux_vector_t *my_auxvector, GRAPH_MAT_ADJ *mygraph, int pos);
void aux_vector_updatecost_prim(aux_vector_t *my_auxvector, GRAPH_MAT_ADJ *mygraph, int pos);
int aux_vector_calcmincost(aux_vector_t *my_auxvector);
void aux_vector_print(aux_vector_t *my_auxvector);
void aux_vector_update_predec(aux_vector_t *my_auxvector, int pos_predec, int pos_vertex);
void aux_vector_update_isvalid(aux_vector_t *my_auxvector, int pos, int value);
int aux_vector_next_insert_on_tree(aux_vector_t *my_auxvector,int *pos_parent_on_tree, int *pos_child_on_tree);
int my_auxvector_travel_tree(GRAPH_MAT_ADJ *mygraph, aux_vector_t * my_auxvector, int pos_start, int pos_end);
int aux_vector_has_valid_elems(aux_vector_t * my_auxvector);

//lab3 exer1
int my_auxvector_travel_tree_and_return_min_cost_dijkstra(GRAPH_MAT_ADJ *mygraph, aux_vector_t * my_auxvector, int pos_start, int pos_end);
int my_auxvector_travel_tree_and_return_max_cost_prim(GRAPH_MAT_ADJ *mygraph, aux_vector_t * my_auxvector, int pos_start, int pos_end);

void prim(GRAPH_MAT_ADJ *mygraph, int posvertex_ini, aux_vector_t* my_auxvector);
void prim_init(GRAPH_MAT_ADJ *mygraph, aux_vector_t* my_auxvector);
void prim_travel_tree(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);

int prim_travel_tree_and_return_min_cost(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);
int prim_travel_tree_and_return_max_cost(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end);

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

	memset(mygraph->vertex, 0, total_vertexes * sizeof(int));


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


aux_vector_t *aux_vector_init(int total)
{
	aux_vector_t *my_auxvector;

	my_auxvector = (aux_vector_t*)malloc(sizeof(aux_vector_t));

	my_auxvector->total = total;

	my_auxvector->vertex = (int*)malloc(sizeof(int) * total);
	my_auxvector->cost = (int*)malloc(sizeof(int) * total);
	my_auxvector->predec = (int*)malloc(sizeof(int) * total);
	my_auxvector->isvalid = (int*)malloc(sizeof(int) * total);
	my_auxvector->min_cost = (int*)malloc(sizeof(int) * total);

	return my_auxvector;
}

void aux_vector_destroy(aux_vector_t *my_auxvector)
{
	free(my_auxvector->vertex);
	free(my_auxvector->cost);
	free(my_auxvector->predec);
	free(my_auxvector->isvalid);
	free(my_auxvector->min_cost);

	free(my_auxvector);


}

void aux_vector_addvertex(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->vertex[pos] = value;
	my_auxvector->isvalid[pos] = 1;
}

void aux_vector_addcost(aux_vector_t *my_auxvector, int pos, int value)
{
	if(value != 0)
		my_auxvector->cost[pos] += value;

	else my_auxvector->cost[pos] = value;

}

void aux_vector_addmincost(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->min_cost[pos] = value;
}


int aux_vector_calcmincost(aux_vector_t *my_auxvector)
{
	int i, min_pos, min_cost;
	int lastpos_mincost;


	//precisamos primeiro zerar o mincost atual
	i = aux_vector_getmincost(my_auxvector);
	if(i >= 0)  {
		//bk, necessario para
		//caso o grafo seja desconectado
		//temos que voltar essa posicao
		lastpos_mincost = i;
		//limpa
		my_auxvector->min_cost[i] = 0;
	}


	i = 0;
	min_cost = 0;




	do{
		if(my_auxvector->isvalid[i] == 1){
			min_cost = my_auxvector->cost[i];
			min_pos = i;

		}
		i++;
	}while(min_cost == 0);



	for(i = 0; i < my_auxvector->total; i++)
	{
		if(my_auxvector->cost[i] < min_cost &&
				my_auxvector->cost[i] != 0 &&
				my_auxvector->isvalid[i] == 1)
		{
			min_cost = my_auxvector->cost[i];
			min_pos = i;
		}

	}

	//se custo é infinito chegamos ao
	//fim (grafo desconectado)
	if(min_cost == INT_MAX)
	{
		//volta a posicao antiga
		my_auxvector->min_cost[lastpos_mincost] = 1;
		return -1;

	}

	my_auxvector->min_cost[min_pos] = 1;

	return min_pos;
}


void aux_vector_update_predec(aux_vector_t *my_auxvector, int pos_vertex, int pos_predec)
{
	my_auxvector->predec[pos_vertex] = pos_predec;


}

void aux_vector_update_isvalid(aux_vector_t *my_auxvector, int pos, int value)
{
	my_auxvector->isvalid[pos] = value;


}

int aux_vector_getmincost(aux_vector_t *my_auxvector)
{
	int i;

	for(i = 0; i < my_auxvector->total; i++)
	{
		if(my_auxvector->min_cost[i] == 1)
			return i;

	}


	return -1;
}

void aux_vector_updatecost_dijkstra(aux_vector_t *my_auxvector, GRAPH_MAT_ADJ *mygraph, int pos)
{
	//temos que procurar com quem
	//o elemento atual faz arestas
	//ecoar seus pesos e atualizar se necessario
	//o vetor de custo

	int i;

	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		//pra ter uma aresta nao pode ser zero e nao pode ser infinito
		if(mygraph->edge[pos][i] > 0 && mygraph->edge[pos][i] < INT_MAX)
		{

			if (my_auxvector->cost[i] > my_auxvector->cost[pos] + mygraph->edge[pos][i] &&
					my_auxvector->cost[pos] != INT_MAX) {

				my_auxvector->cost[i] = my_auxvector->cost[pos] + mygraph->edge[pos][i];


			}

			//atualiza tambem o predec
			// i-> vertice atual visitado ; pos-> quem esta visitando (predec)
			if(my_auxvector->cost[i] != 0) aux_vector_update_predec(my_auxvector, i , pos);

		}

	}

}

void aux_vector_updatecost_prim(aux_vector_t *my_auxvector, GRAPH_MAT_ADJ *mygraph, int pos)
{
	//temos que procurar com quem
	//o elemento atual faz arestas
	//ecoar seus pesos e atualizar se necessario
	//o vetor de custo

	int i;

	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		//pra ter uma aresta nao pode ser zero e nao pode ser infinito
		if(mygraph->edge[pos][i] > 0 && mygraph->edge[pos][i] < INT_MAX)
		{

			if (my_auxvector->cost[i] > mygraph->edge[pos][i] &&
					my_auxvector->cost[pos] != INT_MAX) {

				my_auxvector->cost[i] = my_auxvector->cost[pos] + mygraph->edge[pos][i];


			}

			//atualiza tambem o predec
			// i-> vertice atual visitado ; pos-> quem esta visitando (predec)
			if(my_auxvector->cost[i] != 0) aux_vector_update_predec(my_auxvector, i , pos);

		}

	}

}


int aux_vector_next_insert_on_tree(aux_vector_t *my_auxvector,int *pos_parent_on_tree, int *pos_child_on_tree)
{
	int i;

	for(i = 0; i < my_auxvector->total; i++)
	{
		if(my_auxvector->min_cost[i] == 1)
		{
			*pos_parent_on_tree = my_auxvector->predec[i];
			*pos_child_on_tree = my_auxvector->vertex[i];

		}
	}

	return -1;

}

int my_auxvector_travel_tree(GRAPH_MAT_ADJ *mygraph, aux_vector_t * my_auxvector, int pos_start, int pos_end)
{
	int pos_vertex, pos_predec;
	int total, control;

	total = my_auxvector->total;

	//verifica range válido das posicoes
	if(pos_start < 0 || pos_end < 0 || pos_start >= total ||
			pos_end >= total || (pos_end - pos_start < 0))
	{
		fprintf(stderr, "\nmy_auxvector_travel_tree: Invalid range!\n");
		return -1;

	}

	pos_vertex = pos_end;
	pos_predec = my_auxvector->predec[pos_vertex];

	//usada pra caso tivermos um vetor
	//aux mal formado
	control = 0;

	while(pos_vertex != pos_start && control < 100)
	{
		/*
		printf("passando de %d a %d com custo: %d\n",my_auxvector->vertex[pos_predec],
				my_auxvector->vertex[pos_vertex], mygraph->edge[pos_predec][pos_vertex]);
		 */
		pos_vertex = pos_predec;
		pos_predec = my_auxvector->predec[pos_vertex];

		control++;

	}

	//caso der overflow
	//vetor aux mal formado, avisaremos
	if(control >= 100)
	{
		fprintf(stderr, "\nmy_auxvector_travel_tree: Overflow, bad aux vector!\n");
		return -1;
	}


	return 0;
}

int my_auxvector_travel_tree_and_return_min_cost_dijkstra(GRAPH_MAT_ADJ *mygraph, aux_vector_t * my_auxvector, int pos_start, int pos_end)
{

	return my_auxvector->cost[pos_end];

}




int my_auxvector_travel_tree_and_return_max_cost_prim(GRAPH_MAT_ADJ *mygraph, aux_vector_t * my_auxvector, int pos_start, int pos_end)
{

	int pos_vertex, pos_predec;
	int max_cost, control;


	pos_vertex = pos_end;
	pos_predec = my_auxvector->predec[pos_vertex];
	max_cost = -1;

	//usada pra caso tivermos um vetor
	//aux mal formado
	control = 0;

	while(pos_vertex != pos_start && pos_predec != -1 && control < 100)
	{
		/*
			printf("passando de %d a %d com custo: %d\n",my_auxvector->vertex[pos_predec],
					my_auxvector->vertex[pos_vertex], mygraph->edge[pos_predec][pos_vertex]);
		 */
		//printf("max cost vale %d\n", max_cost);
		if(max_cost < mygraph->edge[pos_predec][pos_vertex])
		{
			max_cost = mygraph->edge[pos_predec][pos_vertex];

		}
		pos_vertex = pos_predec;
		pos_predec = my_auxvector->predec[pos_vertex];


		control++;

	}

	//caso der overflow
	//vetor aux mal formado, avisaremos
	if(control >= 100)
	{
		fprintf(stderr, "\nmy_auxvector_travel_tree: Overflow, bad aux vector!\n");
		return -1;
	}


	return max_cost;

}

int aux_vector_has_valid_elems(aux_vector_t * my_auxvector)
{
	int i;


	//se tiver 1 elemento setado
	//o vetor ainda é valido
	for(i = 0; i < my_auxvector->total; i++)
	{
		if(my_auxvector->isvalid[i] == 1) return 1;

	}


	return 0;
}
void aux_vector_print(aux_vector_t *my_auxvector)
{
	int i;
	printf("Printing aux vector...\n\n");

	printf("Printing vertexes...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->vertex[i]);

	}

	printf("\n");

	printf("Printing costs...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->cost[i]);

	}

	printf("\n");

	printf("Printing predecs...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->predec[i]);

	}

	printf("\n");


	printf("Printing isvalid?...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->isvalid[i]);

	}

	printf("\n");

	printf("Printing mincost...\n");

	for(i = 0; i < my_auxvector->total; i++)
	{
		printf("%d ", my_auxvector->min_cost[i]);

	}


	printf("\n");



}

void prim(GRAPH_MAT_ADJ *mygraph, int posvertex_ini, aux_vector_t* my_auxvector)
{
	int i;
	int pos, pos_parent_on_tree, pos_child_on_tree;
	//preenche o vetor de predec
	prim_init(mygraph, my_auxvector);



	for(i = 0; i < mygraph->total_vertexes; i++)
	{
		//ecoar p/ aux vector
		aux_vector_addcost(my_auxvector, i, mygraph->edge[posvertex_ini][i]);
		aux_vector_update_predec(my_auxvector, i, -1);



	}


	//insiro o primeiro elemento na árvore
	pos = posvertex_ini;
	aux_vector_update_isvalid(my_auxvector, pos, 0);

	while(aux_vector_has_valid_elems(my_auxvector) == 1 && pos != -1)
	{
		//insere segundo elemento
		//pos -> será o primeiro elemento
		aux_vector_updatecost_prim(my_auxvector, mygraph, pos);
		pos = aux_vector_calcmincost(my_auxvector);

		if(pos != -1){
			aux_vector_next_insert_on_tree(my_auxvector, &pos_parent_on_tree, &pos_child_on_tree);
			aux_vector_update_isvalid(my_auxvector, pos, 0);

		}


	}

}

void prim_init(GRAPH_MAT_ADJ *mygraph, aux_vector_t* my_auxvector)
{
	int i;
	int total = mygraph->total_vertexes;

	for(i = 0; i < total; i++)
	{
		aux_vector_addvertex(my_auxvector, i, mygraph->vertex[i]);
		aux_vector_addcost(my_auxvector, i, 0);
		aux_vector_update_predec(my_auxvector, i, -1);
		aux_vector_addmincost(my_auxvector, i, 0);


	}

}

void prim_travel_tree(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end)
{
	my_auxvector_travel_tree(mygraph, my_auxvector, pos_start, pos_end);
}



int prim_travel_tree_and_return_max_cost(GRAPH_MAT_ADJ *mygraph, aux_vector_t *my_auxvector, int pos_start, int pos_end)
{
	return my_auxvector_travel_tree_and_return_max_cost_prim(mygraph, my_auxvector, pos_start, pos_end);

}


int main(int argc, char *argv[])
{
	GRAPH_MAT_ADJ *mygraph;
	aux_vector_t *my_auxvector;

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
	prim(mygraph, 0, my_auxvector);

	for(i = 0; i< trips; i++)
	{
		scanf("%d %d", &src_vertex, &dst_vertex);

		max_cost = prim_travel_tree_and_return_max_cost(mygraph, my_auxvector, src_vertex, dst_vertex);

		if(max_cost < 0 || max_cost == INT_MAX)
			printf("no path\n");
		else printf("%d\n", max_cost);


	}

	aux_vector_print(my_auxvector);
	graph_mat_adj_print_edges(mygraph);



	//destroy graph and aux vector
	graph_mat_adj_destroy(mygraph);
	aux_vector_destroy(my_auxvector);

	return 0;
}


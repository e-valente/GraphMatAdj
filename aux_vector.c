/*
 * aux_vector_t.c
 *
 *  Created on: May 19, 2013
 *      Author: emanuel
 */


#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph_mat_adj.h"
#include "aux_vector.h"

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
		if(mygraph->edge[pos][i] > 0 && mygraph->edge[pos][i] < INT_MAX && my_auxvector->isvalid[i] == 1)
		{

			if (my_auxvector->cost[i] > my_auxvector->cost[pos] + mygraph->edge[pos][i] &&
					my_auxvector->cost[pos] != INT_MAX) {

				my_auxvector->cost[i] = my_auxvector->cost[pos] + mygraph->edge[pos][i];


			}

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
		if(mygraph->edge[pos][i] > 0 && mygraph->edge[pos][i] < INT_MAX && my_auxvector->isvalid[i] == 1)
		{

			if (my_auxvector->cost[i] > mygraph->edge[pos][i] ) {

				my_auxvector->cost[i] =  mygraph->edge[pos][i];
				aux_vector_update_predec(my_auxvector, i , pos);



			}

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
		//fprintf(stderr, "\nmy_auxvector_travel_tree: Overflow, bad aux vector!\n");
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


	if(pos_end == pos_start ) return 0;


	pos_vertex = pos_end;
	pos_predec = my_auxvector->predec[pos_vertex];
	max_cost = -1;

	//usada pra caso tivermos um vetor
	//aux mal formado
	control = 0;


	while(pos_vertex != pos_start && control < 100)
	{

			/*
			printf("passando de %d a %d com custo: %d\n",my_auxvector->vertex[pos_predec],
					my_auxvector->vertex[pos_vertex], my_auxvector->cost[pos_vertex]);
			*/

		//printf("max cost vale %d\n", max_cost);
		if(max_cost < my_auxvector->cost[pos_vertex])
		{
			//max_cost = mygraph->edge[pos_predec][pos_vertex];
			max_cost = my_auxvector->cost[pos_vertex];

		}
		pos_vertex = pos_predec;
		pos_predec = my_auxvector->predec[pos_vertex];


		control++;

	}

	//caso der overflow
	//vetor aux mal formado, avisaremos
	if(control >= 100)
	{
		//fprintf(stderr, "\nmy_auxvector_travel_tree: Overflow, bad aux vector!\n");
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

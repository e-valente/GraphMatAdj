/*
 * tree.c
 *
 *  Created on: May 19, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "tree.h"

Tree *buildTree()
{
	Tree *mytree;

	mytree = (Tree*)malloc(sizeof(Tree));

	mytree->root = NULL;

	return mytree;


}


int insertOnTree(Tree *mytree, int parent, int value)
{
	/*******
	 * Quando a árvore nao tem raiz e parent vale -1
	 */
	if(mytree->root == NULL && parent == -1)
	{
		//insere raiz
		Node *mynode;
		mynode = (Node*)malloc(sizeof(Node));
		mynode->value = value;
		mynode->left = NULL;
		mynode->right = NULL;

		mytree->root = mynode;

		return 1;

	}

	/*******
	 * Quando a árvore nao tem raiz
	 * insere raiz e filho
	 */
	if(mytree->root == NULL && parent > 0)
	{
		//insere raiz
		Node *mynode_parent;
		mynode_parent = (Node*)malloc(sizeof(Node));
		mynode_parent->value = parent;
		mynode_parent->left = NULL;
		mynode_parent->right = NULL;

		mytree->root = mynode_parent;

		//insere nó filho
		Node *mynode_child;
		mynode_child = (Node*)malloc(sizeof(Node));
		mynode_child->value = value;
		mynode_child->left = NULL;
		mynode_child->right = NULL;


		//nó pai deve apontar para o filho
		mytree->root->left = mynode_child;

		return 1;

	}




	/*******
	 * Quando a árvore tem raiz
	 * mas deseja que a insercao seja
	 * um nó filho da raiz	 */

	if(mytree->root != NULL && mytree->root->value == parent)
	{
		//insere nó filho
		Node *mynode_child;
		mynode_child = (Node*)malloc(sizeof(Node));
		mynode_child->value = value;


		//ja tinha nó filho da raiz da arvore?
		//verificando nó da esquerda
		if(mytree->root->left == NULL)
		{
			mynode_child->left = NULL;
			mynode_child->right = NULL;

			mytree->root->left = mynode_child;

			return 1;



		}



		//ja tinha nó filho da raiz da arvore?
		//verificando nó da esquerda
		if(mytree->root->right == NULL)
		{
			mynode_child->left = NULL;
			mynode_child->right = NULL;

			mytree->root->right = mynode_child;

			return 1;



		}
		//caso o nó da direita tenha filho
		//inserimnos no nó da esquerda
		//temos que verificar se o nó da esquerda tem filho
		else
		{
			//se nó da esquerda tem filho
			if(mytree->root->left != NULL)
			{
				//printf("inserindo %d apagando %d\n", value, mytree->root->left->value);
				mynode_child->left = mytree->root->left;
				mynode_child->right = NULL;

				mytree->root->left = mynode_child;

				return 1;
			}

			//se nó da esquerda nao tem filho
			else
			{
				mynode_child->left = NULL;
				mynode_child->right = NULL;

				mytree->root->left = mynode_child;

				return 1;

			}

		}

	}


	/**
	 * Isercao abaixo dos nós filhos da raiz
	 */

	//procura pai
	Node *mynode_parent;

	mynode_parent = searchValueOnTree(mytree->root, parent);

	if(mynode_parent != NULL)
	{
		Node *mynode_child;
		mynode_child = (Node*)malloc(sizeof(Node));
		mynode_child->value = value;

		//tem o nó tem filhos?
		//verificamos prmeiro no nó
		//da esquerda. Caso nao esteja livre,
		//verificamos o da direita, caso
		//da direita esteja ocupado
		//inserimos na esquerda (de qquer modo)



		//verifica esquerda

		if(mynode_parent->left == NULL)
		{
			mynode_child->left = NULL;
			mynode_child->right = NULL;

			//insere
			mynode_parent->left = mynode_child;

			return 1;

		}

		//esquerda com filho,
		//mas direita livre
		else
		{
			if(mynode_parent->right == NULL)
			{
				mynode_child->left = NULL;
				mynode_child->right = NULL;

				//insere
				mynode_parent->right = mynode_child;

				return 1;

			}


			//direita nao livre,
			//entao inserimos na esquerda
			else
			{
				mynode_child->left = mynode_parent->left;
				mynode_child->right = NULL;

				//insere
				mynode_parent->left = mynode_child;

				return 1;

			}

		}
	}

	return 1;
}


void printInOrder(Node *nodeRoot)
{
	if(nodeRoot != NULL)
	{
		printInOrder(nodeRoot->left);

		printf("%d \n", nodeRoot->value);

		printInOrder(nodeRoot->right);
	}

}

Node* searchValueOnTree(Node *nodeRoot, int value)
{
	if(nodeRoot!= NULL)
	{
		if(nodeRoot->value == value)
		{
			printf("achei retornando com valor  %d\n", nodeRoot->value);
			return nodeRoot;
		}

		Node *mynode;
		mynode = searchValueOnTree(nodeRoot->left, value);

		if(mynode != NULL)
		{
			printf("retornando com valor %d\n", mynode->value);
			return mynode;
		}
		else {
			mynode = searchValueOnTree(nodeRoot->right, value);
			if(mynode != NULL)
			{
				printf("retornando com valor %d\n", mynode->value);
				return mynode;

			}
		}
	}


	return NULL;

}


void destroyTree(Tree *mytree)
{
	if(mytree->root != NULL) {
		destroyTreeNodes(mytree->root);

		free(mytree);
	}
}

void destroyTreeNodes(Node *mynode)
{
	if(mynode->left != NULL)
		destroyTreeNodes(mynode->left);

	if(mynode->right != NULL)
		destroyTreeNodes(mynode->right);

	free(mynode);

}


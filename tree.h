/*
 * tree.h
 *
 *  Created on: May 19, 2013
 *      Author: emanuel
 */

#ifndef TREE_H_
#define TREE_H_


typedef struct Node {

	int value;
	struct Node *left;
	struct Node *right;

} Node;

typedef struct Tree{
	struct Node *root;
}Tree;

Tree *buildTree();
int insertOnTree(Tree *mytree, int parent, int value);
void printInOrder(Node *nodeRoot);
Node* searchValueOnTree(Node *nodeRoot, int value);

void destroyTree(Tree*);
void destroyTreeNodes(Node*);


#endif /* TREE_H_ */

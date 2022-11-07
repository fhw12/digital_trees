#include <stdlib.h>
#include "trees.h"

NodeTree *first_node_tree;

NodeTree *node_tree_init(){
	first_node_tree = malloc(sizeof(NodeTree));
	first_node_tree->next = 0;

	return first_node_tree;
}

NodeTree *new_node_tree(NodeTree* ptr){
	if(ptr != 0){
		while(ptr->next != 0){
			ptr = ptr->next;
		}
	}

	ptr->next = malloc(sizeof(NodeTree));
	ptr = ptr->next;
	ptr->next = 0;
	ptr->energy = 0;

	return ptr;
}

void delete_node_tree(NodeTree* ptr, NodeTree* delete_ptr){
	if(ptr != 0){
		while(ptr->next != delete_ptr){
			ptr = ptr->next;
		}
	}

	if(delete_ptr->next != 0){
		ptr->next = delete_ptr->next;
	}else{
		ptr->next = 0;
	}

	free(delete_ptr);
}
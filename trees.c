#include <stdlib.h>
#include "trees.h"

NodeTree *first_node_tree;

NodeTree *node_tree_init(){
	first_node_tree = malloc(sizeof(NodeTree));
	first_node_tree->next = 0;
	first_node_tree->life_days = 0;
	first_node_tree->max_life_days = 0;

	return first_node_tree;
}

NodeTree *new_node_tree(NodeTree *ptr){
	//if(ptr != 0){
	while(ptr->next != 0){
		ptr = ptr->next;
	}
	//}

	ptr->next = malloc(sizeof(NodeTree));
	ptr = ptr->next;
	ptr->next = 0;

	return ptr;
}

NodeTree *create_tree(NodeTree *ptr, NodeTree *parent){
	ptr = new_node_tree(ptr);

	ptr->energy = 300;
	ptr->life_days = 0;
	ptr->max_life_days = 95 + rand() % 11; // [95; 105]

	if(parent == 0){
		for(int i = 0; i < 16; i++){
			for(int j = 0; j < 4; j++){
				ptr->genom[i][j] = rand() % 32;
			}
		}
	}else{
		for(int i = 0; i < 16; i++){
			for(int j = 0; j < 4; j++){
				if(rand() % 100 == 0){
					ptr->genom[i][j] = rand() % 32;
				}else{
					ptr->genom[i][j] = parent->genom[i][j];
				}
			}
		}
	}

	return ptr;
}

void delete_node_tree(NodeTree *ptr, NodeTree *delete_ptr){
	//if(ptr != 0){
		while(ptr->next != delete_ptr){
			ptr = ptr->next;
		}
	

		if(delete_ptr->next != 0){
			ptr->next = delete_ptr->next;
		}else{
			ptr->next = 0;
		}
		
		free(delete_ptr);
	//}
}
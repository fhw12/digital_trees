typedef struct node_tree {
	int genom[16][4];
	int energy;
	int life_days;
	int max_life_days;
	struct node_tree *next;
} NodeTree;


NodeTree *node_tree_init();
NodeTree *new_node_tree(NodeTree* ptr);
void delete_node_tree(NodeTree* ptr, NodeTree* delete_ptr);
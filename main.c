#include <stdio.h>
#include "raylib.h"

#include "trees.h"

const int WIDTH = 800, HEIGHT = 600;
const int SIZE = 5;
const int MAP_WIDTH = 160;
const int MAP_HEIGHT = 120;



int mx, my;

int main(){
	InitWindow(WIDTH, HEIGHT, "Digital Trees");

	NodeTree *map_points[MAP_WIDTH][MAP_HEIGHT];
	int map_trees[MAP_WIDTH][MAP_HEIGHT][2];

	NodeTree *map_points_buffer[MAP_WIDTH][MAP_HEIGHT];
	int map_trees_buffer[MAP_WIDTH][MAP_HEIGHT][2];
	
	NodeTree *tree_ptr;
	NodeTree *first_node_tree_ptr = node_tree_init();

	tree_ptr = create_tree(first_node_tree_ptr);

	tree_ptr = first_node_tree_ptr;
	if(tree_ptr != 0){
		while(tree_ptr->next){
			tree_ptr = tree_ptr->next;
			printf("energy: %d\n", tree_ptr->energy);
			printf("days: %d/%d\n", tree_ptr->life_days, tree_ptr->max_life_days);
			printf("genom:\n");
			for(int i = 0; i < 16; i++){
				printf("%d\t>\t", i);
				for(int j = 0; j < 4; j++){
					printf("%d ", tree_ptr->genom[i][j]);
				}
				printf("\n");
			}
		}
	}
	

	while(!WindowShouldClose()){
		mx = GetMouseX();
		my = GetMouseY();

		BeginDrawing();

		ClearBackground((Color){20, 20, 20, 255});
		DrawRectangle(5, 5, 100, 50, Fade(WHITE, 0.9f));
		DrawRectangleLines(5, 5, 100, 50, WHITE);
		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 10, BLACK);
		DrawText(TextFormat("mouse: (%d, %d)", mx, my), 10, 30, 10, BLACK);
		
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
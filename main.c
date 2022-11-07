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
	
	NodeTree *first_node_tree_ptr, *ptr, *ptr2;
	first_node_tree_ptr = node_tree_init();

	ptr = new_node_tree(first_node_tree_ptr);
	ptr->energy = 5;

	ptr2 = new_node_tree(first_node_tree_ptr);
	ptr2->energy = 10;

	ptr = new_node_tree(first_node_tree_ptr);
	ptr->energy = 15;

	delete_node_tree(first_node_tree_ptr, ptr2);
	ptr = first_node_tree_ptr;

	if(ptr != 0){
		while(ptr->next){
			printf("%d\n", ptr->energy);
			ptr = ptr->next;
		} printf("%d\n", ptr->energy);
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
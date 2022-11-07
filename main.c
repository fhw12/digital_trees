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
	map_trees[80][110][0] = 1;
	map_trees[80][110][1] = 0;
	map_points[80][110] = tree_ptr;

	/*
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
	*/

	while(!WindowShouldClose()){
		mx = GetMouseX();
		my = GetMouseY();

		BeginDrawing();

		ClearBackground((Color){20, 20, 20, 255});
		DrawRectangle(5, 5, 100, 50, Fade(WHITE, 0.9f));
		DrawRectangleLines(5, 5, 100, 50, WHITE);
		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 10, BLACK);
		DrawText(TextFormat("mouse: (%d, %d)", mx, my), 10, 30, 10, BLACK);

		for(int x = 0; x < MAP_WIDTH; x++){
			for(int y = 0; y < MAP_HEIGHT; y++){
				if(map_trees[x][y][0] != 0){ // seed
					if(map_trees[x][y][0] == 1){
						DrawRectangle(x*SIZE, y*SIZE, SIZE, SIZE, (Color){255, 255, 255, 255});
					
						if(y + 1 < MAP_HEIGHT){
							map_trees_buffer[x][y+1][0] = 1;
							map_trees_buffer[x][y][0] = 0;

							map_points_buffer[x][y+1] = map_points[x][y];
							map_points_buffer[x][y] = 0;
						}else{
							map_trees_buffer[x][y][0] = 3; // seed -> sprout
						}
					} else if(map_trees[x][y][0] == 2){
						DrawRectangle(x*SIZE, y*SIZE, SIZE, SIZE, (Color){255, 255, 150, 255});
					} else if(map_trees[x][y][0] == 3){
						DrawRectangle(x*SIZE, y*SIZE, SIZE, SIZE, (Color){50, 255, 50, 255});
					}

					if(mx > x * SIZE && mx <= x * SIZE + SIZE && my > y * SIZE && my <= y * SIZE + SIZE){
						DrawText(TextFormat("type: %d", map_trees[x][y][0]), 10, 70, 10, LIGHTGRAY);
						DrawText(TextFormat("gen: %d", map_trees[x][y][1]), 10, 85, 10, LIGHTGRAY);
						DrawText(TextFormat("days: %d/%d", map_points[x][y]->life_days, map_points[x][y]->max_life_days), 10, 100, 10, LIGHTGRAY);

						for(int j = 0; j < 16; j++){
							if(j == map_trees[x][y][1]){
								DrawText(TextFormat("%d > ", j), 10, 120+j*20, 10, RED);
							}else{
								DrawText(TextFormat("%d > ", j), 10, 120+j*20, 10, LIGHTGRAY);
							}
							for(int i = 0; i < 4; i++){
								DrawText(TextFormat("%d", map_points[x][y]->genom[j][i]), 30+i*20, 120+j*20, 10, LIGHTGRAY);
							}
						}
					}

				}
			}
		}

		for(int x = 0; x < MAP_WIDTH; x++){
			for(int y = 0; y < MAP_HEIGHT; y++){
				map_trees[x][y][0] = map_trees_buffer[x][y][0];
				map_trees[x][y][1] = map_trees_buffer[x][y][1];
				map_points[x][y] = map_points_buffer[x][y];
			}
		}
		
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
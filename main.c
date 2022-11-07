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

	//SetTargetFPS(20);

	while(!WindowShouldClose()){
		mx = GetMouseX();
		my = GetMouseY();

		BeginDrawing();

		ClearBackground((Color){20, 20, 20, 255});
		

		for(int x = 0; x < MAP_WIDTH; x++){
			for(int y = 0; y < MAP_HEIGHT; y++){
				if(map_trees[x][y][0] != 0){ // seed
					map_trees_buffer[x][y][0] = map_trees[x][y][0];
					map_trees_buffer[x][y][1] = map_trees[x][y][1];
					map_points_buffer[x][y] = map_points[x][y];

					if(map_trees[x][y][0] == 1){ // seed
						DrawRectangle(x*SIZE, y*SIZE, SIZE, SIZE, (Color){255, 255, 255, 255});
					
						if(y + 1 < MAP_HEIGHT){
							map_trees_buffer[x][y+1][0] = 1;
							map_trees_buffer[x][y][0] = 0;

							map_points_buffer[x][y+1] = map_points[x][y];
							map_points_buffer[x][y] = 0;
						}else{
							map_trees_buffer[x][y][0] = 2; // seed -> sprout
						}
					} else if(map_trees[x][y][0] == 2){ // sprout
						DrawRectangle(x*SIZE, y*SIZE, SIZE, SIZE, (Color){255, 255, 150, 255});
	
						if(y - 1 > 0 && map_points[x][y]->genom[map_trees[x][y][1]][0] < 16){ // up
							if(map_trees[x][y-1][0] == 0){
								map_trees_buffer[x][y-1][0] = 2;
								map_trees_buffer[x][y-1][1] = map_points[x][y]->genom[map_trees[x][y][1]][0];
								map_points_buffer[x][y-1] = map_points[x][y];

								map_trees_buffer[x][y][0] = 3;
							}
						}

						if(y + 1 < MAP_HEIGHT && map_points[x][y]->genom[map_trees[x][y][1]][2] < 16){ // down
							if(map_trees[x][y+1][0] == 0){
								map_trees_buffer[x][y+1][0] = 2;
								map_trees_buffer[x][y+1][1] = map_points[x][y]->genom[map_trees[x][y][1]][2];
								map_points_buffer[x][y+1] = map_points[x][y];

								map_trees_buffer[x][y][0] = 3;
							}
						}

						if(x + 1 < MAP_WIDTH && map_points[x][y]->genom[map_trees[x][y][1]][1] < 16){ // right
							if(map_trees[x+1][y][0] == 0){
								map_trees_buffer[x+1][y][0] = 2;
								map_trees_buffer[x+1][y][1] = map_points[x][y]->genom[map_trees[x][y][1]][1];
								map_points_buffer[x+1][y] = map_points[x][y];

								map_trees_buffer[x][y][0] = 3;
							}
						}

						if(x - 1 >= 0 && map_points[x][y]->genom[map_trees[x][y][1]][3] < 16){ // left
							if(map_trees[x-1][y][0] == 0){
								map_trees_buffer[x-1][y][0] = 2;
								map_trees_buffer[x-1][y][1] = map_points[x][y]->genom[map_trees[x][y][1]][3];
								map_points_buffer[x-1][y] = map_points[x][y];

								map_trees_buffer[x][y][0] = 3;
							}
						}
						

					} else if(map_trees[x][y][0] == 3){ // tree
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

		DrawRectangle(5, 5, 100, 50, Fade(WHITE, 0.9f));
		DrawRectangleLines(5, 5, 100, 50, WHITE);
		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 10, BLACK);
		DrawText(TextFormat("mouse: (%d, %d)", mx, my), 10, 30, 10, BLACK);

		for(int x = 0; x < MAP_WIDTH; x++){
			for(int y = 0; y < MAP_HEIGHT; y++){

				map_trees[x][y][0] = 0;
				map_trees[x][y][1] = 0;
				map_points[x][y] = 0;

				if(map_points_buffer[x][y] != 0){
					if(map_points_buffer[x][y]->life_days > map_points_buffer[x][y]->max_life_days){
						if(map_trees_buffer[x][y][0] == 2){
							//new tree node
							NodeTree *ptr = create_tree(first_node_tree_ptr);
							map_trees[x][y][0] = 1; // seed
							map_trees[x][y][1] = 0; // active gen
							map_points[x][y] = ptr; // point in new tree
						}
					}else{
						map_trees[x][y][0] = map_trees_buffer[x][y][0];
						map_trees[x][y][1] = map_trees_buffer[x][y][1];
						map_points[x][y] = map_points_buffer[x][y];
					}
				}

				map_trees_buffer[x][y][0] = 0;
				map_trees_buffer[x][y][1] = 0;
				map_points_buffer[x][y] = 0;
			
			}
		}

		int count_trees = 0;
		tree_ptr = first_node_tree_ptr;
		while(tree_ptr->next != 0){
			tree_ptr = tree_ptr->next;

			if(tree_ptr->life_days > tree_ptr->max_life_days){
				NodeTree *tmp_next = tree_ptr->next;
				delete_node_tree(first_node_tree_ptr, tree_ptr);
				tree_ptr = tmp_next;
			}
			else{
				tree_ptr->life_days++;
			}
			count_trees++;
		}
		
		DrawText(TextFormat("trees count: %d", count_trees), 120, 10, 10, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
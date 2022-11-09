#include <stdio.h>
#include "raylib.h"

#include "trees.h"

const int WIDTH = 1000, HEIGHT = 600;
const int SIZE = 5;
const int MAP_WIDTH = 200;
const int MAP_HEIGHT = 120;

const int MAX_LIGHT_POWER = 8;
int light_power = MAX_LIGHT_POWER;
int energy_power = 3;

unsigned long generation_count = 0;
int mx, my;
int x_offset;

int main(){
	InitWindow(WIDTH, HEIGHT, "Digital Trees");

	NodeTree *map_points[MAP_WIDTH][MAP_HEIGHT];
	int map_trees[MAP_WIDTH][MAP_HEIGHT][2];

	NodeTree *map_points_buffer[MAP_WIDTH][MAP_HEIGHT];
	int map_trees_buffer[MAP_WIDTH][MAP_HEIGHT][2];

	for(int x = 0; x < MAP_WIDTH; x++){
		for(int y = 0; y < MAP_HEIGHT; y++){
			map_trees[x][y][0] = 0;
			map_trees[x][y][1] = 0;
			map_points[x][y] = 0;
			map_trees_buffer[x][y][0] = 0;
			map_trees_buffer[x][y][1] = 0;
			map_points_buffer[x][y] = 0;
		}
	}
	
	NodeTree *tree_ptr;
	NodeTree *first_node_tree_ptr = node_tree_init();

	tree_ptr = create_tree(first_node_tree_ptr, 0);
	map_trees[100][110][0] = 1;
	map_trees[100][110][1] = 0;
	map_points[100][110] = tree_ptr;

	while(!WindowShouldClose()){
		mx = GetMouseX();
		my = GetMouseY();

		BeginDrawing();

		ClearBackground((Color){20, 20, 20, 255});


		for(int x = 0; x < MAP_WIDTH; x++){
			light_power = MAX_LIGHT_POWER;
			energy_power = 3;
			for(int y = 0; y < MAP_HEIGHT; y++){
				if(map_trees[x][y][0] != 0){
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

						if(map_points[x][y]->genom[map_trees[x][y][1]][1] < 16){ // right
							if(map_trees[x+1][y][0] == 0){
								if(x + 1 < MAP_WIDTH){x_offset = x + 1;}
								else{x_offset = 0;}

								map_trees_buffer[x_offset][y][0] = 2;
								map_trees_buffer[x_offset][y][1] = map_points[x][y]->genom[map_trees[x][y][1]][1];
								map_points_buffer[x_offset][y] = map_points[x][y];

								map_trees_buffer[x][y][0] = 3;
							}
						}

						if(map_points[x][y]->genom[map_trees[x][y][1]][3] < 16){ // left
							if(map_trees[x-1][y][0] == 0){
								if(x - 1 >= 0){ x_offset = x - 1; }
								else{ x_offset = MAP_WIDTH - 1; }
								map_trees_buffer[x_offset][y][0] = 2;
								map_trees_buffer[x_offset][y][1] = map_points[x][y]->genom[map_trees[x][y][1]][3];
								map_points_buffer[x_offset][y] = map_points[x][y];

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
						DrawText(TextFormat("energy: %d", map_points[x][y]->energy), 10, 115, 10, LIGHTGRAY);

						for(int j = 0; j < 16; j++){
							if(j == map_trees[x][y][1]){
								DrawText(TextFormat("%d > ", j), 10, 150+j*20, 10, RED);
							}else{
								DrawText(TextFormat("%d > ", j), 10, 150+j*20, 10, LIGHTGRAY);
							}
							for(int i = 0; i < 4; i++){
								DrawText(TextFormat("%d", map_points[x][y]->genom[j][i]), 30+i*20, 150+j*20, 10, LIGHTGRAY);
							}
						}
					}

					if(light_power > 0 && energy_power > 0){
						map_points[x][y]->energy += light_power * energy_power;
					}

					light_power--;
					energy_power--;

					map_points[x][y]->energy -= 10;

				} else {
					if(energy_power < 3) { energy_power++; }
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
					if(map_points_buffer[x][y]->life_days > map_points_buffer[x][y]->max_life_days || map_points_buffer[x][y]->energy < 0){
						if(map_trees_buffer[x][y][0] == 2){
							if(map_points_buffer[x][y]->energy >= 0){
								//new tree node
								NodeTree *ptr = create_tree(first_node_tree_ptr, map_points_buffer[x][y]);
								map_trees[x][y][0] = 1; // seed
								map_trees[x][y][1] = 0; // active gen
								map_points[x][y] = ptr; // point in new tree
							}
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
		if(tree_ptr != 0){
		while(tree_ptr->next != 0){
			tree_ptr = tree_ptr->next;
			//if(tree_ptr->life_days != 0){ break; }
			if(tree_ptr->life_days > tree_ptr->max_life_days || tree_ptr->energy < 0){
				NodeTree *tmp_next;
				if(tree_ptr->next != 0){ tmp_next = tree_ptr->next; } else { tmp_next = 0; }
				delete_node_tree(first_node_tree_ptr, tree_ptr);
				//break;
				if(tmp_next != 0){
					tree_ptr = tmp_next; continue;
				} else {
					break;
				}
			}
			else{
				tree_ptr->life_days++;
			}
			count_trees++;
		}
		}

		generation_count++;

		DrawText(TextFormat("generation: %d", generation_count), 120, 10, 10, WHITE);
		DrawText(TextFormat("trees: %d", count_trees), 120, 30, 10, WHITE);


		EndDrawing();
	}

	CloseWindow();

	return 0;
}
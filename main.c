#include <stdio.h>
#include <raylib.h>

const int WIDTH = 800, HEIGHT = 600;
const int SIZE = 5;
const int MAP_WIDTH = 160;
const int MAP_HEIGHT = 120;

int mx, my;

int main(){
	InitWindow(WIDTH, HEIGHT, "Digital Trees");
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
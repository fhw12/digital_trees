#include <stdio.h>
#include <raylib.h>

int main(){
	InitWindow(800, 600, "Digital Trees");
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground((Color){20, 20, 20, 255});

		DrawRectangle(5, 5, 100, 50, Fade(WHITE, 0.9f));
		DrawRectangleLines(5, 5, 100, 50, WHITE);
		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 10, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
#include <stdio.h>
#include <raylib.h>

int main(){
	InitWindow(800, 600, "Digital Trees");
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground((Color){20, 20, 20, 255});
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth=512;
    const int windowHeight=380;
    
    // initialize window
    InitWindow(windowWidth,windowHeight,"Dapper-Dasher");

    // set fps
    SetTargetFPS(60);

    // game loop
    while(!WindowShouldClose())
    {   
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // stop drawing
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth=512;
    const int windowHeight=380;
    
    // initialize window
    InitWindow(windowWidth,windowHeight,"Dapper-Dasher");

    // acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};

    Texture2D scarfy=LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width=scarfy.width/6;
    scarfyRec.height=scarfy.height;
    scarfyRec.x=0;
    scarfyRec.y=0;
    Vector2 scarfyPos;
    scarfyPos.x=windowWidth/2-scarfyRec.width/2;
    scarfyPos.y=windowHeight-scarfyRec.height;

    int velocity{0};
    
    // is the rectangle in the air
    bool isInAir=false;

    // jump velocity
    const int jumpVel{-22};

    // set fps
    SetTargetFPS(60);

    // game loop
    while(!WindowShouldClose())
    {   
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if(scarfyPos.y>=windowHeight-scarfyRec.height)
        {
            // rectangle is on the ground
            velocity=0;
            isInAir=false;
        }
        else
        {
            // rectange is in the air
            isInAir=true;
            // apply gravity
            velocity+=gravity;
        }

        if(IsKeyPressed(KEY_SPACE)&&!isInAir)
        {
            velocity+=jumpVel;
        }

        // update position
        scarfyPos.y += velocity; 

        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();

    return 0;
}
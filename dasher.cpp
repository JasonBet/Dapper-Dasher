#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    
    // initialize window
    InitWindow(windowWidth,windowHeight,"Dapper-Dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{1000};

    Texture2D scarfy=LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width=scarfy.width/6;
    scarfyRec.height=scarfy.height;
    scarfyRec.x=0;
    scarfyRec.y=0;
    Vector2 scarfyPos;
    scarfyPos.x=windowWidth/2-scarfyRec.width/2;
    scarfyPos.y=windowHeight-scarfyRec.height;

    // pixels / frame
    int velocity{0};
    
    // is the rectangle in the air
    bool isInAir=false;

    // jump velocity (pixels / sec)
    const int jumpVel{-600};

    // set fps
    SetTargetFPS(60);

    // game loop
    while(!WindowShouldClose())
    {   
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

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
            velocity+=gravity*dT;
        }

        if(IsKeyPressed(KEY_SPACE)&&!isInAir)
        {
            velocity+=jumpVel;
        }

        // update position
        scarfyPos.y += velocity*dT; 

        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();

    return 0;
}
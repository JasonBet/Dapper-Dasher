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
    Vector2 scarfyPos;

    // rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight-height};
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
        if(posY>=windowHeight-height)
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
        posY += velocity; 

        DrawRectangle(windowWidth/2,posY,width,height, BLUE);
        // stop drawing
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
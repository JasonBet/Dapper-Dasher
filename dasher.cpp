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

    // nebula variables
    Texture2D nebula=LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0,0.0,nebula.width/8.f,nebula.height/8.f};
    Vector2 nebPos{windowWidth,windowHeight-nebRec.height};

    // nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunnignTime{};

    // nebula X velocity (pixels/second)
    int nebVel{-300};

    // scarfy variables
    Texture2D scarfy=LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width=scarfy.width/6;
    scarfyRec.height=scarfy.height;
    scarfyRec.x=0;
    scarfyRec.y=0;
    Vector2 scarfyPos;
    scarfyPos.x=windowWidth/2-scarfyRec.width/2;
    scarfyPos.y=windowHeight-scarfyRec.height;

    // animation frame
    int frame{};
    // amount of time before we update the animation frame
    const float updateTime=1.0/12;
    float runningTime{};

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

        // update nebula position
        nebPos.x+=nebVel*dT;

        // update scarfy position
        scarfyPos.y += velocity*dT; 

        // update running time
        runningTime+=dT;

        // update scarfy animation frame
        if(!isInAir){
            if(runningTime>=updateTime){
                runningTime=0.0;
                // update animation frame
                scarfyRec.x=frame*scarfyRec.width;
                frame++;
                if(frame>5){
                    frame=0;
                }
            }
        }

        // update nebula animation frame
        nebRunnignTime+=dT;
        if(nebRunnignTime>=nebUpdateTime)
        {
            nebRunnignTime=0.0;
            nebRec.x=nebFrame*nebRec.width;
            nebFrame++;
            if(nebFrame>7)
            {
                nebFrame=0;
            }
        }
        
        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    return 0;
}
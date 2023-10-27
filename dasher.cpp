#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

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

    // AnimData for nebula
    AnimData nebData{
        {0.0,0.0,nebula.width/8.f,nebula.height/8.f}, // Rectange rec
        {windowWidth,windowHeight-nebula.height/8}, // Vector2 pos  
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
    };

    AnimData neb2Data{
        {0.0,0.0,nebula.width/8.f,nebula.height/8.f},
        {windowWidth+300,windowHeight-nebula.height/8},
        0,
        1.0/16.0,
        0.0,
    };

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
    AnimData scarfyData;
    scarfyData.rec.width=scarfy.width/6;
    scarfyData.rec.height=scarfy.height;
    scarfyData.rec.x=0;
    scarfyData.rec.y=0;
    scarfyData.pos.x=windowWidth/2-scarfyData.rec.width/2;
    scarfyData.pos.y=windowHeight-scarfyData.rec.height;
    scarfyData.frame=0;
    scarfyData.updateTime=1.0/12.0;
    scarfyData.runningTime=0.0;

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
        if(scarfyData.pos.y>=windowHeight-scarfyData.rec.height)
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
        scarfyData.pos.y += velocity*dT; 

        // update running time
        scarfyData.runningTime+=dT;

        // update scarfy animation frame
        if(!isInAir){
            if(scarfyData.runningTime>=scarfyData.updateTime){
                scarfyData.runningTime=0.0;
                // update animation frame
                scarfyData.rec.x=scarfyData.frame*scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame>5){
                    scarfyData.frame=0;
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
        DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    return 0;
}
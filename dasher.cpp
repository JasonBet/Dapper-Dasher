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
    // array of window dimensions
    int windowDimensions[2];
    windowDimensions[0]=512;
    windowDimensions[1]=380;
    
    // initialize window
    InitWindow(windowDimensions[0],windowDimensions[1],"Dapper-Dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{1000};

    // nebula variables
    Texture2D nebula=LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebulae[2]{};

    for(int i=0;i<2;i++)
    {
        nebulae[i].rec.x=0.0;
        nebulae[i].rec.y=0.0;
        nebulae[i].rec.width=nebula.width/8.f;
        nebulae[i].rec.height=nebula.height/8.f;
        nebulae[i].pos.y=windowDimensions[1]-nebula.height/8;
        nebulae[i].frame=0;
        nebulae[i].runningTime=0.0;
        nebulae[i].updateTime=1.0/16.0;
    }
    
    nebulae[0].pos.x=windowDimensions[0];
    nebulae[1].pos.x=windowDimensions[0]+300;

    // nebula X velocity (pixels/second)
    int nebVel{-300};

    // scarfy variables
    Texture2D scarfy=LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width=scarfy.width/6;
    scarfyData.rec.height=scarfy.height;
    scarfyData.rec.x=0;
    scarfyData.rec.y=0;
    scarfyData.pos.x=windowDimensions[0]/2-scarfyData.rec.width/2;
    scarfyData.pos.y=windowDimensions[1]-scarfyData.rec.height;
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
        if(scarfyData.pos.y>=windowDimensions[1]-scarfyData.rec.height)
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
        nebulae[0].pos.x+=nebVel*dT;

        // update nebula2 position
        nebulae[1].pos.x+=nebVel*dT;

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
        nebulae[0].runningTime+=dT;
        if(nebulae[0].runningTime>=nebulae[0].updateTime)
        {
            nebulae[0].runningTime=0.0;
            nebulae[0].rec.x=nebulae[0].frame*nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame>7)
            {
                nebulae[0].frame=0;
            }
        }

        // update nebula2 animation frame
        nebulae[1].runningTime+=dT;
        if(nebulae[1].runningTime>=nebulae[1].updateTime)
        {
            nebulae[1].runningTime=0.0;
            nebulae[1].rec.x=nebulae[1].frame*nebulae[1].rec.width;
            nebulae[1].frame++;
            if(nebulae[1].frame>7)
            {
                nebulae[1].frame=0;
            }
        }
        
        // draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

        // draw nebula2
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

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
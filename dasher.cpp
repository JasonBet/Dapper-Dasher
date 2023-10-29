#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y>=windowHeight-data.rec.height;
}

AnimData updateAnimdata(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime+=deltaTime;
    if(data.runningTime>=data.updateTime)
    {
        data.runningTime=0.0;
        // update animation frame
        data.rec.x=data.frame*data.rec.width;
        data.frame++;
        if(data.frame>maxFrame)
        {
            data.frame=0;
        }
    }
    return data;
}

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

    const int sizeOfNebulae{20};
    AnimData nebulae[sizeOfNebulae]{};

    for(int i=0;i<sizeOfNebulae;i++)
    {
        nebulae[i].rec.x=0.0;
        nebulae[i].rec.y=0.0;
        nebulae[i].rec.width=nebula.width/8.f;
        nebulae[i].rec.height=nebula.height/8.f;
        nebulae[i].pos.x=windowDimensions[0]+(300*i);
        nebulae[i].pos.y=windowDimensions[1]-nebula.height/8;
        nebulae[i].frame=0;
        nebulae[i].runningTime=0.0;
        nebulae[i].updateTime=1.0/16.0;
    }

    // nebula X velocity (pixels/second)
    int nebVel{-200};

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

    Texture2D background=LoadTexture("textures/far-buildings.png");
    float bgX{};

    Texture2D midground=LoadTexture("textures/back-buildings.png");
    float mgX{};

    Texture2D foreground=LoadTexture("textures/foreground.png");
    float fgX{};
    
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

        // scroll background
        bgX-=20*dT;
        if(bgX<=-background.width*2)
        {
            bgX=0.0;
        }

        // scroll midground
        mgX-=40*dT;
        if(bgX<=-midground.width*2)
        {
            mgX=0.0;
        }

        // scroll foreground
        fgX-=40*dT;
        if(fgX<=-foreground.width*2)
        {
            fgX=0.0;
        }

        // draw the background
        Vector2 bg1Pos{bgX,0.0};
        DrawTextureEx(background,bg1Pos,0.0,2.0,WHITE);
        Vector2 bg2Pos{bgX+background.width*2,0.0};
        DrawTextureEx(background,bg2Pos,0.0,2.0,WHITE);
        
        // draw midground
        Vector2 mg1Pos{mgX,0.0};
        DrawTextureEx(midground,mg1Pos,0.0,2.0,WHITE);
        Vector2 mg2Pos{mgX+midground.width*2,0.0};
        DrawTextureEx(midground,mg2Pos,0.0,2.0,WHITE);

        // draw foreground
        Vector2 fg1Pos{fgX,0.0};
        DrawTextureEx(foreground,fg1Pos,0.0,2.0,WHITE);
        Vector2 fg2Pos{fgX+foreground.width*2,0.0};
        DrawTextureEx(foreground,fg2Pos,0.0,2.0,WHITE);

        // perform ground check
        if(isOnGround(scarfyData,windowDimensions[1]))
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

        for(int i=0;i<sizeOfNebulae;i++)
        {
            // update nebulae positions
            nebulae[i].pos.x+=nebVel*dT;
        }

        // update scarfy position
        scarfyData.pos.y += velocity*dT; 

        // update running time
        scarfyData.runningTime+=dT;

        // update scarfy animation frame
        if(!isInAir){
            scarfyData=updateAnimdata(scarfyData,dT,5);
        }

        for(int i=0;i<sizeOfNebulae;i++)
        {
            // update nebulae animation frames
            nebulae[i]=updateAnimdata(nebulae[i],dT,7);
        }
        
        for(int i=0;i<sizeOfNebulae;i++)
        {
            // draw nebulae
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // draw scarfy
        DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);

        // stop drawing
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    return 0;
}
#include <raylib.h>
#include "game.h"
#include "color.h"
#include <iostream>
double lastUpdateTime = 0;

//set time interval
bool eventTriggered(double interval){
    double curTime = GetTime();
    if(curTime - lastUpdateTime >= interval){
        lastUpdateTime = curTime;
        return true;
    }
    return false;
}
void gameStart();
void gameMenu();
bool paused = false;

int main()
{
    int screenWidth = 500;
    int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, "Raylib Tetris"); //initialize the game window 
    gameMenu();
    CloseWindow();
    return 0;
}

void gameStart(){
    SetTargetFPS(60);
    Font font = LoadFontEx("font/OpenSans-Regular.ttf",64,0,0);
    Game game = Game();

    while (!WindowShouldClose())
    {
        //pause mechanic
        if(IsKeyPressed(KEY_Q)){
            paused = !paused;
        }

        if(paused){         //draw if paused
            DrawTextEx(font, "PAUSED", {330,435}, 50, 2, GOLD);
        }

        if(!paused){        //if game not paused run as normal
            UpdateMusicStream(game.music);
            game.handleInput();
            if(eventTriggered(1/(2.0*game.level))){
                game.MoveBlockDown();
            }
        }
        
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365,15}, 38, 2, WHITE);          //draw text
        DrawTextEx(font, "Level", {365,115}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370,220}, 38, 2, WHITE);
        
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);        //rectangle for score
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 scoreTextSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - scoreTextSize.x)/2, 65}, 38, 2, WHITE);

        DrawRectangleRounded({320, 150, 170, 60}, 0.3, 6, lightBlue);        //rectangle for level
        char levelText[10];
        sprintf(levelText, "%d", game.level);
        Vector2 levelTextSize = MeasureTextEx(font, levelText, 38, 2);
        DrawTextEx(font, levelText, {320 + (170 - levelTextSize.x)/2, 160}, 38, 2, WHITE);

        DrawRectangleRounded({320, 255, 170, 130}, 0.3, 6, lightBlue);      //rectangle for next block

        //texts appear if game is over
        if(game.gameOver){
            DrawTextEx(font, "GAME OVER", {320,435}, 38, 2, WHITE);
            DrawTextEx(font, "Press ENTER", {325,475}, 32, 2, WHITE);
            DrawTextEx(font, "to play again", {325,515}, 32, 2, WHITE);
        }
        game.Draw();
        EndDrawing();
    }
}

//initialize the menu screen
void gameMenu(){
    SetTargetFPS(60);
    Font font = LoadFontEx("font/OpenSans-Regular.ttf",64,0,0);
    Texture2D background = LoadTexture("images/background.png");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTexture(background,0,0,WHITE);
        //instruction
        DrawTextEx(font, "LEFT RIGHT ARROW: MOVE", {10, 320}, 30, 2, WHITE);
        DrawTextEx(font, "UP ARROW: ROTATE", {10, 350}, 30, 2, WHITE);
        DrawTextEx(font, "DOWN ARROW: GO DOWN", {10, 380}, 30, 2, WHITE);
        DrawTextEx(font, "Q: PAUSE", {10, 410}, 30, 2, WHITE);
        DrawTextEx(font, "ESC: EXIT", {10, 440}, 30, 2, WHITE);
        //create play button
        Rectangle playButton;
        playButton.x = (GetScreenWidth()-playButton.width)/2;
        playButton.y = (GetScreenHeight()-playButton.height)/2 - 40;
        playButton.height = 80;
        playButton.width = 180;
        if(CheckCollisionPointRec(GetMousePosition(),playButton))
        {
            DrawRectangle((GetScreenWidth()-playButton.width)/2,(GetScreenHeight()-playButton.height)/2 - 40,playButton.width,playButton.height,WHITE);
            DrawTextEx(font, "PLAY", {205, 250}, 50, 2, BLACK);
        }

        else
        {
            DrawRectangle((GetScreenWidth()-playButton.width)/2,(GetScreenHeight()-playButton.height)/2 - 40,playButton.width,playButton.height,SKYBLUE);
            DrawTextEx(font, "PLAY", {205, 250}, 50, 2, BLACK);
        }

        //check if player click on the play button
        if(CheckCollisionPointRec(GetMousePosition(),playButton) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            gameStart();
            break;
        }
        EndDrawing();
    }
}
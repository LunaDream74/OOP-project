#include "game.h"
#include <random>
#include <iostream>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlock();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    level = 1;
    InitAudioDevice();
    music = LoadMusicStream("sounds/theme.mp3");
    PlayMusicStream(music);
    clearSound = LoadSound("sounds/clear.wav");
    gameoverSound = LoadSound("sounds/gameover.mp3");
    levelupSound = LoadSound("sounds/levelUp.wav");
}

Game::~Game(){
    UnloadSound(gameoverSound);
    UnloadSound(clearSound);
    UnloadSound(levelupSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock(){
    if(blocks.empty()){
            blocks = GetAllBlock();
    }
    int randomIndex = rand()%blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    return block;
}

std::vector<Block> Game::GetAllBlock(){
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(){
    grid.Draw();
    if(blockFits() == true){
        currentBlock.Draw(11, 11);
        switch (nextBlock.id){
            case 3:
                nextBlock.Draw(255,315);
                break;
            case 4:
                nextBlock.Draw(255,285);
                break;
            default:
                nextBlock.Draw(270,290);
                break;
        }
    }
}

//take input from user
void Game::handleInput(){
    int keyPressed = GetKeyPressed();   //get key press except for down key
    if(gameOver && IsKeyPressed(KEY_ENTER)){ //if game is over and pressed ENTER key, restart game
        gameOver = false;
        reset();
    }
    switch(keyPressed){
        case KEY_LEFT:      //move block left
            MoveBlockLeft();
            break;
        
        case KEY_RIGHT:     //move block right
            MoveBlockRight();
            break;

        case KEY_UP:        //rotate block
            rotateBlock();
            break;
    }

    if(!gameOver){
        if(IsKeyDown(KEY_DOWN)){ //if down key is held move block down
            MoveBlockDown();
            updateScore(0,1);
        }
    }
}


void Game::MoveBlockLeft(){
    if(!gameOver){
        currentBlock.Move(0, -1);
        if(isBlockOutside() || blockFits() == false){
            currentBlock.Move(0,1);
        }
    }
}

void Game::MoveBlockRight(){
    if(!gameOver){
        currentBlock.Move(0, 1);
        if(isBlockOutside() || blockFits() == false){
            currentBlock.Move(0,-1);
        }
    }
    
}

void Game::MoveBlockDown(){
    if(!gameOver){
        currentBlock.Move(1, 0);
        if(isBlockOutside() || blockFits() == false){
            currentBlock.Move(-1,0);
            lockBlock();
        }
    }
}

void Game::rotateBlock(){
    if(!gameOver){
        currentBlock.rotate();
        if(isBlockOutside() || blockFits() == false){
            currentBlock.undoRotate();
        }
    }
}

//check if block is outside the grid
bool Game::isBlockOutside()
{   
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles){
        if(grid.isCellOutside(item.row, item.col))
            return true;
    }
    return false;
}

//lock block in place if detect a collision
void Game::lockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles){
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(blockFits() == false){ //if block no longer fit, game over
        gameOver = true;
        StopMusicStream(music);
        PlaySound(gameoverSound);
    }
    nextBlock = GetRandomBlock();

    int rowsCleared = grid.clearFullRow();
    //detect when row is cleared and play sound, update score
    if(rowsCleared > 0){ 
        PlaySound(clearSound);
        updateScore(rowsCleared, 0);
    }
}

//check if current block fits on current game grid
bool Game::blockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item: tiles){
        if(grid.isCellEmpty(item.row, item.col) == false){
            return false;
        }
    }
    return true;
}

//reset game
void Game::reset(){
    grid.Initialize();
    blocks = GetAllBlock();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    level = 1;
    PlayMusicStream(music);
}

//update score for each row cleared
void Game::updateScore(int lineCleared, int moveDownPoint){
    switch (lineCleared){
    case 1:
        score+= 100 * level;
        break;
    case 2:
        score+= 300 * level;
        break;
    case 3:
        score+= 500 * level;
        break;
    case 4:
        score+= 800 * level;
        break;
    default:
        break;
    }
    score += moveDownPoint;
    updateLevel(score);
}

//update level every 1250 score (or any arbitrary number you want)
void Game::updateLevel(int score){
    if(score >= 1250*level){
        PlaySound(levelupSound);
        level++;
    }
}

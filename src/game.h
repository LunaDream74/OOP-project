#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
public:
    Game();
    ~Game();
    void Draw();
    bool gameOver;
    void handleInput();
    void MoveBlockDown();
    int score;
    int level;
    Music music;

private:
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    std::vector<Block> blocks;

    Sound clearSound;
    Sound gameoverSound;
    Sound levelupSound;

    void MoveBlockLeft();
    void MoveBlockRight();
    void rotateBlock();
    bool isBlockOutside();
    void lockBlock();
    bool blockFits();

    Block GetRandomBlock();
    std::vector<Block> GetAllBlock();
    
    
    void reset();
    void updateScore(int lineCleared, int moveDownPoint);
    void updateLevel(int score);
};
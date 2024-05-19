#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "color.h"
using namespace std;

class Block
{
public:
    //constructor
    Block();

    int id;
    map<int, vector<Position>> cells;

    void Draw(int offsetX, int offsetY);
    void Move(int row, int col);    
    void rotate();
    void undoRotate();
    std::vector<Position> GetCellPosition();

private:
    int cellSize;
    int rotationState;
    int rowOffset, colOffset;
    vector<Color> colors;
};
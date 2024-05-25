#include "block.h"
using namespace std;

//constructor
Block::Block(){
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}

//draw blocks
void Block::Draw(int offsetX, int offsetY){
    std::vector<Position> tiles = GetCellPosition();
    for(Position item: tiles){
        DrawRectangle(item.col*cellSize + offsetX, item.row*cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

//move block
void Block::Move(int rows, int cols){
    rowOffset += rows;
    colOffset += cols;
}


vector<Position> Block::GetCellPosition(){
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for(Position item: tiles){
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

//rotate block to next rotation state
void Block::rotate(){
    rotationState++;
    if(rotationState == (int)cells.size())
        rotationState = 0;
}

//reverse rotation
void Block::undoRotate(){
    rotationState--;
    if(rotationState == -1) //if rotation is smaller than 0 set it back to highest rotation state
        rotationState = cells.size() - 1;
}

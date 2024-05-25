#include"grid.h"
#include <iostream>
#include "color.h"
using namespace std;

//constructor
Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

//initialize the grid with 0s
void Grid::Initialize(){
    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){
            grid[row][col] = 0;
        }
    }
}

//print out grid (only for checking if each cell values is correct, not used in game)
void Grid::Print(){
    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

//draw the grid
void Grid::Draw(){
    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){
            int cellValue = grid[row][col];
            DrawRectangle(col*cellSize + 11, row*cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

//check if block cell is outside of the grid
bool Grid::isCellOutside(int row, int col){
    if(row >= 0 && row < numRows && col >= 0 && col < numCols) 
        return false;
    return true;
}

//check if cell is empty
bool Grid::isCellEmpty(int row, int col){
    if(grid[row][col] == 0)
        return true;
    return false;
}

//combine checking if row is full, then clearing it and finally move other rows down
int Grid::clearFullRow(){
    int completed = 0;
    for(int row = numRows - 1; row >= 0; row--){
        if(isRowFull(row)){
            clearRow(row);
            completed++;
        }
        else if(completed > 0){
            moveRowDown(row,completed);
        }
    }
    return completed;
}

//check for full rows function
bool Grid::isRowFull(int row){
    for(int col = 0; col < numCols; col++){
        if(grid[row][col] == 0)
            return false;
    }
    return true;
}

//clear row by setting cell values to 0 function
void Grid::clearRow(int row){
    for(int col = 0; col < numCols; col++){
        grid[row][col] = 0;
    }
}

//move down other rows function
void Grid::moveRowDown(int row, int numRows){
    for(int col = 0; col < numCols; col++){
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

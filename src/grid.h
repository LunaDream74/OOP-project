#pragma once
#include <vector>
#include <raylib.h>
using namespace std;

class Grid
{
private:
    int numRows, numCols, cellSize;
    vector<Color> colors;
    bool isRowFull(int row);
    void clearRow(int row);
    void moveRowDown(int row, int numRows);
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    int grid[20][10];
    bool isCellOutside(int row, int col);
    bool isCellEmpty(int row, int col);
    int clearFullRow();
};


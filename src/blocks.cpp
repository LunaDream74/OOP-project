#include "block.h"
#include "position.h"
/*Each cells represent a state of rotation of the block. For example, using the L block
[0][0][1]       [0][1][0]      [0][0][0]      [1][1][0]
[1][1][1]   ->  [0][1][0]  ->  [1][1][1]  ->  [0][1][0]
[0][0][0]       [0][1][1]      [1][0][0]      [0][1][0]
*/


class LBlock: public Block{
    public:
        LBlock(){
            id = 1;
            cells[0] = {Position(0,2), Position(1,0), Position(1,1), Position(1,2)};
            cells[1] = {Position(0,1), Position(1,1), Position(2,1), Position(2,2)};
            cells[2] = {Position(1,0), Position(1,1), Position(1,2), Position(2,0)};
            cells[3] = {Position(0,0), Position(0,1), Position(1,1), Position(2,1)};
            Move(0,3);          //makes block spawn in center
        }
};

class JBlock: public Block{
    public:
        JBlock(){
            id = 2;
            cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
            cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
            cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)};
            Move(0,3);          //makes block spawn in center
        }
};

class IBlock : public Block
{
public:
    IBlock(){
        id = 3;
        cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
        cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
        cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
        Move(-1,3);          //makes block spawn in center
    }
};

class OBlock : public Block
{
public:
    OBlock(){
        id = 4;
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
        Move(0,4);          //makes block spawn in center
    }
};

class SBlock : public Block
{
public:
    SBlock(){
        id = 5;
        cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
        cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)};
        cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
        Move(0,3);          //makes block spawn in center
    }
};

class TBlock : public Block
{
public:
    TBlock(){
        id = 6;
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
        Move(0,3);          //makes block spawn in center
    }
};

class ZBlock : public Block
{
public:
    ZBlock(){
        id = 7;
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
        Move(0,3);          //makes block spawn in center
    }
};
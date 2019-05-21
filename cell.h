#ifndef CELL_H
#define CELL_H

// used exclusively for storing the state of a cell
// all actual computations should be handled by the Board class

class Cell {
private:
    int xPos, yPos;
    bool isMine;
    int neighborCount;
public:
    Cell(int xPos=0, int yPos=0, bool isMine=false, int neighborCount=0)
    :xPos(xPos), yPos(yPos), isMine(isMine), neighborCount(neighborCount){}
    int getPosX();
    int getPosY();
    bool mineCheck();
    int neighbors();
};

#endif // CELL_H

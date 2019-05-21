#include "cell.h"

int Cell::getPosX() {
    return this->xPos;
}

int Cell::getPosY() {
    return this->yPos;
}

int Cell::neighbors() {
    return this->neighborCount;
}

bool Cell::mineCheck() {
    return this->isMine;
}

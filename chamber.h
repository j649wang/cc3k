
#ifndef chamber_hpp
#define chamber_hpp

#include <stdio.h>
#include <memory>
#include <vector>

class Cell;

class Chamber{
    std::vector<Cell *> cells;
public:
    Chamber();
    ~Chamber();
    std::vector<Cell *> getCells();
    void addCells(Cell *c);
};
#endif /* chamber_hpp */

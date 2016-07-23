//

#include "chamber.h"
#include "cell.h"
using namespace std;

Chamber::Chamber(){}

Chamber::~Chamber(){
    cells.clear();
}

vector<Cell *> Chamber::getCells(){
    return cells;
};

void Chamber::addCells(Cell * c){
    cells.emplace_back(c);
}

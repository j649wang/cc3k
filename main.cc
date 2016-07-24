#include "game.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char **argv){
    srand(time(NULL));
    bool restartGame;
    string cmd = "*";
    string floorplan = "map.txt";
    
    if(argv[1]){
        floorplan = argv[1];
    }
    
    do{
        Game g(floorplan);
        g.chooserace();
        if(g.quitProgram()) return 0;
        g.start();
        if((g.isWin())||(g.isLost())){
            cout << "Do you want to play again? Enter 'y' means Yes; Enter 'n' means No." << endl;
            cin >> cmd;
            if(cmd == "n") return 0;
            while((cmd != "y")&&(cmd != "n")){
                cout << "invalid command!" << endl;
                cin >> cmd;
                if(cmd == "n") return 0;
            }
        }
        if(g.quitProgram()) return 0;
        restartGame = g.quitGame();
    }while(restartGame||(cmd == "y"));
    return true;
}

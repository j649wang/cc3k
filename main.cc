//
//  main.cpp
//  cc3k.cs246.Final
//
//  Created by Zoey on 16/7/17.
//  Copyright © 2016年 Zoey. All rights reserved.
//

#include "game.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char **argv){
    bool restartGame;
    string cmd;
    string floorplan = "map.txt";
    
    if(argv[1]){
        floorplan = argv[1];
    }
       
    do{
        Game g(floorplan);
        g.chooserace(); //
        if(g.quitProgram()) return 0;
        g.start();
        if((g.isWin())||(g.isLost())){
            cout << "Do you want to play again? Enter 'y' or 'Y' means Yes; Enter 'N' or 'n' means No." << endl;
            cin >> cmd;
            if((cmd == "N")||(cmd == "n")) return 0;
            else if((cmd != "Y")||(cmd != "y")) cout << "Invalid Command!" << endl;
        }
        if(g.quitProgram()) return 0;
        restartGame = g.quitGame();
    }while(restartGame||(cmd == "Y")||(cmd == "y"));
    return true;
}
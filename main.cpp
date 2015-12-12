//
//  main.cpp
//  MP1
//
//  Created by Erik on 9/24/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "MazeArray.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    World temp("/Users/Erik/Documents/School/AI/MP1/MP1/input.txt");
    //temp.runDFS();
    //temp.runBFS();
    //temp.runGreedy();
    //temp.runAstar();
    temp.RunTurn();
    temp.RunFoward();
   
    return 0;
    
}

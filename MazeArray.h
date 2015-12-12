//
//  MazeArray.h
//  MP1
//
//  Created by Erik on 9/24/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#ifndef __MP1__MazeArray__
#define __MP1__MazeArray__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <list>

#define LEFT 0;
#define RIGHT 1;

#define G 2; //ghost
#define PG 1; // ghost was just there path still dies
#define NG 0; // no ghost

using namespace std;


class xyCord
{
public:
    int x;
    int y;
    
    
private:
    
    
};

class Ghost{
    
public:
    xyCord pos;
    xyCord lastpos;
    int direction;
    
};



class Maze // needs copy constructor but that functionality will not be used so screw it
{
public:
    
    
    class Node// no copy consturctor or assignment operator needed becuase all attributs are assigend by value
    {           // all the pointers of the cildren will be copied aswell important to note
    public:
        Node(int x, int y, Maze * m, Node * p);
        Node(xyCord loc, Maze * m, Node * p);
        ~Node();
        // gets cordinats of
        xyCord getxyCord();
        
        //expands the current node
        // expands all new nodes reachable from current node exept the parent of that node
        void expandNode();
        
        //funtions that return all pointers
        Node * getParent();
        Node * getNorhChild();
        Node * getEastChild();
        Node * getSouthChild();
        Node * getWestChild();
        
        
        //checks if node has already been expanded
        bool isExpanded();
        
        int getHuristicValue();
        int getAstarValue();
        
        int getGhostVal();
        int getForwardCost();
        int getTurnCost();
        
        int height = 0;
        
        vector<Ghost> currGhosts;
        
    private:
        //pointer to associated maze
        Maze * maze;
        
        // x and y coords of the node
        xyCord location;
        
        //all pinters to nodes
        Node * parent = NULL;
        Node * NorhChild = NULL;
        Node * EastChild = NULL;
        Node * SouthChild = NULL;
        Node * WestChild = NULL;
        
        char curdir;
        int forwardCost;
        int turnCost;
        
        //expanded chedk
        bool isexpanded = false;
        
        //delets current node and all children
        void deleteme();
        
        int ghostVal = (int)NG;
        
        int Hvalue;
        double Astarval;
        
    };
    
    
    
    
    Maze(string pathname);
    
    //returns values of X and Y sizes of the map
    int getXsize();
    int getYsize();
    
    //returns character located ay given x,y chord
    char getChar(int x, int y);
    
    /*returns a string of a copy of the maze*/
    string PrintMaze();
    
    //Redturns location of goal state
    xyCord getGoalLocation();
    
    //returns starting node
    Node * getStartNode();
    
    vector<Ghost> getStartGhosts;
    
    bool changeChar(int x, int y, char c);
    
    
private:
    vector <string> cMap;
    int Xsize = 0;
    int Ysize = 0;
    
    xyCord goalLocation;
    xyCord  startLocation;
    vector<Ghost> startGhosts;
};






class World
{
    
    
    
public:
    World(string s);
    ~World();
    
    bool runDFS();
    bool runBFS();
    bool runGreedy();
    bool runAstar();
    int expansions = 0;
    
private:
    
    void printSol();
    bool DFS(Maze::Node * curr_node);//function for DFS on rest of nodes
    bool BFS(Maze::Node * curr_node);
    bool Greedy(Maze::Node * curr_node);
    bool Astar();
    bool ** check;
    Maze * maze;
    xyCord goal_coord;
    Maze::Node * start = NULL;
    Maze::Node * endNode = NULL;
    
    string path;
    void makeWorld(string s);
    void deleteWorld();
    vector<Maze::Node*> frontier;
    
    
    
};

#endif /* defined(__MP1__MazeArray__) */

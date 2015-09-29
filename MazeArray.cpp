//
//  MazeArray.cpp
//  MP1
//
//  Created by Erik on 9/24/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include "MazeArray.h"
using namespace std;


//NODE
Maze::Node::Node(int X, int Y, Maze * m, Node * p)
{
    location.x = X;
    location.y = Y;
    maze = m;
    parent = p;
}

Maze::Node::Node(xyCord loc, Maze * m, Node * p)
{
    location = loc;
    maze = m;;
    parent = p;
}


xyCord Maze::Node::getxyCord()
{
    return location;
}

void Maze::Node::expandNode()
{
    //all children initialy set to null so only add the ones that need it
    
    
    if(isexpanded)// if it is already expanded then dont expand it again
        return;
    
    
    isexpanded = true;
    //make sure inside of maze
    if((location.x < 0)||(location.x >= maze->getXsize() )||(location.y < 0 )||(location.y >= maze->getYsize() ))
        return;
    
    //get north child
    if( ((location.y -1) >= 0) ) // check if in bounds
    {
        if(maze->getChar(location.x, location.y-1) != '%' )// if there is a space add child
        {
    
            if(parent == NULL)// if no parent add child
                NorhChild = new Node(location.x,location.y-1, maze, this);
            
            else if((parent->location.x == location.x ) && (parent->location.y == location.y-1)  )//if node matches parent dont add
                NorhChild = NULL;
            
            else
                NorhChild =new Node(location.x,location.y-1, maze, this);
        }
    }
    
    
    //get east child
    if((location.x +1) < maze->getXsize() )
    {
        if(maze->getChar(location.x+1, location.y) != '%' )// if there is a space add child
        {
            if(parent == NULL)
                EastChild = new Node(location.x+1, location.y, maze, this );
        
            else if( (parent->location.x == location.x+1 ) && (parent->location.y == location.y)  )
                EastChild = NULL;
            
            else
                EastChild = new Node(location.x+1, location.y, maze, this );
        }
    }
    
    
    //get south child
    if((location.y + 1) < maze->getYsize() )
    {
        if(maze->getChar(location.x, location.y+1) != '%' )// if there is a space add child
        {
            if(parent == NULL)
                SouthChild = new Node (location.x, location.y +1, maze, this);
        
            else if((parent->location.x == location.x ) && (parent->location.y == location.y + 1))
                SouthChild = NULL;
        
            else
                SouthChild = new Node (location.x, location.y +1, maze, this);
        }

    }
    
    //get west child
    if((location.x -1) >= 0)
    {
        if(maze->getChar(location.x-1, location.y) != '%' )// if there is a space add child
        {
            if(parent == NULL)
                WestChild = new Node(location.x -1,location.y, maze,this);
        
            else if((parent->location.x == location.x - 1) && (parent->location.y == location.y))
                WestChild = NULL;
        
            else
                WestChild = new Node(location.x -1,location.y, maze,this);
        }
        
        
    }
    
    
}

bool Maze::Node::isExpanded()
{
    return isexpanded;
}

Maze::Node * Maze::Node::getParent()
{
    return parent;
}
Maze::Node * Maze::Node::getNorhChild()
{
    return NorhChild;
}
Maze::Node * Maze::Node::getEastChild()
{
    return EastChild;
}
Maze::Node * Maze::Node::getSouthChild()
{
    return SouthChild;
}
Maze::Node * Maze::Node::getWestChild()
{
    return WestChild;
}

Maze::Node::~Node()
{
    deleteme();
}

void Maze::Node::deleteme()
{
    //free all childre
    if(NorhChild != NULL)
        delete NorhChild;
    
    if(EastChild != NULL)
        delete EastChild;

    if(SouthChild != NULL)
        delete SouthChild;

    if(WestChild != NULL)
        delete WestChild;

}


//MAZE
Maze::Maze(string pathname)
{
    ifstream inFile(pathname);
    if(inFile.bad())
        return;
    
    string s;
    
    while(!inFile.eof() )
    {
        getline(inFile, s); // get row
        s.append("\n"); // add new line character
        cMap.push_back(s);
    }
    Xsize = (int)(cMap[0].size() - 1);
    Ysize = (int)cMap.size();
    
    inFile.close();

}


string Maze::PrintMaze()
{
    string s;
    for(int i = 0; i < cMap.size(); i++)
    {
        s += cMap[i];
    }
    return s;
}


char Maze::getChar(int x, int y)
{
    return cMap[y][x];
}


int Maze::getXsize()
{
    return Xsize;
}


int Maze::getYsize()
{
    return Ysize;
}


Maze::Node * Maze::getStartNode()
{
    //error checking
    if((Xsize <= 0) || (Ysize<=0))
    {
        return NULL;
    }
    
    for(int x = 0; x < Xsize; x++)
    {
        for(int y = 0; y < Ysize; y++)
        {
          if(cMap[y][x] == 'P')
              return new Node(x,y,this, NULL);
        }
    }
    
    //if it gets here no "P" found so return error
    return NULL;
}



xyCord Maze::getGoalLocation()
{
    xyCord temp;
    temp.x = -1;
    temp.y = -1;
    
    if((Xsize <= 0) || (Ysize<=0))
    {
        return temp;
    }
    
    for(int x = 0; x < Xsize; x++)
    {
        for(int y = 0; y < Ysize; y++)
        {
            if(cMap[y][x] == '.')
            {
                temp.x = x;
                temp.y = y;
                return temp;
            }
        }
    }
    //return error if no period
    return temp;
}

bool Maze::changeChar(int x, int y, char c)
{
   if((x<0)||(x>=Xsize)||(y < 0)||(y >= Ysize))
       return false;
    
    cMap[y][x] = c;
    
    return true;
}


//WORLD
//world constructor
World::World(string s)
{
    makeWorld(s);
}

void World::makeWorld(string s)
{
    path = s;
    maze = new Maze(s);
    goal_coord = maze->getGoalLocation();
    start = maze->getStartNode();
    
    //get nmber of culums
    check = new bool*[maze->getXsize()];
    
    for(int i = 0; i < maze->getXsize(); i++)
    {
        check[i] = new bool[maze->getYsize()];
    }
    
    //initialize all nodes to not cheked
    for(int x = 0; x < maze->getXsize(); x++)
    {
        for(int y = 0; y < maze->getYsize(); y++)
        {
            check[x][y] = false;
        }
    }
}

World::~World()
{
    deleteWorld();
}

void  World::deleteWorld()
{
    
    for(int i = 0; i < maze->getXsize(); i++)
    {
        if(check[i] != NULL)
            delete [] check[i];
    }
    
    if(check != NULL)
        delete [] check;
    
    if(maze)
        delete maze;
    if(start)
        delete start;
}

bool World::runDFS()
{
    //refresh maze of old data
    deleteWorld();
    makeWorld(path);
    
    if((maze == NULL)||(start == NULL)||(check == NULL))
        return false;
    
    cout << "Given Maze:"<< endl<<maze->PrintMaze() << endl <<endl;
    
    if(DFS(start))
    {
        cout << "Solution Maze:" << endl;
        printSol();
        return true;
    }
    
    cout << "No solution found"<< endl;
    
    return false;
    
}

bool World::DFS(Maze::Node * curr_node)
{
    //base case
    if(curr_node == NULL)
        return false;
    
    if(check[curr_node->getxyCord().x][curr_node->getxyCord().y] == true)
        return false;
    
    check[curr_node->getxyCord().x][curr_node->getxyCord().y] = true;
    
    if ((curr_node->getxyCord().x == goal_coord.x) && (curr_node->getxyCord().y == goal_coord.y) )
    {
        //maze->changeChar(curr_node->getxyCord().x, curr_node->getxyCord().y, '$');
        //cout << maze->PrintMaze()<<endl<<endl<<endl;
        endNode = curr_node;   //save coordinates of goal node
        return true;
    }
    
    //maze->changeChar(curr_node->getxyCord().x, curr_node->getxyCord().y, '*');
    //cout << maze->PrintMaze()<<endl<<endl<<endl;
    
    
    curr_node->expandNode();        //expand this node to get surrounding nodes
    
    //check children and if found return true
    if( DFS( curr_node->getNorhChild() ) )
       return true;
    
    if( DFS( curr_node->getEastChild() ) )
        return true;
    
    if( DFS( curr_node->getSouthChild() ) )
        return true;
    
    if( DFS( curr_node->getWestChild() ) )
        return true;
    
    
    return false;
    
}

/*
World::BFS(Node *node, Maze *maze)
{
    
    //adjaceny list of size of possible nodes in maze
    Node *curr_node;
    list<Node*> queue;    //queue for BFS
    
    node->explored = 1;       //current node has been explored
    queue.push_back(node);
    
    list<Node*>::iterator i;
    while(!queue.empty())
    {
        curr_node = queue.front();  //update current node being looked at
        
        //check for solution
        if(curr_node->location.x, curr_node->location.y) == '.')
        {
            curr_node->correct_path = 1;
            world->goal_coords = curr_node->location;
            break;
        }
        curr_node->expand_node;          //expand node to use children
        queue.pop_front();
        
        //if unexplored and not a wall, add it to the queue
        if(curr_node->NorthChild.explored == 0 && maze.getChar(curr_node->NorthChild.location.x, curr_node->NorthChild.location.y) != '%')
            queue.push_back(curr_node->NorthChild);
        
        if(curr_node->EastChild.explored == 0 && maze.getChar(curr_node->EastChild.location.x, curr_node->EastChild.location.y) != '%')
            queue.push_back(curr_node->EastChild);
        
        if(curr_node->SouthChild.explored == 0 && maze.getChar(curr_node->SouthChild.location.x, curr_node->SouthChild.location.y) != '%')
            queue.push_back(curr_node->SouthChild);
        
        if(curr_node->WestChild.explored == 0 && maze.getChar(curr_node->WestChild.location.x, curr_node->WestChild.location.y) != '%')
            queue.push_back(curr_node->WestChild);    
        
    }
   */
void World::printSol()
{
    if(endNode == NULL)
    {
        cout << "No solution to print" << endl;
        return;
    }
    
    Maze::Node * temp;
    
    temp = endNode;
    
    while(temp != NULL)
    {
        maze->changeChar(temp->getxyCord().x,temp->getxyCord().y,'.');
        temp = temp->getParent();
    }
    
    cout << maze->PrintMaze() << endl;
    
    
}







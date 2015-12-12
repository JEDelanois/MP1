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
    Hvalue = abs(maze->getGoalLocation().x -X ) + abs(maze->getGoalLocation().y -Y);
    
    if(p == NULL)
        height = 0;
    else
        height = p->height + 1;
   
   double value=  Astarval =  (Hvalue +  height);
    int temp;
    temp++;
    
}

Maze::Node::Node(xyCord loc, Maze * m, Node * p)
{
    location = loc;
    maze = m;;
    parent = p;
    Hvalue = abs(maze->getGoalLocation().x - loc.x ) + abs(maze->getGoalLocation().y - loc.y);
    
    if(p == NULL)
        height = 0;
    else
        height = p->height + 1;
    
    Astarval = (Hvalue + height);
}

int Maze::Node::getAstarValue()
{
    return Astarval;
}

int Maze::Node::getHuristicValue()
{
    return Hvalue;
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
    
    
    vector<Ghost> childGhosts;
    //get new ghosts
    
        for (int i = 0; i < (int)currGhosts.size(); i++)
        {
            Ghost temp = currGhosts[i];
            
            if(temp.direction ==  0)// if moving left idk why i cannotuse macros here
            {
                if(maze->getChar(temp.pos.x - 1, temp.pos.y) != '%')// if not a wall then continue in that direction
                {
                    //save last location
                    temp.lastpos.x = temp.pos.x;
                    temp.lastpos.y = temp.pos.y;
                    
                    //move to new location
                    temp.pos.x = temp.pos.x - 1;
                    temp.pos.y = temp.pos.y;
                }
                else{//flip directions
                    
                    //save last location
                    temp.lastpos.x = temp.pos.x;
                    temp.lastpos.y = temp.pos.y;
                    
                    //move to new location
                    temp.pos.x = temp.pos.x + 1;
                    temp.pos.y = temp.pos.y;
                    
                    temp.direction = 1;
                }
                
            }
            else{ //else if moving right
            
                if(maze->getChar(temp.pos.x + 1, temp.pos.y) != '%')// if not a wall then continue in that direction
                {
                    //save last location
                    temp.lastpos.x = temp.pos.x;
                    temp.lastpos.y = temp.pos.y;
                    
                    //move to new location
                    temp.pos.x = temp.pos.x + 1;
                    temp.pos.y = temp.pos.y;
                }
                else{//flip directions
                    
                    //save last location
                    temp.lastpos.x = temp.pos.x;
                    temp.lastpos.y = temp.pos.y;
                    
                    //move to new location
                    temp.pos.x = temp.pos.x - 1;
                    temp.pos.y = temp.pos.y;
                    
                    temp.direction = 0;
                }
            
            }
            childGhosts.push_back(temp);
        }
    
    
    
    //get north child
    if( ((location.y -1) >= 0) ) // check if in bounds
    {
        if( maze->getChar(location.x, location.y-1) != '%' )// no wall there
        {
            bool ghost = false;
            //if the child coresponds to ghost node then make it null
            for(int i = 0; i < (int)childGhosts.size(); i++ )
            {
                if((childGhosts[i].pos.x == location.x) && (childGhosts[i].pos.y == location.y-1) )
                    ghost = true;
                else if((childGhosts[i].lastpos.x == location.x) && (childGhosts[i].lastpos.y == location.y-1) )
                    ghost = true;
            }
    
            
            if(ghost  )//if node matches parent dont add or if there is a ghost dont add
                NorhChild = NULL;
            
            else
                NorhChild = new Node(location.x,location.y-1, maze, this);
            
            if(NorhChild != NULL)
                NorhChild->currGhosts = childGhosts;
            
        }
    }
    
    
    //get east child
    if((location.x +1) < maze->getXsize() )
    {
        if(maze->getChar(location.x+1, location.y) != '%' )// if there is a space add child
        {
            
            bool ghost = false;
            //if the child coresponds to ghost node then make it null
            for(int i = 0; i < (int)childGhosts.size(); i++ )
            {
                if((childGhosts[i].pos.x == location.x + 1) && (childGhosts[i].pos.y == location.y) )
                    ghost = true;
                else if((childGhosts[i].lastpos.x == location.x + 1) && (childGhosts[i].lastpos.y == location.y) )
                    ghost = true;
            }
            
            if( ghost  )
                EastChild = NULL;
            
            else
                EastChild = new Node(location.x+1, location.y, maze, this );
            
            if(EastChild != NULL)
                EastChild->currGhosts = childGhosts;
        }
    }
    
    
    //get south child
    if((location.y + 1) < maze->getYsize() )
    {
        if(maze->getChar(location.x, location.y+1) != '%' )// if there is a space add child
        {
            bool ghost = false;
            //if the child coresponds to ghost node then make it null
            for(int i = 0; i < (int)childGhosts.size(); i++ )
            {
                if((childGhosts[i].pos.x == location.x) && (childGhosts[i].pos.y == location.y + 1) )
                    ghost = true;
                else if((childGhosts[i].lastpos.x == location.x) && (childGhosts[i].lastpos.y == location.y + 1) )
                    ghost = true;
            }
            
            
            if(ghost)
                SouthChild = NULL;
        
            else
                SouthChild = new Node (location.x, location.y +1, maze, this);
            
            
            if(SouthChild != NULL)
                SouthChild->currGhosts = childGhosts;
        }

    }
    
    //get west child
    if((location.x -1) >= 0)
    {
        if(maze->getChar(location.x-1, location.y) != '%' )// if there is a space add child
        {
            bool ghost = false;
            //if the child coresponds to ghost node then make it null
            for(int i = 0; i < (int)childGhosts.size(); i++ )
            {
                if((childGhosts[i].pos.x == location.x -1 ) && (childGhosts[i].pos.y == location.y) )
                    ghost = true;
                else if((childGhosts[i].lastpos.x == location.x - 1) && (childGhosts[i].lastpos.y == location.y) )
                    ghost = true;
            }
            
            
            if(ghost)
                WestChild = NULL;
        
            else
                WestChild = new Node(location.x -1,location.y, maze,this);
            
            if(WestChild != NULL)
                WestChild->currGhosts = childGhosts;
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



int Maze::Node::getGhostVal()
{
    return ghostVal;
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
    
    
    //initialize goallocation and endlocation
    
    goalLocation.x = -1;
    goalLocation.y = -1;
    
    startLocation.x = -1;
    startLocation.y = -1;
    
    if((Xsize <= 0) || (Ysize<=0))
    {
        return;
    }
    
    for(int x = 0; x < Xsize; x++)
    {
        for(int y = 0; y < Ysize; y++)
        {
            if(cMap[y][x] == '.')
            {
                goalLocation.x = x;
                goalLocation.y = y;
            }
            
            if(cMap[y][x] == 'P')
            {
                startLocation.x = x;
                startLocation.y = y;
            }
            if(cMap[y][x] == 'G')
            {
                Ghost g;
                g.pos.x = x;
                g.pos.y = y;
                g.lastpos.x = -1;
                g.lastpos.y = -1;
                g.direction = (int)LEFT;
                
                startGhosts.push_back(g);
            }
        }
    }
    
    

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
    
    
    Node * temp = new Node(startLocation,this, NULL);
    
    temp->currGhosts = startGhosts; // get the starting positions of the new ghosts
    
    
    return temp;


    
}



xyCord Maze::getGoalLocation()
{
    return goalLocation;
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
        cout << "DFS Solution Maze:" << endl;
        printSol();
        return true;
    }
    
    cout << "DFS No solution found"<< endl;
    
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

bool World::runBFS()
{
    //refresh maze of old data
    deleteWorld();
    makeWorld(path);
    if ((maze == NULL) || (start == NULL) || (check == NULL))
        return false;
    /*	maze->changeChar(start->getxyCord().x, start->getxyCord().y, 'a');
     maze->changeChar(goal_coord.x, goal_coord.y, 'Y');*/
    cout << "Given Maze:" << endl << maze->PrintMaze() << endl << endl;
    
    if (BFS(start))
    {
        cout << "BFS Solution Maze:" << endl;
        printSol();
        return true;
    }
    
    cout << "BFS No solution found" << endl;
    
    return false;
}

bool World::BFS(Maze::Node * curr_node)
{
    if (curr_node == NULL)
        return false;
    
    list<Maze::Node*> queue;    //queue for BFS
    
    queue.push_back(curr_node);	//add first node to queue
    check[curr_node->getxyCord().x][curr_node->getxyCord().y] = true;	//mark node as visited
    
    while (!queue.empty())
    {
        curr_node = queue.front();  //update current node being looked at
        queue.pop_front();
        
        /*
        maze->changeChar(curr_node->getxyCord().x, curr_node->getxyCord().y, '.');
        cout << maze->PrintMaze()<<endl<<endl<<endl;
        */
        
        //check for solution
        if ((curr_node->getxyCord().x == goal_coord.x) && (curr_node->getxyCord().y == goal_coord.y))
        {
            endNode = curr_node;   //save coordinates of goal node
            return true;
        }
        curr_node->expandNode();          //expand node to use children
        expansions++;					  //update number of node expansions
        
        
        //if unexplored and not a wall, add it to the queue
        if ((curr_node->getNorhChild() != NULL) && (check[curr_node->getNorhChild()->getxyCord().x][curr_node->getNorhChild()->getxyCord().y] == false)){
            queue.push_back(curr_node->getNorhChild());
            check[curr_node->getNorhChild()->getxyCord().x][curr_node->getNorhChild()->getxyCord().y] = true;	//mark node as visited
        }
        
        if ((curr_node->getEastChild() != NULL) && (check[curr_node->getEastChild()->getxyCord().x][curr_node->getEastChild()->getxyCord().y] == false)){
            queue.push_back(curr_node->getEastChild());
            check[curr_node->getEastChild()->getxyCord().x][curr_node->getEastChild()->getxyCord().y] = true;	//mark node as visited
        }
        
        if ((curr_node->getSouthChild() != NULL) && (check[curr_node->getSouthChild()->getxyCord().x][curr_node->getSouthChild()->getxyCord().y] == false)){
            queue.push_back(curr_node->getSouthChild());
            check[curr_node->getSouthChild()->getxyCord().x][curr_node->getSouthChild()->getxyCord().y] = true;	//mark node as visited
        }
        
        if ((curr_node->getWestChild() != NULL) && (check[curr_node->getWestChild()->getxyCord().x][curr_node->getWestChild()->getxyCord().y] == false)){
            queue.push_back(curr_node->getWestChild());
            check[curr_node->getWestChild()->getxyCord().x][curr_node->getWestChild()->getxyCord().y] = true;	//mark node as visited
        }
        
    }
    return false;
}

bool World::runGreedy()
{
    //refresh maze of old data
    deleteWorld();
    makeWorld(path);
    
    if ((maze == NULL) || (start == NULL) || (check == NULL))
        return false;
    /*	maze->changeChar(start->getxyCord().x, start->getxyCord().y, 'a');
     maze->changeChar(goal_coord.x, goal_coord.y, 'Y');*/
    cout << "Given Maze:" << endl << maze->PrintMaze() << endl << endl;
    
    frontier.resize(0);
    frontier.push_back(start);

    if (Greedy(start))
    {
        cout << "Greedy Solution Maze:" << endl;
        printSol();
        return true;
    }
    
    cout << "Greedy No solution found" << endl;
    
    return false;

}

bool World::Greedy(Maze::Node *curr_node)
{
    
    if (curr_node == NULL)
        return false;
    
    
    
    check[curr_node->getxyCord().x][curr_node->getxyCord().y] = true;
    
    while (!frontier.empty())
    {
        //sort queue
        if((int)frontier.size() > 1) // if there is more than one element
        {
            for(int i = 0; i < (int)frontier.size() - 1; i++) // this gets the node with the smallest hurisic valute
            {
                if(frontier[i +1]->getHuristicValue() > frontier[i]->getHuristicValue())
                {
                    Maze::Node * temp = frontier[i +1];
                    frontier[i +1] = frontier[i];
                    frontier[i] = temp;
                }
            }
        }
        
        
        curr_node = frontier.back();
        frontier.pop_back();  //update current node being looked at
       
        
        /*
        maze->changeChar(curr_node->getxyCord().x, curr_node->getxyCord().y, '.');
        cout << maze->PrintMaze()<<endl<<endl<<endl;
         */
         
        
        
        //check for solution
        if ((curr_node->getxyCord().x == goal_coord.x) && (curr_node->getxyCord().y == goal_coord.y))
        {
            endNode = curr_node;   //save coordinates of goal node
            return true;
        }
        curr_node->expandNode();          //expand node to use children
        expansions++;
        
        
        
        //if unexplored and not a wall, add it to the queue
        if ((curr_node->getNorhChild() != NULL) && (check[curr_node->getNorhChild()->getxyCord().x][curr_node->getNorhChild()->getxyCord().y] == false)){
            frontier.push_back(curr_node->getNorhChild());
            check[curr_node->getNorhChild()->getxyCord().x][curr_node->getNorhChild()->getxyCord().y] = true;	//mark node as visited
        }
        
        if ((curr_node->getEastChild() != NULL) && (check[curr_node->getEastChild()->getxyCord().x][curr_node->getEastChild()->getxyCord().y] == false)){
            frontier.push_back(curr_node->getEastChild());
            check[curr_node->getEastChild()->getxyCord().x][curr_node->getEastChild()->getxyCord().y] = true;	//mark node as visited
        }
        
        if ((curr_node->getSouthChild() != NULL) && (check[curr_node->getSouthChild()->getxyCord().x][curr_node->getSouthChild()->getxyCord().y] == false)){
            frontier.push_back(curr_node->getSouthChild());
            check[curr_node->getSouthChild()->getxyCord().x][curr_node->getSouthChild()->getxyCord().y] = true;	//mark node as visited
        }
        
        if ((curr_node->getWestChild() != NULL) && (check[curr_node->getWestChild()->getxyCord().x][curr_node->getWestChild()->getxyCord().y] == false)){
            frontier.push_back(curr_node->getWestChild());
            check[curr_node->getWestChild()->getxyCord().x][curr_node->getWestChild()->getxyCord().y] = true;	//mark node as visited
        }
        
        
    }
    
    return false;
    
}


bool World::runAstar()
{
    //refresh maze of old data
    deleteWorld();
    makeWorld(path);
    
    if ((maze == NULL) || (start == NULL) || (check == NULL))
        return false;
    /*	maze->changeChar(start->getxyCord().x, start->getxyCord().y, 'a');
     maze->changeChar(goal_coord.x, goal_coord.y, 'Y');*/
    cout << "Given Maze:" << endl << maze->PrintMaze() << endl << endl;
    
    frontier.resize(0);
    frontier.push_back(start);

    if (Astar())
    {
        cout << "A* Solution Maze:" << endl;
        printSol();
        return true;
    }
    
    cout << "A* No solution found" << endl;
    
    return false;
    
}

bool World::Astar()
{
    
    
    
    while (!frontier.empty())
    {
        //sort queue
        if((int)frontier.size() > 1) // if there is more than one element
        {
            for(int i = 0; i < (int)frontier.size() - 1; i++) // this gets the node with the smallest hurisic valute
            {
                if(frontier[i + 1]->getAstarValue() > frontier[i]->getAstarValue())
                {
                    Maze::Node * temp = frontier[i +1];
                    frontier[i +1] = frontier[i];
                    frontier[i] = temp;
                }
            }
        }
        
        
        Maze::Node * curr_node = frontier.back();
        frontier.pop_back();  //update current node being looked at
        

        
        
        
        //check for solution
        if ((curr_node->getxyCord().x == goal_coord.x) && (curr_node->getxyCord().y == goal_coord.y))
        {
            endNode = curr_node;   //save coordinates of goal node
            return true;
        }
        curr_node->expandNode();          //expand node to use children
        expansions++;
        
        
        
        //if unexplored and not a wall, add it to the queue
        if (curr_node->getNorhChild() != NULL){
            frontier.push_back(curr_node->getNorhChild());
            
            for(int i = 0; i < (int)frontier.size() - 1; i++) // this gets the node with the smallest hurisic valute
            {
                if( (frontier[(int)frontier.size()-1]->getxyCord().x == frontier[i]->getxyCord().x) &&
                    (frontier[(int)frontier.size()-1]->getxyCord().y == frontier[i]->getxyCord().y) &&
                    (frontier[(int)frontier.size()-1]->getAstarValue() == frontier[i]->getAstarValue()) &&
                    (frontier[(int)frontier.size()-1]->height == frontier[i]->height) )
                {
                   
                    frontier.pop_back();// if repeated state then remove it
                }
            }
            
        }
        
        if (curr_node->getEastChild() != NULL){
            frontier.push_back(curr_node->getEastChild());
            
            for(int i = 0; i < (int)frontier.size() - 1; i++) // this gets the node with the smallest hurisic valute
            {
                if( (frontier[(int)frontier.size()-1]->getxyCord().x == frontier[i]->getxyCord().x) &&
                   (frontier[(int)frontier.size()-1]->getxyCord().y == frontier[i]->getxyCord().y) &&
                   (frontier[(int)frontier.size()-1]->getAstarValue() == frontier[i]->getAstarValue()) &&
                   (frontier[(int)frontier.size()-1]->height == frontier[i]->height) )
                {
                    
                    frontier.pop_back();// if repeated state then remove it
                }
            }
        }
        
        if (curr_node->getSouthChild() != NULL){
            frontier.push_back(curr_node->getSouthChild());
            
            for(int i = 0; i < (int)frontier.size() - 1; i++) // this gets the node with the smallest hurisic valute
            {
                if( (frontier[(int)frontier.size()-1]->getxyCord().x == frontier[i]->getxyCord().x) &&
                   (frontier[(int)frontier.size()-1]->getxyCord().y == frontier[i]->getxyCord().y) &&
                   (frontier[(int)frontier.size()-1]->getAstarValue() == frontier[i]->getAstarValue()) &&
                   (frontier[(int)frontier.size()-1]->height == frontier[i]->height) )
                {
                
                    frontier.pop_back();// if repeated state then remove it
                }
            }
        }
        
        if (curr_node->getWestChild() != NULL){
            frontier.push_back(curr_node->getWestChild());
            
            for(int i = 0; i < (int)frontier.size() - 1; i++) // this gets the node with the smallest hurisic valute
            {
                if( (frontier[(int)frontier.size()-1]->getxyCord().x == frontier[i]->getxyCord().x) &&
                   (frontier[(int)frontier.size()-1]->getxyCord().y == frontier[i]->getxyCord().y) &&
                   (frontier[(int)frontier.size()-1]->getAstarValue() == frontier[i]->getAstarValue()) &&
                   (frontier[(int)frontier.size()-1]->height == frontier[i]->height) )
                {
                
                    frontier.pop_back(); // if repeated state then remove it
                }
            }
        }
        
        
        
    }
    
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







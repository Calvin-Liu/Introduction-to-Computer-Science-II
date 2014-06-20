//
//  File.cpp
//  CS 32 Hwk 2
//
//  Created by Calvin Liu on 2/3/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <queue>
#include <iostream>
using namespace std;

class Coord //queue of this class
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}    //initialized
    int r() const { return m_r; }   //simple return values
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue <Coord> q;
    q.push(Coord(sr,sc));         //push the starting point onto the queue
    maze[sr][sc] = 'H';
    while(!q.empty())
    {
        Coord qCoordnow = q.front();
        if(qCoordnow.r() == er && qCoordnow.c() == ec)
        {
            return true;
        }
        cout << qCoordnow.r() << ' ' << qCoordnow.c() << endl;
        q.pop();  //remove top from queue
        //NORTH
        if(maze[qCoordnow.r()-1][qCoordnow.c()] != 'X' && maze[qCoordnow.r()-1][qCoordnow.c()] != 'H')
        {
            maze[qCoordnow.r()-1][qCoordnow.c()]= 'H'; //move H to that spot
            q.push(Coord(qCoordnow.r()-1,qCoordnow.c()));
        }
        //SOUTH
        if(maze[qCoordnow.r()+1][qCoordnow.c()] != 'X' && maze[qCoordnow.r()+1][qCoordnow.c()] != 'H')
        {
            maze[qCoordnow.r()+1][qCoordnow.c()]= 'H'; //move H to that spot
            q.push(Coord(qCoordnow.r()+1, qCoordnow.c()));
        }
        //WEST
        if(maze[qCoordnow.r()][qCoordnow.c()-1] != 'X' && maze[qCoordnow.r()][qCoordnow.c()-1] != 'H')
        {
            maze[qCoordnow.r()][qCoordnow.c()-1] = 'H'; //move H to that spot
            q.push(Coord(qCoordnow.r(), qCoordnow.c()-1));
        }
        //EAST
        if(maze[qCoordnow.r()][qCoordnow.c()+1] != 'X' && maze[qCoordnow.r()][qCoordnow.c()+1] != 'H')
        {
            maze[qCoordnow.r()][qCoordnow.c()+1]= 'H'; //move H to that spot
            q.push(Coord(qCoordnow.r(), qCoordnow.c()+1));
        }
    }
    return false;
}

/*
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
	
    if (pathExists(maze, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
*/
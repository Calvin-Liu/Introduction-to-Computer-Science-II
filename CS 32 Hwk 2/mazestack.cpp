//
//  main.cpp
//  CS 32 Hwk 2
//
//  Created by Calvin Liu on 2/3/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Coord //stack of this class
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
    stack <Coord> s;
    s.push(Coord(sr,sc)); //Push sr,sc onto the coordinate stack and mark it with 'H'
    maze[sr][sc] = 'H';
    while(!s.empty())
    {
        Coord coordnow = s.top();
        s.pop();
        if(coordnow.r() == er && coordnow.c() == ec)//if your 'H' is at the end point return true
        {
            return true;
        }
        //NORTH
        if(maze[coordnow.r()-1][coordnow.c()] != 'X' && maze[coordnow.r()-1][coordnow.c()] != 'H')
        {
            maze[coordnow.r()-1][coordnow.c()]= 'H'; //move H to that spot
            s.push(Coord(coordnow.r()-1,coordnow.c()));
        }
        //SOUTH
        if(maze[coordnow.r()+1][coordnow.c()] != 'X' && maze[coordnow.r()+1][coordnow.c()] != 'H')
        {
            maze[coordnow.r()+1][coordnow.c()]= 'H'; //move H to that spot
            s.push(Coord(coordnow.r()+1, coordnow.c()));
        }
        //WEST
        if(maze[coordnow.r()][coordnow.c()-1] != 'X' && maze[coordnow.r()][coordnow.c()-1] != 'H')
        {
            maze[coordnow.r()][coordnow.c()-1] = 'H'; //move H to that spot
            s.push(Coord(coordnow.r(), coordnow.c()-1));
        }
        //EAST
        if(maze[coordnow.r()][coordnow.c()+1] != 'X' && maze[coordnow.r()][coordnow.c()+1] != 'H')
        {
            maze[coordnow.r()][coordnow.c()+1]= 'H'; //move H to that spot
            s.push(Coord(coordnow.r(), coordnow.c()+1));
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
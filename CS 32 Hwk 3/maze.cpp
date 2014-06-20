//
//  File.cpp
//  CS 32 Hwk 3
//
//  Created by Calvin Liu on 2/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//


#include <iostream>
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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    Coord coordnow = Coord(sr,sc);
    if (coordnow.r() == er  &&  coordnow.c() == ec)
    {
        return true;
    }
    maze[coordnow.r()][coordnow.c()] = 'H';
    //NORTH
    if(maze[coordnow.r()-1][coordnow.c()] != 'X' && maze[coordnow.r()-1][coordnow.c()] != 'H')
    {
        if(pathExists(maze, coordnow.r()-1, coordnow.c(), er, ec))
            return true;
    }
    //SOUTH
    if(maze[coordnow.r()+1][coordnow.c()] != 'X' && maze[coordnow.r()+1][coordnow.c()] != 'H')
    {
        if(pathExists(maze, coordnow.r()+1, coordnow.c(), er, ec))
            return true;
    }
    //WEST
    if(maze[coordnow.r()][coordnow.c()-1] != 'X' && maze[coordnow.r()][coordnow.c()-1] != 'H')
    {
        if(pathExists(maze, coordnow.r(), coordnow.c()-1, er, ec))
            return true;
    }
    //EAST
    if(maze[coordnow.r()][coordnow.c()+1] != 'X' && maze[coordnow.r()][coordnow.c()+1] != 'H')
    {
        if(pathExists(maze, coordnow.r(), coordnow.c()+1, er, ec))
            return true;
    }
    return false;
}


//int main()
//{
//    char maze[10][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X'},
//        { 'X','.','.','.','.','.','.','.','.','X'},
//        { 'X','X','.','X','.','X','X','X','X','X'},
//        { 'X','.','.','X','.','X','.','.','.','X'},
//        { 'X','.','.','X','.','.','.','X','.','X'},
//        { 'X','X','X','X','.','X','X','X','X','X'},
//        { 'X','.','.','X','.','.','.','X','.','X'},
//        { 'X','.','.','X','X','.','X','X','.','X'},
//        { 'X','.','.','.','X','.','.','.','.','X'},
//        { 'X','X','X','X','X','X','X','X','X','X'}
//    };
//	
//    if (pathExists(maze, 6,4, 1,1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}

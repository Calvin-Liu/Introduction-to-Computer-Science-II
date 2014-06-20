//
//  main.cpp
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

// robots.cpp

 
#include "Robot.h"
#include "EnergySource.h"
#include "Valley.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

// You can use whatever main routine you want.  In fact, try different
// things that will thoroughly test your classes.  This main routine is
// the one that the sample executable uses.

int main()
{
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a 10x10 valley
    Valley v(1, 10);
    
    // Populate it with three robots
    v.addRobot("Abner", 0, 0, SOUTH);
    //v.addRobot("Betty", 9, 9, NORTH);
    //v.addRobot("Chris", 0, 9, SOUTH);
    
    // Add energy sources at (2,2), (2,5), (2,8), (5,2), ..., (8,8)
    for (int r = 2; r < v.rows(); r += 3)
        for (int c = 2; c < v.cols(); c += 3)
            v.addEnergySource(r, c);
    
    // Step until all robots are dead, displaying the valley each time
    do
    {
        v.display();
        cout << endl;
        cout << "Press Enter to continue ";
        cin.ignore(10000, '\n');
    } while(v.step());

    cout << "All robots are dead" << endl;
}
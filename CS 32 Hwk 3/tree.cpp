//
//  tree.cpp
//  CS 32 Hwk 3
//
//  Created by Calvin Liu on 2/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//


#include <iostream>
#include <string>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if(n2 == 0)
    {
        return 0;
    }
    if(n1 == 0)
    {
        return 0;
    }
    if(a1[0] == a2[0])
    {
        int k = (countIncludes(a1+1, n1-1, a2+1, n2-1) + countIncludes(a1+1, n1-1, a2, n2));
        if(n2 != 1)
        {
            return k;
        }
        if(n2 == 1)
        {
            return k+1;
        }
    }
    else
    {
        return countIncludes(a1+1, n1-1, a2, n2);
    }
    return 0;
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void partition(double a[], int n, double separator,
               int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
	
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator
	
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

void partition(double a[], int n, double separator,
               int& firstNotGreater, int& firstLess);

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    if(n <= 1)
    {
        return;
    }
    
    int FNG;
    int FL;
    
    partition(a, n, a[n/2], FNG, FL);
    order(a, FNG);
    order(a, (n-FL));
}


//int countIncludes(const double a1[], int n1, const double a2[], int n2);
//int main()
//{
//    const double a1[] = {10, 50, 40, 20, 50, 40, 30};
//    const double a2[] = {50};
//    if(countIncludes(a1, 7, a2, 1) == 2)
//    {
//        cout << "countIncludes works";
//    }
//}

//void order(double a[], int n);
//int main()
//{
//    double a[] = {10, 50, 40, -20, 50, 40, 30, -8};
//    order(a, 7);
//    for(int k = 0; k < 7; k++)
//    {
//        cout << a[k] << endl;
//    }
//}




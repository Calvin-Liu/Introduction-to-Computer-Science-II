//
//  File.cpp
//  CS 32 Hwk 3
//
//  Created by Calvin Liu on 2/7/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include <iostream>
using namespace std;

// Return true if any of the array elements is negative, false
// otherwise.
bool anyNegative(const double a[], int n)
{
    if(n <= 0)                       //check to see if n is -1
    {
        n = 0;
        return false;
    }
    if(a[0] < 0)                    //if the element is negative
    {
        return true;                //anyNegative will be true
    }
    return anyNegative(a+1, n-1);          //loop through and return
}

// Return the number of negative elements in the array.
int countNegatives(const double a[], int n)
{
    if(n <= 0)
    {
        n = 0;
        return 0;
    }
    if(n == 1 && a[0] > 0)
    {
        return 0;
    }
    if(a[0] < 0)
    {
        return (1 + countNegatives(a+1, n-1));           //[4][7][-8][-9]
    }
    return countNegatives(a+1, n-1);
}

// Return the subscript of the first negative element in the array.
// If no element is negative, return -1.
int firstNegative(const double a[], int n)
{
    if(n <= 0)
    {
        n = 0;
        return -1;                      //[0], [8], [-5],[3],[-9]
    }
    if(a[0] < 0)
    {
        return 0;
    }
    else
    {
        if(firstNegative(a+1, n-1) == -1)
        {
            return -1;
        }
        return (1 + firstNegative(a+1, n-1));
    }
}

// Return the subscript of the largest element in the array.  If
// more than one element has the same largest value, return the
// smallest subscript of such an element.  If the array is empty,
// return -1.
int indexOfMax(const double a[], int n)
{
    if(n <= 0)
    {
        n = 0;
        return -1;
    }
    if(n == 1)
    {
        return 0;
    }
    if(a[0] < a[n-1])
    {
        return (1 + indexOfMax(a+1, n-1));
    }
    else
    {
        return (indexOfMax(a, n-1));
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if(n2 == 0)
    {
        return true;
    }
    if(n1 <= 0 || n2 < 0)
    {
        n1 = 0;
        n2 = 0;
        return false;
    }
    if(a1[0] == a2[0])
    {
        return includes(a1+1, n1-1, a2+1, n2-1);
    }
    else
    {
        return includes(a1+1, n1-1, a2, n2);
    }
}

//bool anyNegative(const double a[], int n);
//int main()
//{
//    const double a[] = {1, -2};
//    if(anyNegative(a, 5))
//    {
//        cout << "anyNegative works";
//    }
//}

//int countNegatives(const double a[], int n);
//int main()
//{
//    const double a[] = {0, 1, -2, 5, 6, -8, -7};
//    cout << countNegatives(a, 7);
//}

//int firstNegative(const double a[], int n);
//int main()
//{
//    const double a[] = {1, 1, -2, -5, -6, -8};
//    cout << firstNegative(a, 6);
//}

//int indexOfMax(const double a[], int n);
//int main()
//{
//    const double a[] = {-1, 5, 3, 7, 13, 8};
//    cout << indexOfMax(a, 6);
//}

//bool includes(const double a1[], int n1, const double a2[], int n2);
//int main()
//{
//    const double a1[] = {0, 1, 2, 5, 6, -8};
//    const double a2[] = {1, -2, -8};
//    if(includes(a1, 6, a2, 3))
//    {
//        cout << "includes works";
//    }
//}

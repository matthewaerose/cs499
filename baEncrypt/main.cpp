/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sslt
 *
 * Created on January 20, 2018, 7:59 PM
 */

#include <cstdlib>
#include <math.h>
#include <complex>
#include <iostream>

using namespace std;

/*
 * 
 */

void testCoprime(int a, int b);

int main(int argc, char** argv) {

    testCoprime(10,3);
    
    return 0;
}

void testCoprime(int big, int small)
{
    float sqr = sqrt( (float)big );
    float flr = floor( sqr );
    
    cout << "sqr : " << sqr <<
            "\nflr : " << flr <<
            "\nbig : " << big << endl;
    
//    std::ne
//    int round = (int)std::round(big);
//    int test = std::rostd::sqrt(big));
}
//
//  main.c
//  402P2
//
//  Created by Raphael Reyna on 3/22/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#import <math.h>
#import "NumericalMethods.h"

//ODE System, this is a vector function, takes the independent param (scalar),
//the solution vector, and a temp vector for dirty work.
//(this temp vector is not declared in the function so that it may be reused)
double *ODE(double x, double *y, double *System){
    System[0] = y[1];
    System[1] = -y[0];
    return System;
}

//Standard, main function, nothing interesting here.
int main(int argc, const char * argv[])
{
    double initConditions[2] = {0.0, 1.0};
    double *i = (double *)&initConditions;
    ODEContext *context = makeODEContext(0.0001, 2, i, ODE);
    eulersMethod(context, 0, M_PI_4);
}





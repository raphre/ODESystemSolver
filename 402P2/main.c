//
//  main.c
//  402P2
//
//  Created by Raphael Reyna on 3/22/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include <stdio.h>
#import <math.h>

#pragma mark Numerical Methods -

#pragma mark ODE Solvers
//This method takes an ODE System (a function which returns a vector), the solution
//vector (which will be overwritten in each time step), the size of the solution vector,
//the bounds for the interval over which we will be solving the system, and the
//number of desired steps.
void eulersMethod(double *(*f)(double, double*, double*), double *w, int c, double a, double b, int n){
    double h = (b-a)/(double)n; //compute the stepsize
    double ODESystem[c]; //the array that will hold temp ODE system values
    
    for (int k = 0; k <= n; k++){ //time step loop
        double t = a + k*h; //update time step
        
        for (int i = 0; i < c; i++) { //iterates the solver method over the solution vector.
            w[i] = w[i] + h*(f(t, w, (double *)&ODESystem)[i]); //eulers method for a vector.
            if (i == 0) {
                printf("%f\n", w[i]);
            }
        }
    }
}

double w[2] = {1, 1};
double b = 1;

#pragma mark Root Finding Methods
//The Secant Method for finding roots, requires a function to find the root of, the error tolerance,
//and a pointer to the bounding root interval, notice this function is of type void,
//this is because it replaces the final interval value with the approximated root.
void secantMethod(double (*f)(double), double *x_0, double *x_1, double epsilon){
    if (fabs(*x_0 - *x_1) > epsilon){
        double temp = *x_1;
        *x_1 = (*x_1 - f(*x_1)*(*x_1 - *x_0)/(f(*x_1) - f(*x_0)));
        secantMethod(f, &temp, x_1, epsilon);
    }
}

void bisectionMethod(double (*f)(double), double *xa, double *xb, double epsilon)
{
    double xm, fa, fm;
    
    fa = f(*xa);
    while (xb - xa > epsilon)
    {
        xm = (*xa + *xb) / 2;
        fm = f(xm);
        if (fm == 0.0)
            break;
        else if (fa*fm > 0)
        {
            xa = &xm;
            fa = fm;
        }
        else {
            xb = &xm;
        }
    }
    *xb = xm;
}

#pragma mark -

#pragma mark Auxilary Functions
//ODE System, this is a vector function, takes the independent param (scalar),
//the solution vector, and a temp vector for dirty work.
//(this temp vector is not declared in the function so that it may be reused)
double *ODE(double x, double *y, double *System){
    System[0] = y[1];
    System[1] = -2*(y[0]*y[0])+8*(x*x)*(y[0]*y[0]*y[0]);
    return System;
}

//Out of laziness and time contraints we hardcode these values.
//Our function that turns the BVP into a root-finding problem.
double g(double x){
    //set the second initial condition in the solution vector to x
    w[1] = x;
    //Approximate the solution using x
    eulersMethod(ODE, (double *)&w, 2, 0, 1, 40);
    //We want to feed this back in so we store it since
    //we will be reseting the solution vector.
    double a = w[0];
    //We reset the solution vector back to its original
    //state to try again with a better guess as to what x is.
    w[0] = 1;
    //We return the error.
    return fabs(a - 0.5);
}

//Solves the root-finding problem.
void shoot(){
    //This is for our interval
    double a = 0;
    //secantMethod(g, &a, &b, 0.0155);
    bisectionMethod(g, &a, &b, 0.025);
}
#pragma mark -


int isInHood(double a, double b, double epsilon){
    if (fabs(a - b) < epsilon){
        return 1;
    }
    
    return 0;
}

int not(int a){
    if (a == 0){
        return 1;
    }
    return 0;
}

//Standard, main function, nothing interesting here.
int main(int argc, const char * argv[])
{
    int K = 100;
    int b = 0;
    for (int i = 0; i < K; i++) {
        int b = isInHood(1.0/(double)i, 0, .02);
    }
}





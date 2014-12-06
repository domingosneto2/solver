
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

/**
 * testamos aqui uma formula para obter qual 
 */
double get_si( double N, double i )
{
    return N * i - i * (i + 1.0) / 2.0;
}

double get_i( double N, double Si )
{
    return N - 0.5 - sqrt( ( N - 0.5 ) * ( N - 0.5 ) - 2.0 * Si );
}

double get_j( double N, double Si )
{
    double i = get_i( N, Si );
    double f = floor( i );
    
    double Sf = get_si( N, f );
    
    double delta = Si - Sf;
    double j = f + 1 + delta;
    return j;
}


void printUsage()
{
    cout << "Usage:  test_si N Si" << endl;
}

int main( int argc, char **argv )
{
    if ( argc != 3 )
    {
        printUsage();
        return 1;
    }
    
    int N     = atoi( argv[1] );
    double Si = atof( argv[2] );
    
    cout << "N : " << N << endl;
    cout << "Si: " << Si << endl;
    
    double i = get_i( N, Si );
    double j = get_j( N, Si );
    
    cout << "i : " << floor(i) << endl;
    cout << "j : " << j << endl;
    return 0;
}
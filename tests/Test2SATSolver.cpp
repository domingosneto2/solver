
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <sat/2SATSolver.h>
#include <util/Timer.h>
#include <util/Random.h>
#include <sat/SATLIBParser.h>

//-----------------------------------------------------------------------------
int test2SATSolver( int argc, char **argv )
{
	if ( argc != 2 )
	{
		cout << "Usage: solver test2SATSolver filename" << endl;
		return 1;
	}

	Random::s_randomize();

	SATLIBParser parser;

	cout << "Parsing input file..." << endl;
	
	Timer timer2;

	bool res = parser.open( argv[1] );
	if ( res == false )
	{
		cout << "Unable to open input file" << endl;
		return 1;
	}

	CNFFormula formula = parser.getFormula();    

	cout << "OK, took " << timer2.evaluate() << " milisseconds" << endl;
    
    TwoSATSolver solver( formula );

	Interpretation interpretation( 1 );

	cout << "Solving..." << endl;
	timer2.reset();
    
    if ( solver.solve( interpretation ) == false )
	{
		cout << "Unable to find a solution" << endl;
		return 1;
	}

	cout << "OK, took " << timer2.evaluate() << " milisseconds" << endl;
    
    cout << "-----------" << endl;
    
    cout << "The result: " << formula.getValue( interpretation ) << endl;
    cout << "The values: " << endl;

	for ( int i = 0; i < formula.getNumVars(); i++ )
	{
		cout << interpretation.getValue( i ) << " ";
	}

	return 0;
}
//-----------------------------------------------------------------------------


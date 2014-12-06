
#include <iostream>
#include <sat/BasicCNFSolver.h>
#include <sat/CNFFormula.h>


int testCNFFormula( int argc, char **argv )
{
    CNFFormula formula;
    
    // Create the formula a && b && !c && d
    
    formula.init();
    
	formula.initClause( 0 );
    formula.initClauseVar( 0, 0, true, 0 );
    
    formula.initClause( 1 );
    formula.initClauseVar( 1, 0, true, 1 );
    
    formula.initClause( 2 );
    formula.initClauseVar( 2, 0, false, 2 );
    
    formula.initClause( 3 );
    formula.initClauseVar( 3, 0, true, 3 );
    
    
    BasicCNFSolver solver;

	Interpretation interpretation( 4 );
    
    solver.solve( &formula, interpretation );
    
    cout << "-----------" << endl;
    
    cout << "The result: " << formula.getValue( interpretation ) << endl;
    cout << "The values: " << interpretation.getValue( 0 ) << " "  <<
		                      interpretation.getValue( 1 ) << " " << 
                              interpretation.getValue( 2 ) << " " << 
							  interpretation.getValue( 3 ) << endl;

	if ( formula.getValue( interpretation ) != true )
	{
		return 1;
	}

	return 0;
}


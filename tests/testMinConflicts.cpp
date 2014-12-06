
#include <iostream>

#include <sat/SATLIBParser.h>
#include <util/Random.h>
#include <csp/MinConflicts.h>
#include <csp/NQueensCSP.h>
#include <csp/RandomCSP.h>
#include <sat/Interpretation.h>
#include <csp/CSPProblem.h>
#include <sat2csp/DualEncodingSAT2CSP.h>

//CSPProblem *createProblem( char *filename )
//{
//}


int testMinConflicts( int argc, char ** argv )
{
	Random::s_randomize();
	
	if ( argc != 2 )
	{
		cout << "Usage: " << argv[0] << " filename" << endl;
		return 1;
	}
	
	char *filename = argv[1];

	cout << "Initializing..." << endl;
	/*CSPProblem *problem = NQueensCSPFactory::create( 1024 );*/
	
	CNFFormula formula;
	SATLIBParser parser;

	cout << "Filename:    " << filename << endl;
	cout << "Parsing... ";

	if ( !parser.open( filename ) )
	{
		cout << "Error: Unable to parse file"<< endl;
		return false;		
	}	

	formula = parser.getFormula();

	
	DualEncodingSAT2CSP *enc = DualEncodingSAT2CSP::create();
	enc->setFormula( &formula );
	
	CSPProblem *problem = enc->getProblem();
	
	cout << "Running arc-consistency" << endl;
	problem->arcConsistency();
	cout << "OK" << endl;
	
	
	MinConflicts *minConflicts = MinConflicts::create( problem );
	minConflicts->setNumSidewaysSteps( problem->getNumVars() * problem->getNumVars() );
	
	//int tries = problem->getNumVars();
	bool res;
	int tries = 1;

	for ( int i = 0; i < tries; i++ )
	{
		// Initialize a random assignment
		CSPInterpretation interpretation1( problem->getNumVars() );
		CSPInterpretation interpretation2( problem->getNumVars() );
		
		for ( int i = 0; i < problem->getNumVars(); i++ )
		{
			interpretation1.setVariableValue( i, Random::s_randomInt( 0, problem->getDomainList()->getDomainSize( i ) ) );
		}
		
		cout << "Calling local search" << endl;
		// Call local search
		minConflicts->localSearch( interpretation1, interpretation2 );
		
		// check result
		res = problem->isSatisfied( interpretation2 );
		if ( res )
		{
			break;
		}
	}
	cout << "Result: " << res << endl;

	return res ? 0 : 1;

}
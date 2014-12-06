
#include <iostream>
#include <csp/BasicCSP.h>
#include <csp/CrosswordsCSP.h>

//-----------------------------------------------------------------------------
/* Here we test the CSPProblem and the BasicCSP constructs, using the 
 * crosswords problem.  The problem consists in, given a dictionary with N
 * words with length L, find an assignment to a board with size NxN such that
 * each row and each column will contain a word from the dictionary, without
 * repetition.
 */
static char *dictionary[] = { "add", "ado", "age", "aid", "and", "bag", "dau", "dog", "dug", "ear", "eft", "nao", "rat" };
static int dictSize = 13;
static int wordlen = 3;

int testBasicCSP( int argc, char **argv )
{
	cout << "testBasicCSP" << endl;
	// Setup the domains of all variables
	CSPProblem *problem = CrosswordsCSPFactory::create( (const char **)dictionary, dictSize, wordlen );

	// Now, we set an interpretation
	CSPInterpretation interpretation( 6 );

	interpretation.setVariableValue( 0, 0 );
	interpretation.setVariableValue( 1, 11 );
	interpretation.setVariableValue( 2, 8 );
	interpretation.setVariableValue( 3, 4 );
	interpretation.setVariableValue( 4, 6 );
	interpretation.setVariableValue( 5, 7 );

	int n = problem->getNumSatisfiedConstraints( interpretation );

	if ( n != problem->getConstraintList()->getNumConstraints() )
	{
		cout << "Not all constraints satisfied!" << endl;
		cout << "n = " << n << endl;
		return 1;
	}

	cout << "OK!" << endl;

	problem->release();

	return 0;
};


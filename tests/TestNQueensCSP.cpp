
#include <iostream>
#include <csp/NQueensCSP.h>

//-----------------------------------------------------------------------------
static int testFailure( CSPProblem *problem )
{
	cout << "\ttestFailure" << endl;
	CSPInterpretation interpretation;

	interpretation.setNumVariables( 4 );
	interpretation.setVariableValue( 0, 2 );
	interpretation.setVariableValue( 1, 3 );
	interpretation.setVariableValue( 2, 0 );
	interpretation.setVariableValue( 3, 2 );

	if ( problem->isSatisfied( interpretation ) )
	{		
		cout << "\tErro" << endl;
		return 1;
	}
	else
	{
		cout << "\tOK" << endl;
		return 2;
	}
}
//-----------------------------------------------------------------------------
static int testSuccess( CSPProblem *problem )
{
	cout << "\ttestSuccess" << endl;
	CSPInterpretation interpretation;

	interpretation.setNumVariables( 4 );
	interpretation.setVariableValue( 0, 1 );
	interpretation.setVariableValue( 1, 3 );
	interpretation.setVariableValue( 2, 0 );
	interpretation.setVariableValue( 3, 2 );

	if ( problem->isSatisfied( interpretation ) )
	{		
		cout << "\tOK" << endl;
		return 0;
	}
	else
	{
		cout << "\tErro" << endl;
		return 1;
	}
}
//-----------------------------------------------------------------------------
int testNQueensCSP( int argc, char **argv )
{
	cout << "testNQueensCSP" << endl;
	CSPProblem *problem = NQueensCSPFactory::create( 4 );

	int res1 = testSuccess( problem );
	int res2 = testFailure( problem );	
	
	problem->release();

	return res1 + res2;	
}
//-----------------------------------------------------------------------------


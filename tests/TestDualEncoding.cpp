
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <iostream>
#include <sat2csp/DualEncodingSAT2CSP.h>
#include <sat/SATLIBParser.h>
#include <aco/AntSolver.h>
#include <util/Random.h>
#include <csp/BasicCSP.h>



int testDualEncoding( int argc, char **argv )
{
	Random::s_randomize();
	CNFFormula formula;
	SATLIBParser parser;

	bool res = parser.open( "tests/satlib2.txt" );
	if ( res == false )
	{
		cout << "Mal, sap�o" << endl;
		return 1;
	}

	formula = parser.getFormula();
	DualEncodingSAT2CSP *enc = DualEncodingSAT2CSP::create();

	enc->setFormula( &formula );

	CSPProblem *problem = enc->getProblem();

	int numVars = problem->getNumVars();
	int numConstraints = problem->getConstraintList()->getNumConstraints();

	cout << "Problem has " << numVars << " variables, " << " and " << numConstraints << " constraints." << endl;

	Interpretation interpretation( formula.getNumVars() );
	CSPInterpretation cspInterpretation( problem->getNumVars() );

	AntSolver solver;

	solver.setAlpha( 2 );
	solver.setBeta( 10 );
	solver.setMaxPheromone( 10 );
	solver.setMinPheromone( 1 );
	solver.setNumAnts( 8 );
	solver.setProblem( problem );
	solver.setRo( 0.99 );

	res = solver.solve( 100 );
	cout << res << endl;

	if ( res == false )
	{
		cout << "Unable to solve with ant solver!!!" << endl;
		return 1;
	}

	cout << "Solved with ant solver" << endl;

	cspInterpretation = solver.getResult();

	int i;
	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		int var1value = cspInterpretation.getVariableValue( i );
		BasicCSPVariableValue* value1 = (BasicCSPVariableValue *)problem->getDomainList()->getDomain( i )->getValue( var1value );

		cout << "Var " << i << " = " << value1->getValue() << endl;
	}

	res = enc->getSATInterpretation( cspInterpretation, interpretation );
	if ( res == false )
	{
		cout << "Unable to retrieve the SAT interpretaiton" << endl;
		return 2;
	}

	if ( formula.getNumSatisfiedClauses( interpretation ) != formula.getNumClauses() )
	{
		cout << "Formula not satisfied!" << endl;
		return 3;
	}

	return 0;
}

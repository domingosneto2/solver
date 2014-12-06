
#include <iostream>

#include <util/Random.h>
#include <aco/AntSolver.h>
#include <csp/NQueensCSP.h>
#include <csp/RandomCSP.h>


int testAntSolver( int argc, char **argv )
{
	Random::s_randomize();

	int numVars= 100;
	int domainSize = 8;
	double p1 = 0.14;
	double p2 = 0.2592;

	//CSPProblem *problem = NQueensCSPFactory::create( 8 );
	//CSPProblem *problem = RandomCSPFactory::create( 50, 8, 0.14, 0.4546, true );
	CSPProblem *problem = RandomCSPFactory::create( numVars, domainSize, p1, p2, true );
	int numConstraints = problem->getConstraintList()->getNumConstraints();

	cout << "Problem has " << numVars << " variables, with domain size " << domainSize << "," << endl
		 << " and " << numConstraints << " constraints." << endl;

	AntSolver solver;

	solver.setAlpha( 2 );
	solver.setBeta( 10 );
	solver.setMaxPheromone( 50 );
	solver.setMinPheromone( 0 );
	solver.setNumAnts( 8 );
	solver.setProblem( problem );
	solver.setRo( 0.99 );
	solver.setUseLocalSearch( true );

	bool res = solver.solve( 10000 );
	cout << res << endl;

	if ( res )
	{
		for ( int i = 0; i < problem->getNumVars(); i++ )
		{
			cout << solver.getResult().getVariableValue( i ) << " ";
		}
	}
	return res;
}



#include <iostream>
#include <csp/CSPProblem.h>
#include <csp/RandomCSP.h>
#include <csp/CSPGABuilder.h>

int testRandomCSP( int argc, char **argv )
{
	int numVars= 10;
	int domainSize = 8;
	int numConstraints;

	CSPProblem *problem = RandomCSPFactory::create( numVars, domainSize, 1, 0.8, true );
	numConstraints = problem->getConstraintList()->getNumConstraints();

	cout << "Problem has " << numVars << " variables, with domain size " << domainSize << "," << endl
		 << " and " << numConstraints << " constraints." << endl;

	CSPGABuilder builder;

	builder.setElitist( false );
	builder.setFitnessScalingFactor( 2 );
	builder.setMutationProbability( 0.005 );
	builder.setPopulationSize( 16 );
	builder.setUseCI( true );
	builder.setUseCIPermutation( true );
	builder.setUseCIQuickLoop( false );
	builder.setUseCIStrictFlip( false );
	builder.setUseFitnessScaling( true );
	
	GeneticSolver *solver = builder.createSolver( problem );

	if ( solver->solve( 1000 ) == true )
	{
		cout << "OK" << endl;
	}
	else
	{
		cout << "Error" << endl;
	}

	problem->release();
	return 0;
}


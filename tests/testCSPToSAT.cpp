
#include <time.h>
#include <iostream>
#include <sat/SATGABuilder.h>
#include <sat/Interpretation.h>
#include <csp/NQueensCSP.h>
#include <sat2csp/DirectEncodingCSP2SAT.h>
#include <sat2csp/LogEncodingCSP2SAT.h>
#include <util/Random.h>

#include <util/Timer.h>


int testCSPToSAT( int argc, char **argv )
{
	Random::s_randomize();
	

	///////////////////////////////////////////////////////////////////////////
	// Variables that can be configured, in the future we will
	// read'em from the command line
	// This is the size of the N-Queens problem that we will use in the test
	int size = 16;
	int    populationSize      = 16;
	double mutationProbability = 1.0 / ( (double)populationSize * 3.0 );
	int    numGenerations      = 1000;
	bool   bUseImprover        = true;
	bool   scaleFitness        = true;
	double scalingFactor       = 3;
	int    numPopulations      = 1;
	///////////////////////////////////////////////////////////////////////////

	CSPProblem *problem = NQueensCSPFactory::create( size );

	cout << "Testing with the " << size << "-Queens problem" << endl;

	// Create the converter and get the corresponding formula
	CSP2SAT *csp2Sat = LogEncodingCSP2SAT::create();
	csp2Sat->setCSP( problem );
	CNFFormula formula = csp2Sat->getFormula();	

	cout << "The resulting formula has " << formula.getNumVars() << " variables and " << formula.getNumClauses() << " clauses" << endl;

	// try to solve it with a genetic solver
	// Setup the genetic solver
    GeneticSolver *solver;

	SATGABuilder builder;
	builder.setPopulationSize( populationSize );
	builder.setMutationProbability( mutationProbability );
	builder.setUseCI( bUseImprover );
	builder.setUseFitnessScaling( scaleFitness );
	builder.setFitnessScalingFactor( scalingFactor );

	solver = builder.createSolver( formula );
			
	// Setup a timer
	Timer timer2;
    
	// Solve the problem
    if ( solver->solve( numGenerations ) == false )
	{
		cout << "Unable to solve" << endl;
		solver->release();
		problem->release();
		return 1;
	}

	cout << "Solution found in "
		 << timer2.evaluate() << " milisseconds and "
		 << solver->getNumSteps() << " generations" << endl;

	Interpretation interpretation( formula.getNumVars() );
	interpretation.assignCopy( solver->getResult(), formula.getNumVars() );
	CSPInterpretation cspInterpretation;

	solver->release();
	solver = NULL;

	if ( !csp2Sat->getCSPInterpratation( interpretation, cspInterpretation ) )
	{
		cout << "Unable to convert the SAT interpretation into a CSP interpreatation!" << endl;
		problem->release();
		
		return 1;
	}

	// check with the problem if the result is ok
	if ( problem->isSatisfied( cspInterpretation ) == false )
	{
		cout << "Oooops, the CSP interpretation doesn't satisfy the problem!! It's a bug!!" << endl;
		problem->release();
		return 1;
	}

	problem->release();

	// print the results
	for ( int i = 0; i < size; i++ )
	{
		int position = cspInterpretation.getVariableValue( i );

		for ( int j = 0; j < size; j++ )
		{
			if ( j == position )
			{
				 cout << "1 ";
			}
			else
			{
				cout << "0 ";
			}			
		}

		cout << endl;
	}
	
	return 0;
}


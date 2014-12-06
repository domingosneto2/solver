
#include <time.h>
#include <iostream>
#include <sat/SATLIBParser.h>
#include <util/Timer.h>
#include <util/Random.h>
#include <sat/SATGABuilder.h>


int testGeneticSAT( int argc, char **argv )
{
	if ( argc != 2 )
	{
		cout << "Usage: solver testGeneticSAT filename" << endl;
		return 1;
	}

	///////////////////////////////////////////////////////////////////
	// Variables that can be configured, in the future we will
	// read'em from the command line or a file
	int    populationSize      = 8;
	double mutationProbability = 1.0 / ( (double)populationSize * 3.0 );
	int    numGenerations      = 1000;
	bool   bUseImprover        = true;
	bool   bStrictFlip         = false;
	bool   bQuickLoop          = false;
	bool   bPermutation        = true;
	bool   scaleFitness        = true;
	double scalingFactor       = 2;
	bool   elitist             = true;
	///////////////////////////////////////////////////////////////////

	// Read the filename from command line
	char *filename = argv[1];

	// Seed the random number generator
	Random::s_randomize();

	// Parse the satlib file
	SATLIBParser parser;	

	bool res = parser.open( filename );
	if ( res == false )
	{
		cout << "Unable to open input file" << endl;
		return 1;
	}

	CNFFormula formula = parser.getFormula();

	// Setup the genetic solver
    GeneticSolver *solver;	

	SATGABuilder builder;
	builder.setPopulationSize( populationSize );
	builder.setMutationProbability( mutationProbability );
	builder.setUseCI( bUseImprover );
	builder.setUseCIStrictFlip( bStrictFlip );
	builder.setUseCIPermutation( bPermutation );
	builder.setUseCIQuickLoop( bQuickLoop );
	builder.setUseFitnessScaling( scaleFitness );
	builder.setFitnessScalingFactor( scalingFactor );
	builder.setElitist( elitist );

	solver = builder.createSolver( formula );
			
	// Setup a timer
	Timer timer2;
    
	// Solve the problem
    if ( solver->solve( numGenerations ) == false )
	{
		cout << "Unable to solve" <<
				endl;
		solver->release();
		return 1;
	}

	cout << "Solved in "
		 << timer2.evaluate() << " milisseconds and "
		 << solver->getNumSteps() << " generations." << endl;

	solver->release();
	return 0;
}


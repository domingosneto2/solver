
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <iostream>
#include <vector>
#include <string>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ga/GeneticSolver.h>
#include <sat/CNFFormula.h>
#include <sat/SATGABuilder.h>
#include <sat/SATLIBParser.h>
#include <util/BitArrayOps.h>
#include <util/Random.h>
#include <util/Timer.h>
#include <util/Properties.h>
#include <util/EnumDir.h>

#ifdef WIN32
#include <direct.h>
#define getcwd _getcwd
#define strcasecmp strcmpi
#else
#include <unistd.h>
#endif

const char *boolstr( bool b )
{
	return b ? "yes" : "no";
}


//-----------------------------------------------------------------------------
static void BitArrayString( void *bitArray, int nBits, char *string )
{
	int i;
	for ( i = 0; i < nBits; i++ )
	{
		bool value = BitArrayOps::getValue( bitArray, i );
		string[i] = value ? '1' : '0';
	}

	string[i] = 0;
}

//-----------------------------------------------------------------------------
static bool run( const char *filename,
				 int populationSize,
				 int maxNumGenerations,
				 double mutationProbability,
				 bool useChromossomeImprover,
				 bool scaleFitness,
				 double fitnessScalingFactor,
				 bool quickLoop,
				 bool improveFromCache,
				 bool permutation,
				 bool strictFlip )
{
	CNFFormula formula;
	SATLIBParser parser;

	cout << "======================================================================" << endl;
	cout << "Filename:    " << filename << endl;
	cout << "Parsing... ";

	if ( !parser.open( filename ) )
	{
		cout << "Error: Unable to parse file"<< endl;
		return false;		
	}	

	formula = parser.getFormula();

	cout << "Formula details:" << endl;
	cout << "\tClauses:       " << formula.getNumClauses() << endl;
	cout << "\tSAT Variables: " << formula.getNumVars() << endl;	

	cout << "SATGA Parameters:" << endl;
	cout << "\tPopulation Size:        " << populationSize << endl;
	cout << "\tMutation Pribability:   " << mutationProbability << endl;
	cout << "\tLocal Search:           " << boolstr(useChromossomeImprover) << endl;
	if ( useChromossomeImprover )
	{
		cout << "\tQuick loop:             " << boolstr(quickLoop) << endl;
		cout << "\tCache:                  " << boolstr(improveFromCache ) << endl;
		cout << "\tRandom Permutation:     " << boolstr(permutation) << endl;
		cout << "\tStrict flip:            " << boolstr(strictFlip) << endl;
	}
	cout << "\tFitness scaling:        " << boolstr(scaleFitness) << endl;
	if ( scaleFitness )
	{
		cout << "\tFitness scaling factor: " << fitnessScalingFactor << endl;
	}	

	SATGABuilder builder;
	builder.setPopulationSize( populationSize );
	builder.setMutationProbability( mutationProbability );
	builder.setUseCI( useChromossomeImprover );
	builder.setUseFitnessScaling( scaleFitness );
	builder.setFitnessScalingFactor( fitnessScalingFactor );
	builder.setUseCIQuickLoop( quickLoop );
	builder.setImproveFromCache( improveFromCache );
	builder.setUseCIPermutation( permutation );
	builder.setUseCIStrictFlip( strictFlip );

	GeneticSolver *solver = builder.createSolver( formula );

	cout << "Solving..." << endl;

	Timer timer;
	bool result = solver->solve( maxNumGenerations );
	int elapsedTime = timer.evaluate();
	double maxRawFitness = solver->getMaxRawFitness();	
	int numGenerations = solver->getNumSteps();

	if ( result )
	{
		cout << "Result: Success" << endl;
	}
	else
	{
		cout << "Result: Failed" << endl;
	}

	cout << "Time:        " << elapsedTime << endl;
	cout << "Generations: "  << solver->getNumSteps() << endl;
	cout << "Max Fitness: " << solver->getMaxRawFitness() << endl;

	if ( result )
	{
		cout << "Verifying... ";

		Interpretation interpretation( formula.getNumVars() );
		interpretation.assignCopy( solver->getResult(), formula.getNumVars() );

		if ( formula.getNumSatisfiedClauses( interpretation ) == formula.getNumClauses() )
		{
			cout << "OK" << endl;
		}
		else
		{
			cout << "Failed" << endl;
		}
	}
	

	solver->release();	

	return true;
}
//-----------------------------------------------------------------------------

static bool atob( const char *str )
{
	if ( strcasecmp( str, "true" ) == 0 ||
		 strcasecmp( str, "yes" ) == 0 ||
		 strcasecmp( str, "1" ) == 0 )
	{
		return true;
	}

	return false;
}

static bool extract_arg( int &i, int argc, char **argv, char &cmd, char *param )
{
	char *arg= argv[i];
	int len = strlen( arg );

	if ( arg[0] != '-' )
	{
		return false;
	}

	cmd = arg[1];
	if ( len > 2 )
	{
		strcpy( param, arg + 2 );
		i++;
	}
	else
	{
		if ( i == argc - 1 )
		{
			return false;
		}
		strcpy( param, argv[i+1] );
		i += 2;
	}

	return true;
}

static bool getCommandLineOptions( int argc, char **argv,
			         int &populationSize,
				 int &maxNumGenerations,
				 double &mutationProbability,
				 bool &useChromossomeImprover,
				 bool &scaleFitness,
				 double &fitnessScalingFactor,
				 bool &quickLoop,
				 bool &improveFromCache,
				 bool &permutation,
				 bool &strictFlip,
			         char * filename)
{
	int i = 1;
	char buff[1024];
	while ( i < argc )
	{
		char cmd;
		if ( !extract_arg( i, argc, argv, cmd, buff ) )
		{
			cerr << "Error on parameter " << argv[i] << endl;
			return false;
		}

		switch( cmd )
		{
			case 'n':
				populationSize = atof( buff );
				break;
			case 'g':
				maxNumGenerations = atoi( buff );
				break;
			case 'p':
				mutationProbability = atof( buff );
				break;
			case 'l':
				useChromossomeImprover = atob( buff );
				break;
			case 's':
				scaleFitness = atob( buff );
				break;
			case 'F':
				fitnessScalingFactor = atof( buff );
				break;
			case 'q':
				quickLoop = atob( buff );
				break;
			case 'c':
				improveFromCache = atob( buff );
				break;
			case 'r':
				permutation = atob( buff );
				break;
			case 'i':
				strictFlip = atob( buff );
				break;
			case 'f':
				strcpy( filename, buff );
				break;
			default:
				cerr << "Unknown parameter -" << cmd << endl;
				return false;
		}
	}

	return true;
}

int benchmarkGeneticSAT( int argc, char **argv )
{
	Random::s_randomize();
	
	if ( argc < 3 )
	{
		cout << "Error:  Usage: benchmarkGeneticSAT [options]" << endl;
		return 1;
	}

	char filename[1024];
	int populationSize = 16;
	int maxNumGenerations = 500;
	double mutationProbability = 0.2;
	bool useChromossomeImprover = true;
	bool scaleFitness = true;
	double scalingFactor = 4;
	bool bQuickLoop = false;
	bool improveFromCache = false;
	bool permutation = true;
	bool strictFlip = false;

	bool res = getCommandLineOptions( argc, argv, populationSize, maxNumGenerations, 
		                          mutationProbability, useChromossomeImprover, scaleFitness,
					  scalingFactor, bQuickLoop, improveFromCache,
					  permutation, strictFlip, filename );

	if ( res == false )
	{
		return 1;
	}


	res = run( filename, populationSize, maxNumGenerations, mutationProbability,
		   useChromossomeImprover, scaleFitness, scalingFactor, bQuickLoop,
		   improveFromCache, permutation, strictFlip );

	return res? 0 : 1;

}

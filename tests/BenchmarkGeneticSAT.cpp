
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <iostream>
#include <vector>
#include <string>
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
#else
#include <unistd.h>
#endif


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
				 bool strictFlip,
				 int &numVars,
				 int &numClauses,
				 bool &result,
				 int &numGenerations,
				 int &elapsedTime,
				 double &maxRawFitness,
				 char ** presult )
{
	CNFFormula formula;

	SATLIBParser parser;

	if ( !parser.open( filename ) )
	{
		cerr << "Unable to parse " << filename << endl;
		return false;
	}

	formula = parser.getFormula();
	char *res_str = new char[formula.getNumVars() + 1];

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

	Timer timer;
	result = solver->solve( maxNumGenerations );
	elapsedTime = timer.evaluate();
	maxRawFitness = solver->getMaxRawFitness();
	numVars = formula.getNumVars();
	numClauses = formula.getNumClauses();
	numGenerations = solver->getNumSteps();

	BitArrayString( result ? solver->getResult() : solver->getBestIndividual(), formula.getNumVars(), res_str );

	solver->release();

	*presult = res_str;

	return true;
}
//-----------------------------------------------------------------------------
static void run( FILE *fptr,
				 const char *directory,
				 const char *mask,
				 int runs,
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
	char cwd[1024];

	getcwd( cwd, 1024);
	chdir( directory );

	double nSuccess = 0;
	double total = 0;

	int curRun = 0;

	char *res_str;

	while ( curRun < runs )
	{
		EnumDir enumDir;
		enumDir.start( ".", mask );

		while ( enumDir.next() )
		{
			int numVars;
			int numClauses;
			bool result;
			int numGenerations;
			int elapsedTime;
			double maxRawFitness;

			printf( "enumDir.getName() = %s\n", enumDir.getName() );


			bool status = run( enumDir.getName(), populationSize, maxNumGenerations,
							mutationProbability, useChromossomeImprover, scaleFitness,
							fitnessScalingFactor, quickLoop, improveFromCache,
							permutation, strictFlip, numVars, numClauses, result,
							numGenerations, elapsedTime, maxRawFitness, &res_str );

			if ( status == true )
			{
				fprintf( fptr, "%s,%d,%d,%d,%lf,%s,%d,%s,%lf,%s,%s,%s,%s,%s,%d,%d,%lf,%s\n",
					    enumDir.getName(),
						numVars,
						numClauses,
						populationSize,
						mutationProbability,
						useChromossomeImprover ? "true" : "false",
						maxNumGenerations,
						scaleFitness ? "true" : "false",
						fitnessScalingFactor,
						improveFromCache ? "true" : "false",
						quickLoop ? "true" : "false",
						permutation ? "true" : "false",
						strictFlip ? "true" : "false",
						result ? "true" : "false",
						numGenerations,
						elapsedTime,
						maxRawFitness,
						res_str );
				fflush( fptr );

				cout << result << "," << numGenerations << "," << elapsedTime << "," << maxRawFitness << endl;

				if ( result == true )
				{
					nSuccess++;
				}
				total++;
			}
		}
		curRun++;
	}

	//fprintf( fptr, "SR: %lf\n", (double)nSuccess/(double)total );
	printf( "SR: %lf\n", (double)nSuccess/(double)total );
	delete []res_str;

	chdir( cwd );
}
//-----------------------------------------------------------------------------
static bool readConfig( const char *filename, 
				 char *csv,
				 char *directory,
				 char *mask,
				 int &runs,
				 vector<int> &populationSize,
				 vector<int> &maxNumGenerations,
				 vector<double> &mutationProbability,
				 vector<bool> &useChromossomeImprover,
				 vector<bool> &scaleFitness,
				 vector<double> &fitnessScalingFactor,
				 vector<bool> &quickLoop,
				 vector<bool> &improveFromCache,
				 vector<bool> &permutation,
				 vector<bool> &strictFlip )
{
	Properties properties;

	if ( properties.read( filename ) == 0 )
	{
		cout << "Unable to read " << filename << endl;
		cout << "Error in line " << properties.getErrorLine() << endl;
		return false;
	}

	strcpy( csv, properties.getPropertyString( "csv" ).c_str() );
	strcpy( directory, properties.getPropertyString( "directory" ).c_str() );
	strcpy( mask, properties.getPropertyString( "mask" ).c_str() );

	runs = properties.getPropertyInt( "runs", 1 );
	populationSize = properties.getPropertyIntVector( "populationSize" );
	maxNumGenerations = properties.getPropertyIntVector( "maxNumGenerations" );
	mutationProbability = properties.getPropertyDoubleVector( "mutationProbability" );
	useChromossomeImprover = properties.getPropertyBooleanVector( "useChromossomeImprover" );
	scaleFitness = properties.getPropertyBooleanVector( "scaleFitness" );
	fitnessScalingFactor = properties.getPropertyDoubleVector( "fitnessScalingFactor" );
	quickLoop = properties.getPropertyBooleanVector( "bQuickLoop" );
	improveFromCache = properties.getPropertyBooleanVector( "improveFromCache" );
	permutation = properties.getPropertyBooleanVector( "permutation" );
	strictFlip = properties.getPropertyBooleanVector( "strictFlip" );

	return true;
}
//-----------------------------------------------------------------------------
int BenchmarkGeneticSAT( int argc, char **argv )
{
	Random::s_randomize();
	
	if ( argc != 2 )
	{
		return 1;
	}

	char *filename = argv[1];

	char dirname[1030];
	char mask[1030];
	char csv[1030];
	char message[1030];

	int runs;
	vector<int> populationSize;
	vector<int> maxNumGenerations;
	vector<double> mutationProbability;
	vector<bool> useChromossomeImprover;
	vector<bool> scaleFitness;
	vector<double> scalingFactor;
	vector<bool> bQuickLoop;
	vector<bool> improveFromCache;
	vector<bool> permutation;
	vector<bool> strictFlip;


	bool res = readConfig( filename, csv, dirname, mask, runs, populationSize, 
						   maxNumGenerations, mutationProbability,
						   useChromossomeImprover, scaleFitness, scalingFactor,
						   bQuickLoop, improveFromCache, permutation, strictFlip );

	if ( res == false )
	{
		return false;
	}


	FILE *fptr = fopen( csv, "wt" );
	if ( fptr == NULL )
	{
		cout << "Unable to open " << csv << endl;
		return 0;
	}
	
	fprintf( fptr, "fileName, numVars, numClauses, populationSize, mutationProbability, useChromossomeImprover, maxNumGenerations, scaleFitness, "
				   "fitnessScalingFactor, improveFromCache, quickLoop,permutation, strictFlip, result, "
				   "numGenerations, elapsedTime, maxRawFitness\n" );


	for ( int i1 = 0; i1 < populationSize.size(); i1++ )
		for ( int i2 = 0; i2 < maxNumGenerations.size(); i2++ )			
			for ( int i3 = 0; i3 < mutationProbability.size(); i3++ )
				for ( int i4 = 0; i4 < useChromossomeImprover.size(); i4++ )
					for ( int i5 = 0; i5 < scaleFitness.size(); i5++ )
						for ( int i6 = 0; i6 < scalingFactor.size(); i6++ )
							if ( scaleFitness[i5] == 0 && i6 > 0 ) continue;
							else
							for ( int i7 = 0; i7 < bQuickLoop.size(); i7++ )
								if ( useChromossomeImprover[i4] == 0 && i7 > 0 ) continue;
								else
								for ( int i8 = 0; i8 < improveFromCache.size(); i8++ )
									if ( useChromossomeImprover[i4] == 0 && i8 > 0 ) continue;
									else
									for ( int i9 = 0; i9 < permutation.size(); i9++ )
										if ( useChromossomeImprover[i4] == 0 && i9 > 0 ) continue;
										else
										for ( int i10 = 0; i10 < strictFlip.size(); i10++ )	
											if ( useChromossomeImprover[i4] == 0 && i10 > 0 ) continue;
											else
											run( fptr, 
												 dirname, 
												 mask, 
												 runs, 
												 populationSize[i1],
												 maxNumGenerations[i2], 
												 mutationProbability[i3],
												 useChromossomeImprover[i4], 
												 scaleFitness[i5],
												 scalingFactor[i6], 
												 bQuickLoop[i7],
												 improveFromCache[i8], 
												 permutation[i9], 
												 strictFlip[i10] );

	fclose( fptr );
	

	return 0;

}

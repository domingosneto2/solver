
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <sat/SATLIBParser.h>
#include <util/Random.h>
#include <util/Timer.h>
#include <aco/AntSolver.h>
#include <csp/RandomCSP.h>
#include <sat/Interpretation.h>
#include <csp/CSPProblem.h>
#include <sat2csp/DualEncodingSAT2CSP.h>

#ifdef WIN32
#define strcasecmp strcmpi
#endif

static bool runAntSolver( double alpha, 
                          double beta, 
			  double minPheromone, 
			  double maxPheromone, 
			  int numAnts, 
			  double ro, 
			  int numSteps,
			  bool localSearch,
			  const char *filename )
{
	SATLIBParser parser;
	CNFFormula formula;

	cout << "======================================================================" << endl;
	cout << "Filename:    " << filename << endl;
	cout << "Parsing... ";

	if ( !parser.open( filename ) )
	{
		cout << "Error: Unable to parse file"<< endl;
		return false;
	}

	cout << "OK." << endl;

	formula = parser.getFormula();

	cout << "Formula details:" << endl;
	cout << "\tClauses:       " << formula.getNumClauses() << endl;
	cout << "\tSAT Variables: " << formula.getNumVars() << endl;
	cout << "Creating CSP" << endl;

	DualEncodingSAT2CSP *enc = DualEncodingSAT2CSP::create();
	enc->setFormula( &formula );
	
	CSPProblem *problem = enc->getProblem();

	cout << "CSP  details:" << endl;
	cout << "\tCSP Variables: " << problem->getNumVars() << endl;
	cout << "\tConstraints:   " << problem->getConstraintList()->getNumConstraints() << endl;

	cout << "Ant-Solver parameters:" << endl;
	cout << "\tRo:            " << ro << endl;
	cout << "\tAlpha:         " << alpha << endl;
	cout << "\tBeta:          " << beta << endl;
	cout << "\tMin Pheromone: " << minPheromone << endl;
	cout << "\tMax Pheromone: " << maxPheromone << endl;
	cout << "\tNum. Ants:     " << numAnts << endl;
	cout << "\tLocal Search:  " << (localSearch ? "yes" : "no") << endl;

	AntSolver solver;

	solver.setAlpha( alpha );
	solver.setBeta( beta );
	solver.setMaxPheromone( maxPheromone );
	solver.setMinPheromone( minPheromone );
	solver.setNumAnts( numAnts );
	solver.setProblem( problem );
	solver.setRo( ro );

	cout << "Solving..." << endl;

	Timer timer;
	timer.reset();

	bool res = solver.solve( numSteps );

	unsigned int time = timer.evaluate();	

	if ( res )
	{
		cout << "Result: Success" << endl;
	}
	else
	{
		cout << "Result: Failed" << endl;
	}
	cout << "Time:  " << time << endl;
	cout << "Steps: "  << solver.getNumSteps() << endl;
	if ( res )
	{
		cout << "Verifying... ";

		Interpretation interpretation( formula.getNumVars() );

		res = enc->getSATInterpretation( solver.getResult(), interpretation );
		if ( res == false )
		{
			cout << "Error" << endl;
		}
		else
		{
			res = formula.getNumSatisfiedClauses( interpretation ) == formula.getNumClauses();
			if ( res )
			{
				cout << "OK" << endl;
			}
			else
			{
				cout << "Failed" << endl;
			}
		}
	}

	problem->release();

	return res;
}

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
			    double &alpha,
			    double &beta,
			    double &minPheromone,
			    double &maxPheromone,
			    int    &numAnts,
			    bool   &localSearch,
			    double &ro,
			    int    &numSteps,
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
			case 'a':
				alpha = atof( buff );
				break;
			case 'b':
				beta = atof( buff );
				break;
			case 'm':
				minPheromone = atof( buff );
				break;
			case 'M':
				maxPheromone = atof( buff );
				break;
			case 'n':
				numAnts = atoi( buff );
				break;
			case 'l':
				localSearch = atob( buff );
				break;
			case 'r':
				ro = atof( buff );
				break;
			case 's':
				numSteps = atoi( buff );
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

int benchmarkAntSolver( int argc, char **argv )
{
	Random::s_randomize();

	if ( argc < 3 )
	{
		cout << "Error:  Usage: runAntSolver [options]" << endl;
		return 1;
	}	

	double alpha = 2;
	double beta = 10;
	double minPheromone = 1;
	double maxPheromone = 100;
	int numAnts = 8;
	bool localSearch = true;
	double ro = 0.99;
	int numSteps = 500;
	char filename[1024];
	filename[0] = 0;

	bool res = getCommandLineOptions( argc, argv, alpha, beta, minPheromone,
		                          maxPheromone, numAnts, localSearch, ro, numSteps, filename );
	if ( res == false )
	{
		return 1;
	}

	if ( strlen( filename ) == 0 )
	{
		cerr << "Missing parameter -f" << endl;
		return 1;
	}

	res = runAntSolver( alpha, beta, minPheromone, maxPheromone, numAnts, ro, numSteps, localSearch, filename );
	return res ? 0 : 1;
}


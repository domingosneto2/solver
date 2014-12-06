
//#include <windows.h>
//#include <conio.H>
#include <stdio.h>
#include <iostream>

#include <math.h>
#include <aco/AntSolver2.h>
#include <util/Random.h>
#include <csp/MinConflicts.h>

//---------------------------------------------------------------------------
AntSolver2::AntSolver2()
{
	useLocalSearch = true;
}
//---------------------------------------------------------------------------
AntSolver2::~AntSolver2()
{
}
//---------------------------------------------------------------------------
void AntSolver2::setProblem( CSPProblem *_problem )
{
	problem = _problem;
}
//---------------------------------------------------------------------------
void AntSolver2::setNumAnts( int _numAnts )
{
	numAnts = _numAnts;
}
//---------------------------------------------------------------------------
void AntSolver2::setAlpha( double _alpha )
{
	alpha = _alpha;
}
//---------------------------------------------------------------------------
void AntSolver2::setBeta( double _beta )
{
	beta = _beta;
}
//---------------------------------------------------------------------------
void AntSolver2::setRo( double _ro )
{
	ro = _ro;
}
//---------------------------------------------------------------------------
void AntSolver2::setMinPheromone( double _minPheromone )
{
	minPheromone = _minPheromone;
}
//---------------------------------------------------------------------------
void AntSolver2::setMaxPheromone( double _maxPheromone )
{
	maxPheromone = _maxPheromone;
}
//---------------------------------------------------------------------------
void AntSolver2::setUseLocalSearch( bool _useLocalSearch )
{
	useLocalSearch = _useLocalSearch;
}
//---------------------------------------------------------------------------
int AntSolver2::getNumSteps()
{
	return stepsPerformed;
}
//---------------------------------------------------------------------------
void AntSolver2::calculateValuesScore( vector< vector< double > > &valuesScore )
{
	int i, j;

	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		double max, min;
		valuesScore[i].resize( problem->getDomainList()->getDomainSize( i ) );
		for ( j = 0; j < problem->getDomainList()->getDomainSize( i ); j++ )
		{
			valuesScore[i][j] = calculateValueScore( i, j );
			if ( j == 0 )
			{
				max = min = valuesScore[i][j];
			}
			else
			{
				if ( max < valuesScore[i][j] )
				{
					max = valuesScore[i][j];
				}
				if ( min > valuesScore[i][j] )
				{
					min = valuesScore[i][j];
				}
			}			
		}

		// aplicamos uma transformacao
		double a, b;
		double l = 1, h = 2;
		a = ( l - h ) / ( min - max );
		b = l - a * min;

		for ( j = 0; j < problem->getDomainList()->getDomainSize( j ); j++ )
		{
			//printf( "valuesScore[%d][%d] = %lf\n", i, j, valuesScore[i][j] );
			valuesScore[i][j] = a * valuesScore[i][j] + b;
			//valuesScore[i][j] = 1;
			//printf( "valuesScore[%d][%d] = %lf\n", i, j, valuesScore[i][j] );
		}
	}
}
//---------------------------------------------------------------------------
double AntSolver2::calculateValueScore( int var, int value )
{
	int i, j;
	int valueScore = 0;

	for ( i = 0; i < variableConstraints[var].size(); i++ )
	{
		int constraint = variableConstraints[var][i];
		int var1 = problem->getConstraintList()->getVar1( constraint );
		int var2 = problem->getConstraintList()->getVar2( constraint );
		int theVar = ( var == var1 ? var2 : var1 );

		for ( j = 0; j < problem->getDomainList()->getDomainSize( theVar ); j++ )
		{
			if ( var1 == var )
			{
				if ( problem->getConstraintList()->passes( constraint, value, j ) )
				{
					valueScore++;
				}
			}
			else
			{
				if ( problem->getConstraintList()->passes( constraint, j, value ) )
				{
					valueScore++;
				}
			}
		}
	}

	return valueScore;
}
//---------------------------------------------------------------------------
bool AntSolver2::solve( int numSteps )
{
	init();	

	vector<int> uninstantiatedVariables( problem->getNumVars(), 0 );	
	vector<int> numSatisfiedConstraints( numAnts );	
	vector< vector<double> > valuesScore( problem->getNumVars() );

	calculateValuesScore( valuesScore );

	MinConflicts *minConflicts = NULL;
	if ( useLocalSearch )
	{
		minConflicts = MinConflicts::create( problem );
	}

	int maxSatisfiedConstraints;

	int i, j;

	for ( i = 0; i < numSteps; i++ )
	{

		maxSatisfiedConstraints = 0;
		vector< CSPInterpretation > interpretations( numAnts );
		for ( j = 0; j < numAnts; j++ )
		{			
			int numVars = problem->getNumVars();

			// Initialize the vector of uninstantiated variables
			int k;
			for ( k = 0; k < numVars; k++ )
			{
				uninstantiatedVariables[k] = k;
			}

			// Build a path			
			
			interpretations[j].setNumVariables( problem->getNumVars() );
			for ( k = 0; k < problem->getNumVars(); k++ )
			{
				// Pick a variable.
				int variable = pickUninstantiatedVariable( interpretations[j], uninstantiatedVariables , problem->getNumVars() - k );
				// pick a value from this variable
				int value    = pickValue( variable, valuesScore );

				interpretations[j].setVariableValue( variable, value );
			}

			if ( useLocalSearch )
			{
				minConflicts->localSearch( interpretations[j], interpretations[j] );
			}

			numSatisfiedConstraints[j] = problem->getNumSatisfiedConstraints( interpretations[j] );
			if ( numSatisfiedConstraints[j] == problem->getConstraintList()->getNumConstraints() )
			{
				result = interpretations[j];
				stepsPerformed = i;
				if ( minConflicts )
					minConflicts->release();
				return true;
			}
			if ( numSatisfiedConstraints[j] > maxSatisfiedConstraints )
			{
				maxSatisfiedConstraints = numSatisfiedConstraints[j];
			}
		}

		// Now that we've built all assignments
		// let's choose the best ones
		// Only the assignmenst with the max number of satisfied
		// constraints will lay pheromone
		for ( j = 0; j < numAnts; j++ )
		{
			if ( numSatisfiedConstraints[j] == maxSatisfiedConstraints )
			{
				layPheromone( interpretations[j] );
			}
		}

		//cout << "Step " << i << ", maxSatisfiedConstraints: " << maxSatisfiedConstraints << endl;
		cout << i << ", " << maxSatisfiedConstraints << endl;
		//if ( i % 10 == 0 )
		{
			//printPheromones ( i, maxSatisfiedConstraints );
		}
	}

	stepsPerformed = i;

	if ( useLocalSearch )
	{
		minConflicts->release();
	}

	return false;
}
//---------------------------------------------------------------------------
int AntSolver2::pickUninstantiatedVariable( const CSPInterpretation &interpretation, vector<int> &uninstantiatedVariables, int numUninstVars )
{
	int index = Random::s_generateUniformVariable( 0, numUninstVars );
	int val = uninstantiatedVariables[index];

	if ( index < numUninstVars - 1 )
	{
		uninstantiatedVariables[index] = uninstantiatedVariables[numUninstVars - 1];
	}

	return val;
}
//---------------------------------------------------------------------------
int AntSolver2::pickValue( int variable, vector< vector< double > > &valuesScore )
{	
	int domainSize = problem->getDomainList()->getDomainSize( variable );
	int numVars = problem->getNumVars();

	vector< double > factors( domainSize );
	double sumFactors = 0;

	for ( int i = 0; i < domainSize; i++ )
	{
		double trailFactor = getTrailFactor( variable, i );
		double qualityFactor = valuesScore[variable][i];

		factors[i] = pow( trailFactor, alpha ) * pow( qualityFactor, beta );
		sumFactors += factors[i];
	}

	if ( sumFactors == 0 )
	{
		sumFactors = domainSize;
		factors.assign( domainSize, 1 );
	}
	int value = (int)Random::s_pick( factors, sumFactors );
	return value;
}
//---------------------------------------------------------------------------
void AntSolver2::init()
{
	// init, create a vector that indicates to which constraints
	// each variable belongs
	variableConstraints.resize( problem->getNumVars() );

	for ( int i = 0; i < problem->getConstraintList()->getNumConstraints(); i++ )
	{
		variableConstraints[problem->getConstraintList()->getVar1( i )].push_back( i );
		variableConstraints[problem->getConstraintList()->getVar2( i )].push_back( i );
	}

	// init the graph
	graph.init( minPheromone, maxPheromone, ro, problem );
}
//---------------------------------------------------------------------------
double AntSolver2::getTrailFactor( int variable, int value )
{
	return graph.getPheromone( variable, value );
}
//---------------------------------------------------------------------------
void AntSolver2::layPheromone( const CSPInterpretation &interpretation )
{
	graph.evaporate();

	double numConstraints = problem->getConstraintList()->getNumConstraints();
	double numSatisfiedConstraints = problem->getNumSatisfiedConstraints( interpretation );
	double cost = numConstraints - numSatisfiedConstraints;	
	double pheromone = (double)1 / cost;
	//double cost = ( numConstraints - numSatisfiedConstraints ) / numConstraints;	
	//double pheromone = (double)1 - cost;

	int numVars = problem->getNumVars();

	for ( int i = 0; i < numVars; i++ )
	{
		int ivalue = interpretation.getVariableValue( i );		
		//graph.addPheromone( i, ivalue, pheromone );
		graph.addPheromone( i, ivalue, 1 );
	}

	//printf( "MAX: %lf MIN: %lf\n", graph.getMaxCurValue(), graph.getMinCurValue() );
	
}
//---------------------------------------------------------------------------
const CSPInterpretation &AntSolver2::getResult()
{
	return result;
}
//---------------------------------------------------------------------------
/*
int clrscr()

{



  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(hndl, &csbi);

  DWORD written;

  DWORD N = csbi.dwSize.X * csbi.dwCursorPosition.Y +

            csbi.dwCursorPosition.X + 1;

  COORD curhome = {0,0};



  FillConsoleOutputCharacter(hndl, ' ', N, curhome, &written);

  csbi.srWindow.Bottom -= csbi.srWindow.Top;

  csbi.srWindow.Top = 0;

  SetConsoleWindowInfo(hndl, TRUE, &csbi.srWindow);

  SetConsoleCursorPosition(hndl, curhome);



  return 0;

}

void AntSolver::printPheromones( int step, int maxSatisfiedConstraints )
{
	clrscr();

	printf( "%d %d\n", step, maxSatisfiedConstraints );

	int numVars = problem->getNumVars();	

	map< pair< int, int >, double > pheromones;
	graph.getPheromoneMap( pheromones );
	
	for ( int i = 0; i < numVars; i++ )
	{
		int domainSize = problem->getDomainList()->getDomainSize( i );		
		
		for ( int j = 0; j < domainSize; j++ )
		{
			double pheromone = 0;
			if ( pheromones.count( make_pair( i, j ) ) > 0 )
			{
				pheromone = pheromones[ make_pair( i, j ) ];
			}
			printf( "%6.2f ", pheromone );
		}

		printf( "\n\n" );
		
	}
}
*/
//---------------------------------------------------------------------------


//#include <windows.h>
//#include <conio.H>
#include <stdio.h>
#include <iostream>

#include <math.h>
#include <aco/AntSolver.h>
#include <util/Random.h>
#include <csp/MinConflicts.h>

//---------------------------------------------------------------------------
AntSolver::AntSolver()
{
	useLocalSearch = true;
}
//---------------------------------------------------------------------------
AntSolver::~AntSolver()
{
}
//---------------------------------------------------------------------------
void AntSolver::setProblem( CSPProblem *_problem )
{
	problem = _problem;
}
//---------------------------------------------------------------------------
void AntSolver::setNumAnts( int _numAnts )
{
	numAnts = _numAnts;
}
//---------------------------------------------------------------------------
void AntSolver::setAlpha( double _alpha )
{
	alpha = _alpha;
}
//---------------------------------------------------------------------------
void AntSolver::setBeta( double _beta )
{
	beta = _beta;
}
//---------------------------------------------------------------------------
void AntSolver::setRo( double _ro )
{
	ro = _ro;
}
//---------------------------------------------------------------------------
void AntSolver::setMinPheromone( double _minPheromone )
{
	minPheromone = _minPheromone;
}
//---------------------------------------------------------------------------
void AntSolver::setMaxPheromone( double _maxPheromone )
{
	maxPheromone = _maxPheromone;
}
//---------------------------------------------------------------------------
void AntSolver::setUseLocalSearch( bool _useLocalSearch )
{
	useLocalSearch = _useLocalSearch;
}
//---------------------------------------------------------------------------
int AntSolver::getNumSteps()
{
	return stepsPerformed;
}
//---------------------------------------------------------------------------
bool AntSolver::solve( int numSteps )
{
	init();	

	vector<int> instantiatedVariables( problem->getNumVars(), 0 );
	vector<int> numSatisfiedConstraints( numAnts );	
	vector< int > consistentValues( problem->getNumVars() );

	// these vectors must be able to store all values of all variables
	int i;
	/*
	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		consistentValues[i].resize( problem->getDomainList()->getDomainSize( i ) );		
	}
	*/

	MinConflicts *minConflicts;
	if ( useLocalSearch )
	{
		minConflicts = MinConflicts::create( problem );
	}

	int maxSatisfiedConstraints;

	for ( i = 0; i < numSteps; i++ )
	{

		maxSatisfiedConstraints = 0;
		vector< CSPInterpretation > interpretations( numAnts );
		int j;
		for ( j = 0; j < numAnts; j++ )
		{			
			int numVars = problem->getNumVars();

			// Initialize the vector of consistent values
			int k;
			for ( k = 0; k < numVars; k++ )
			{
				int domainSize = problem->getDomainList()->getDomainSize( k );				
				consistentValues[k] = domainSize;
			}

			// Build a path			
			instantiatedVariables.assign( numVars, 0 );
			interpretations[j].setNumVariables( problem->getNumVars() );
			for ( k = 0; k < problem->getNumVars(); k++ )
			{
				// Pick a variable.
				int variable = pickUninstantiatedVariable( interpretations[j], instantiatedVariables, consistentValues );
				// pick a value from this variable
				int value    = pickValue( interpretations[j], variable, instantiatedVariables );

				interpretations[j].setVariableValue( variable, value );
				
				// update the vector of consistent values
				updateConsistentValuesVector( variable, interpretations[j], consistentValues, instantiatedVariables );
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

		cout << "Step " << i << ", maxSatisfiedConstraints: " << maxSatisfiedConstraints << endl;
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
int AntSolver::pickUninstantiatedVariable( const CSPInterpretation &interpretation, vector<int> &instantiatedVariables, vector< int > &consistentValues )
{
	// use the smallest-domain ordering
	int i;
	int numVars = problem->getNumVars();
	int minConsistantValues = -1;
	vector< int >varsWithMinConsistantValues;

	// Search through all uninstantiated variables
	for ( i = 0; i < numVars; i++ )
	{
		// If this variable has already been instantiated,
		// we skip to the next
		if ( instantiatedVariables[i] != 0 )
		{
			continue;
		}

		// Get the number of consistant values of this variable
		// in relation with the already instantiated variables
		int numConsistentValues = consistentValues[i];

		if ( minConsistantValues == -1 )
		{
			minConsistantValues = numConsistentValues;
			varsWithMinConsistantValues.push_back( i );
		}
		else if ( numConsistentValues < minConsistantValues )
		{
			minConsistantValues = numConsistentValues;
			varsWithMinConsistantValues.resize( 0 );
			varsWithMinConsistantValues.push_back( i );
		}
		else if ( numConsistentValues == minConsistantValues )
		{
			varsWithMinConsistantValues.push_back( i );
		}
	}

	int ret;

	if ( varsWithMinConsistantValues.size() == 1 )
	{
		ret = varsWithMinConsistantValues[0];
	}
	else
	{
		int index = (int)Random::s_generateUniformVariable( 0, varsWithMinConsistantValues.size() );
		if ( index >= varsWithMinConsistantValues.size() )
		{
			index = varsWithMinConsistantValues.size() - 1;
		}
		ret = varsWithMinConsistantValues[index];
	}

	instantiatedVariables[ret] = 1;	
	return ret;
}
//---------------------------------------------------------------------------
/**
 * Returns true if a given value of a given variable is consistent
 * with the already instantiate variables in the partial assignment.
 */
bool AntSolver::isConsistentValue( int variable, int value, const CSPInterpretation &interpretation, vector<int> &instantiatedVariables )
{
	int numConstraints = variableConstraints[variable].size();
	int k;
	for ( k = 0; k < numConstraints; k++ )
	{
		int constraint = variableConstraints[variable][k];
		if ( problem->getConstraintList()->getVar1( constraint ) == variable )
		{
			int var2 = problem->getConstraintList()->getVar2( constraint );
			if ( instantiatedVariables[var2] != 0 )
			{
				int value2 = interpretation.getVariableValue( var2 );
				if ( problem->getConstraintList()->passes( constraint, value, value2 ) == false )
				{
					return false;
				}
			}
		}
		else
		{
			int var1 = problem->getConstraintList()->getVar1( constraint );
			if ( instantiatedVariables[var1] != 0 )
			{
				int value1 = interpretation.getVariableValue( var1 );
				if ( problem->getConstraintList()->passes( constraint, value1, value ) == false )
				{
					return false;
				}
			}
		}
	}

	return true;
}
//---------------------------------------------------------------------------
int AntSolver::pickValue( const CSPInterpretation &interpretation, int variable, vector<int> &instantiatedVariables  )
{	
	int domainSize = problem->getDomainList()->getDomainSize( variable );
	int numVars = problem->getNumVars();

	vector< double > factors( domainSize );
	double sumFactors = 0;

	for ( int i = 0; i < domainSize; i++ )
	{
		double trailFactor = getTrailFactor( variable, i, interpretation, instantiatedVariables );
		double qualityFactor = getQualityFactor( variable, i, interpretation, instantiatedVariables );;

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
void AntSolver::init()
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
double AntSolver::getTrailFactor( int variable, int value, const CSPInterpretation &interpretation, vector<int> &instantiatedVariables )
{
	int j;	
	int numVars = problem->getNumVars();
	double trailFactor = 0;
	for ( j = 0; j < numVars; j++ )
	{
		if ( j == variable )
		{
			continue;
		}
		if ( instantiatedVariables[j] != 0 )
		{
			trailFactor += graph.getPheromone( variable, value, j, interpretation.getVariableValue( j ) );
		}
	}

	return trailFactor;
}
//---------------------------------------------------------------------------
double AntSolver::getQualityFactor( int variable, int value, const CSPInterpretation &interpretation, vector<int> &instantiatedVariables )
{
	double violatedConstraints = 0;
	// the quality factor
	int j;
	for ( j = 0; j < variableConstraints[variable].size(); j++ )
	{
		int constraint = variableConstraints[variable][j];
		int var1 = problem->getConstraintList()->getVar1( constraint );			
		if ( var1 == variable )
		{
			int otherVar = problem->getConstraintList()->getVar2( constraint );
			if ( instantiatedVariables[otherVar] != 0 )
			{
				int otherVarValue = interpretation.getVariableValue( otherVar );
				if ( problem->getConstraintList()->passes( constraint, value, otherVarValue ) == false )
				{
					violatedConstraints++;
				}
			}				
		}
		else
		{
			int otherVar = var1;
			if ( instantiatedVariables[otherVar] != 0 )
			{
				int otherVarValue = interpretation.getVariableValue( otherVar );
				if ( problem->getConstraintList()->passes( constraint, otherVarValue, value ) == false )
				{
					violatedConstraints++;
				}
			}
		}
	}

	return 1.0 / ( 1 + violatedConstraints );
}
//---------------------------------------------------------------------------
void AntSolver::layPheromone( const CSPInterpretation &interpretation )
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
		for ( int j = i + 1; j < numVars; j++ )
		{			
			int jvalue = interpretation.getVariableValue( j );
			graph.addPheromone( i, ivalue, j, jvalue, pheromone );
		}
	}
	
}
//---------------------------------------------------------------------------
const CSPInterpretation &AntSolver::getResult()
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
void AntSolver::updateConsistentValuesVector( 
    int lastInstantiatedVar, 
	const CSPInterpretation &interpretation, 
	vector<int> &consistentValues, 
	vector <int> &instantiatedVariables )
{
	int i;
	int numConstraints = variableConstraints[lastInstantiatedVar].size();


	for ( i = 0; i < numConstraints; i++ )
	{
		int curConstraint = variableConstraints[lastInstantiatedVar][i];
		int otherVar = problem->getConstraintList()->getVar1( curConstraint );
		if ( otherVar == lastInstantiatedVar )
		{
			otherVar = problem->getConstraintList()->getVar2( curConstraint );
		}
		if ( instantiatedVariables[otherVar] == false )
		{
			int domainSize = problem->getDomainList()->getDomainSize( otherVar );
			int count = 0;			
			for ( int j = 0; j < domainSize; j++ )
			{
				if ( isConsistentValue( otherVar, j, interpretation, instantiatedVariables ) )
				{
					count++;
				}
			}

			consistentValues[otherVar] = count;
		}
	}
}
//---------------------------------------------------------------------------


#include <csp/MinConflicts.h>
#include <util/Random.h>

//---------------------------------------------------------------------------
MinConflicts *MinConflicts::create( CSPProblem *problem )
{
	return new MinConflicts( problem );
}
//---------------------------------------------------------------------------
void MinConflicts::release()
{
	delete this;
}
//---------------------------------------------------------------------------
MinConflicts::MinConflicts( CSPProblem *problem )
{
	init( problem );
}
//---------------------------------------------------------------------------
MinConflicts::~MinConflicts()
{
}
//---------------------------------------------------------------------------
void MinConflicts::setNumSidewaysSteps( int _numSidewaysSteps )
{
	numSidewaysSteps = _numSidewaysSteps;
}
//---------------------------------------------------------------------------
void MinConflicts::init( CSPProblem *_problem )
{
	problem = _problem;
	numSidewaysSteps = problem->getNumVars();

	int numVars = problem->getNumVars();
	const CSPConstraintList *constraintList = problem->getConstraintList();
	int numConstraints = constraintList->getNumConstraints();

	// First we build a list of all constraints in wich each variable
	// appears.
	variablesConstraints.resize( numVars );

	// Resize all vectors to zero
	int i;
	for ( i = 0; i < numVars; i++ )
	{
		variablesConstraints[i].resize( 0 );
	}
	
	// Build the list
	for ( i = 0; i < numConstraints; i++ )
	{
		int var1 = constraintList->getVar1( i );
		int var2 = constraintList->getVar2( i );

		variablesConstraints[var1].push_back( i );
		variablesConstraints[var2].push_back( i );
	}

}
//---------------------------------------------------------------------------
void MinConflicts::localSearch( const CSPInterpretation &source, CSPInterpretation &dest )
{
	// The number of conflits each variable is involved in the current
	// interpretation
	vector< int > numConflicts;
	// A vector that contains the id's of all conflicting variables
	vector< int > conflictingVariables;
	// a vector that contains the position of each variable in the
	// conflictingVariables vector.
	vector< int > conflictingIndex;

	// The number of variables involved in a conflict
	int numConflictingVars = 0;

	int i;
	int numVars = problem->getNumVars();
	const CSPConstraintList *constraintList = problem->getConstraintList();
	const CSPDomainList *domainList = problem->getDomainList();
	int numConstraints = constraintList->getNumConstraints();
	int numViolatedConstraints = 0;

	numConflicts.resize( numVars );
	conflictingIndex.resize( numVars );
	for ( i = 0; i < numVars; i++ )
	{
		numConflicts[i] = 0;
		conflictingIndex[i] = 0;
	}

	// Initialization
	for ( i = 0; i < numConstraints; i++ )
	{
		int var1 = constraintList->getVar1( i );
		int var2 = constraintList->getVar2( i );

		if ( constraintList->passes( i, source ) == false )
		{
			numConflicts[var1]++;
			numConflicts[var2]++;

			if ( numConflicts[var1] == 1 )
			{
				conflictingIndex[var1] = numConflictingVars;
				conflictingVariables.push_back( var1 );
				numConflictingVars++;
			}

			if ( numConflicts[var2] == 1 )
			{
				conflictingIndex[var2] = numConflictingVars;
				conflictingVariables.push_back( var2 );
				numConflictingVars++;
			}
			numViolatedConstraints++;
		}
	}

	CSPInterpretation prev = source;
	dest = source;

	if ( numViolatedConstraints == 0 )
	{
		return;
	}

	// The number of steps since the last improvement
	int improveCount = 0;
	
	//cout << "Problem has " << numViolatedConstraints << " violated constraints" << endl;

	while ( improveCount < numSidewaysSteps )
	{
		// Pick a conflicting variable at random
		int varIndex = Random::s_generateUniformVariable( 0, numConflictingVars );

		int var = conflictingVariables[varIndex];
		
		//cout << "Picked variable " << var << " from " << numConflictingVars << " conflicting variables." << endl;
		//cout << "This variable is involved in " << numConflicts[var] << " conflicts" << endl;
		int domainSize = domainList->getDomainSize( var );
		int originalValue = dest.getVariableValue( var );
		int originalBroken;

		// Now let's chose the value that will decrease the number
		// of unsatisfied constraints the most
		int j;
		int minBroken = variablesConstraints[var].size();
		vector<int> tiedValues;
		for ( j = 0; j < domainSize; j++ )
		{
			dest.setVariableValue( var, j );

			int k;
			int broken = 0;
			for ( k = 0; k < variablesConstraints[var].size(); k++ )
			{
				if ( constraintList->passes( variablesConstraints[var][k], dest ) == false )
				{
					broken++;
				}
			}

			//cout << "Value " << j << " violates " << broken << " constraints." << endl;

			if ( broken < minBroken )
			{
				tiedValues.resize( 1 );
				tiedValues[0] = j;
				minBroken = broken;
			}
			else if ( broken == minBroken )
			{
				tiedValues.push_back( j );
			}			
			
			if ( j == originalValue )
			{
				originalBroken = broken;
			}
		}

		int assignedValue;

		// if the tiedValues vector contains only one element, we assing this
		// value to the variable, othewise, we chose one at random
		if ( tiedValues.size() == 1 )
		{
			assignedValue = tiedValues[0];
			dest.setVariableValue( var, assignedValue );			
		}
		else
		{
			int index = Random::s_randomInt( 0, tiedValues.size() );
			assignedValue = tiedValues[index];			
			dest.setVariableValue( var, assignedValue );
		}
		
		//cout << "Picked value " << assignedValue << endl;
		//cout << "The variable now is involved in " << minBroken << " conflicts" << endl;

		// Now if no constraints are violated we need to remove
		// this variable from the conflicting vars list
		if ( minBroken == 0 )
		{
			changeConflictCount( var, 0, numConflicts, conflictingVariables,
				             conflictingIndex, numConflictingVars );
		}
		else
		{
			// Update the vector that keeps the number of conflicts that
			// a variable is involved
			numConflicts[var] = minBroken;
		}

		if ( assignedValue == originalValue )
		{
			improveCount++;
			//cout << "improveCount: " << improveCount << endl;
			continue;
		}

		// Now we have to update all conflicting counts
		// of the other variables involved in conflicts with this
		// variable
		int broken = 0;
		int pre_broken = 0;
		for ( i = 0; i < variablesConstraints[var].size(); i++ )
		{
			int iConstraint = variablesConstraints[var][i];
			int var2 = constraintList->getVar1( iConstraint );
			if ( var2 == var )
			{
				var2 = constraintList->getVar2( iConstraint );
			}

			// evaluate the constraint in both situations
			bool passesNow, passedPreviously;
			passesNow = constraintList->passes( iConstraint, dest );
			passedPreviously = constraintList->passes( iConstraint, prev );

			if( !passesNow )
			{
				broken++;
			}
			if ( !passedPreviously )
			{
				pre_broken++;
			}

			// if it was previously satisfied and remains being satisfied,
			// or if it was previously unsatisfied and remains being unsatisfied,
			// we do nothing.
			if ( passesNow == passedPreviously )
			{
				// go to the next constraint
				continue;
			}

			if ( passesNow && !passedPreviously )
			{
				changeConflictCount( var2, numConflicts[var2] - 1, numConflicts,
					              conflictingVariables, conflictingIndex,
						      numConflictingVars );
			}

			if ( !passesNow && passedPreviously )
			{
				changeConflictCount( var2, numConflicts[var2] + 1, numConflicts,
					              conflictingVariables, conflictingIndex,
						      numConflictingVars );
			}
		}

		numViolatedConstraints -= pre_broken - broken;
		//cout << "broken: " << broken << " pre_broken: " << pre_broken << endl;
		//cout << "numViolatedConstraints: " << numViolatedConstraints << " numConflictingVars " << numConflictingVars << endl;

		if ( broken < pre_broken )
		{
			improveCount = 0;
		}
		else
		{
			improveCount++;
		}

		//cout << "improveCount: " << improveCount << endl;

		if ( numConflictingVars == 0 )
		{
			return;
		}

		prev.setVariableValue( var, assignedValue );
	}
}
//---------------------------------------------------------------------------
void MinConflicts::changeConflictCount( int var, int count, vector< int > &numConflicts, 
	                            vector< int > &conflictingVariables,
                                    vector< int > &conflictingIndex,
				    int &numConflictingVars )
{
	int previousCount = numConflicts[var];

	if ( previousCount > 0 && count > 0 )
	{
		numConflicts[var] = count;
		return;
	}

	if ( previousCount == 0 && count > 0 )
	{
		numConflicts[var] = count;
		conflictingVariables.push_back( var );
		conflictingIndex[var] = numConflictingVars;
		numConflictingVars++;
		return;
	}

	if ( previousCount > 0 && count == 0 )
	{
		int index = conflictingIndex[var];
		if ( index == numConflictingVars - 1 )
		{
			conflictingVariables.resize( numConflictingVars - 1 );
			conflictingIndex[var] = 0;
			numConflictingVars--;
			numConflicts[var] = 0;
			return;
		}
		else
		{
			int other_var = conflictingVariables[numConflictingVars - 1];
			conflictingVariables[index] = other_var;
			conflictingIndex[other_var] = index;
			conflictingIndex[var] = 0;
			conflictingVariables.resize( numConflictingVars - 1 );
			numConflicts[var] = 0;
			numConflictingVars--;
			return;
		}
	}
}
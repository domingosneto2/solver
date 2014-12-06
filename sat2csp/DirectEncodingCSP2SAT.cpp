
#include <sat2csp/DirectEncodingCSP2SAT.h>


//---------------------------------------------------------------------------
DirectEncodingCSP2SAT::DirectEncodingCSP2SAT()
{

}
//---------------------------------------------------------------------------
DirectEncodingCSP2SAT::~DirectEncodingCSP2SAT()
{
}
//---------------------------------------------------------------------------
DirectEncodingCSP2SAT *DirectEncodingCSP2SAT ::create()
{
	return new DirectEncodingCSP2SAT();
}
//---------------------------------------------------------------------------
void DirectEncodingCSP2SAT ::release()
{
	delete this;
}
//---------------------------------------------------------------------------
void DirectEncodingCSP2SAT ::setCSP( const CSPProblem *problem )
{
	// we will need to know how many variables the formula will have
	int numVars = 0;
	int i;

	cspVariableStart.resize( 0 );
	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		cspVariableStart.push_back( numVars );
		numVars += problem->getDomainList()->getDomainSize( i );
	}

	// init the formula
	formula.init();
	formula.setNumVars( numVars );

	// now let's create the clauses
	int clauseCount = 0;
	int varCount = 0;

	// first the clauses that ensure that each csp variable is given a value
	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		formula.initClause( clauseCount );

		for ( int j = 0; j < problem->getDomainList()->getDomainSize( i ); j++ )
		{
			formula.initClauseVar( clauseCount, j, true, varCount );
			varCount++;
		}
		clauseCount++;
	}

	// now the clauses that ensure that each csp variable takes only one value
	varCount = 0;
	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		int domainSize = problem->getDomainList()->getDomainSize( i );		

		int i1, i2;
		for ( i1 = 0; i1 < domainSize; i1++ )
		{
			for ( i2 = i1 + 1; i2 < domainSize; i2++ )
			{
				formula.initClause( clauseCount );
				formula.initClauseVar( clauseCount, 0, false, i1 + varCount );
				formula.initClauseVar( clauseCount, 1, false, i2 + varCount );
				clauseCount++;
			}
		}

		varCount += domainSize;
	}

	// and finally the clauses that rule out binary nogoods
	CSPConstraintList *constraintList = problem->getConstraintList()->clone();
	constraintList->resetIterator();

	i = 0;
	while ( constraintList->nextConstraint() )
	{
		int var1 = constraintList->getVar1();
		int var2 = constraintList->getVar2();

		int var1Start = cspVariableStart[var1];
		int var2Start = cspVariableStart[var2];

		int i1, i2;
		for ( i1 = 0; i1 < problem->getDomainList()->getDomainSize( var1 ); i1++ )
		{
			for ( i2 = 0; i2 < problem->getDomainList()->getDomainSize( var2 ); i2++ )
			{
				if ( constraintList->passes( i1, i2 ) == false )
				{
					formula.initClause( clauseCount );
					formula.initClauseVar( clauseCount, 0, false, i1 + var1Start );
					formula.initClauseVar( clauseCount, 1, false, i2 + var2Start );
					clauseCount++;
				}
			}
		}
	}

	// release the constraint list because it's a copy
	constraintList->release();
}
//---------------------------------------------------------------------------
const CNFFormula DirectEncodingCSP2SAT ::getFormula() const
{
	return formula;
}
//---------------------------------------------------------------------------
bool DirectEncodingCSP2SAT::getCSPInterpratation( const Interpretation &interpretation, CSPInterpretation &cspInterpretation )
{
	// Initialize the csp interpretation with the number of variables
	// of the CSP problem
	int numCspVariables = cspVariableStart.size();
	cspInterpretation.setNumVariables( numCspVariables );

	// for each variable in the csp, we will find the sat variable
	// that defines it's value
	for ( int i = 0; i < numCspVariables; i++ )
	{
		// get the start and ending points of the sat variables
		// that define the value of the current csp variable
		int start = cspVariableStart[i];
		int end;
		if ( i == numCspVariables - 1 )
		{
			end = formula.getNumVars();
		}
		else
		{
			end = cspVariableStart[i+1];
		}

		// look at all sat variables related to the current
		// csp variable to find it's value.

		// this flag indicates that the value was not found yet
		bool set = false;
		for ( int j = start; j < end; j++ )
		{
			// if we found a value
			if ( interpretation.getValue( j ) == true )
			{
				if ( !set )
				{
					// ok, we set the corresponding value in the csp interpretation
					cspInterpretation.setVariableValue( i, j - start );
					set = true;
				}
				else
				{
					// error!  we cannot have two sat variables relate to the same
					// csp variable set at the same time
					return false;
				}				
			}
		}

		// if we couldn't find a value for the current csp variable,
		// we return false
		if ( !set )
		{
			return false;
		}
	}

	// if we got here we found values to all csp variables... return true
	return true;
}
//---------------------------------------------------------------------------


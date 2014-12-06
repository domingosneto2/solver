#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <csp/NQueensCSP.h>
#include <csp/BasicCSP.h>

#include <csp/VirtualCSPDomainList.h>
#include <csp/BasicCSPConstraintList.h>
#include <csp/NQueensCSPConstraintList.h>


//---------------------------------------------------------------------------
NQueensCSPConstraint *NQueensCSPConstraint::create( CSPProblem *problem, int var1, int var2 )
{
	return new NQueensCSPConstraint( problem, var1, var2 );
}
//---------------------------------------------------------------------------
void NQueensCSPConstraint::release()
{
	delete this;
}
//---------------------------------------------------------------------------
/**
 * Returns true if the values pass the constraint.
 * <p>
 * The parameters var1Value and var2Value are indexes to the values
 * in the variable domains, not the values themselves.
 */
bool NQueensCSPConstraint::passes( int var1Value, int var2Value ) const
{
	// Each variable is a row of the board.  The value is the position of the queen
	// in the row.
	if ( var1Value == var2Value )
	{
		// Two queens cannot be in the same column.
		return false;
	}
	if ( abs( var1Value - var2Value ) == abs( var1 - var2 ) )
	{
		// Two queens cannot be in the same diagonal.
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
Constraint *NQueensCSPConstraint::clone() const
{
	return new NQueensCSPConstraint( problem, var1, var2 );
}
//---------------------------------------------------------------------------
NQueensCSPConstraint::NQueensCSPConstraint( CSPProblem *problem, int var1, int var2 ) :
	Constraint( problem, var1, var2 )	
{
	
}
//---------------------------------------------------------------------------
NQueensCSPConstraint::~NQueensCSPConstraint()
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
 * Factory method that creates a new instance of the N-Queens CSP problem.
 * <p>
 * @param size: The size of the board.
 */
CSPProblem *NQueensCSPFactory::create( int size, bool virtualConstraints )
{
	// Create the problem
	CSPProblem *problem = CSPProblem::create();

	VirtualCSPDomainList *domainList = VirtualCSPDomainList::create();	

	// Each variable is a row of the board, and it's value is the position
	// of the queen in this row.
	problem->setNumVars( size );

	domainList->setNumDomains( size, true );
	domainList->setCommonSize( size );	

	problem->setDomainList( domainList );
	

	// Now we set the constraints...
	if ( virtualConstraints )
	{
		NQueensCSPConstraintList *constraintList = NQueensCSPConstraintList::create( size );
		problem->setConstraintList( constraintList );
	}
	else
	{		
		// There is one constraint for each pair of variables.
		BasicCSPConstraintList *constraintList = BasicCSPConstraintList::create();	
		int i;
		for ( i = 0; i < size; i++ )
		{
			for ( int j = i + 1; j < size; j++ )
			{
				constraintList->addConstraint( NQueensCSPConstraint::create( problem, i, j ) );
			}
		}	
		problem->setConstraintList( constraintList );
	}

	return problem;
}
//---------------------------------------------------------------------------

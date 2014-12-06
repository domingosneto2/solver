#include <stdio.h>
#include <math.h>

#include <sat2csp/DualEncodingSAT2CSP.h>
#include <csp/BasicCSPDomainList.h>
#include <csp/BasicCSPConstraintList.h>
#include <csp/BasicCSP.h>
#include <util/BitArrayOps.h>

//---------------------------------------------------------------------------
DECSPConstraint *DECSPConstraint::create( CNFFormula *formula, CSPProblem *_problem, int _var1, int _var2, int ind1, int ind2 )
{
	return new DECSPConstraint( formula, _problem, _var1, _var2, ind1, ind2 );
}
//---------------------------------------------------------------------------
void DECSPConstraint::release()
{
	delete this;
}
//---------------------------------------------------------------------------
bool DECSPConstraint::passes( int var1Value, int var2Value ) const
{
	BasicCSPVariableValue *value1, *value2;
	int ivalue1, ivalue2;

	value1 = (BasicCSPVariableValue *)problem->getDomainList()->getDomain( var1 )->getValue( var1Value );
	value2 = (BasicCSPVariableValue *)problem->getDomainList()->getDomain( var2 )->getValue( var2Value );

	ivalue1 = value1->getValue();
	ivalue2 = value2->getValue();

	bool bvalue1, bvalue2;
	bvalue1 = (ivalue1 & ( 1 << ind1 )) != 0;
	bvalue2 = (ivalue2 & ( 1 << ind2 )) != 0;

	return bvalue1 == bvalue2;
}
//---------------------------------------------------------------------------
Constraint *DECSPConstraint::clone() const
{
	return create( formula, problem, var1, var2, ind1, ind2 );
}
//---------------------------------------------------------------------------
DECSPConstraint::DECSPConstraint( CNFFormula *_formula, CSPProblem *_problem, int _var1, int _var2, int _ind1, int _ind2 )
	: Constraint( _problem, _var1, _var2 )
{
	ind1 = _ind1;
	ind2 = _ind2;
}
//---------------------------------------------------------------------------
DECSPConstraint::~DECSPConstraint()
{
}
//---------------------------------------------------------------------------
DualEncodingSAT2CSP *DualEncodingSAT2CSP::create()
{
	return new DualEncodingSAT2CSP();
}
//---------------------------------------------------------------------------
DualEncodingSAT2CSP::DualEncodingSAT2CSP()
{
	problem = NULL;
}
//---------------------------------------------------------------------------
DualEncodingSAT2CSP::~DualEncodingSAT2CSP()
{
	if ( problem != NULL )
	{
		problem->release();
	}
}
//---------------------------------------------------------------------------
void DualEncodingSAT2CSP::release()
{
	delete this;
}
//---------------------------------------------------------------------------
void DualEncodingSAT2CSP::setFormula( const CNFFormula *_formula )
{
	int i, j, k;
	int numVars;

	formula = *_formula;
	numVars = formula.getNumClauses();

	if ( problem != NULL )
	{
		problem->release();
	}

	problem = CSPProblem::create();
	problem->setNumVars( numVars );

	// Create the domains.
	// There will be one CSP variable for each clause.
	// The clause will contain all possible combinations
	// of allowed values for the variables contained in this clause.
	BasicCSPDomainList *domainList = BasicCSPDomainList::create();
	domainList->setNumDomains( numVars );

	for ( i = 0; i < numVars; i++ )
	{
		int clauseNumVars = formula.getClause(i)->getNumVars();
		int domainSize = (int)pow( 2, clauseNumVars ) - 1;
		CSPVariableDomain *domain = CSPVariableDomain::create( domainSize );

		// Get the value forbidden by this clause
		int forbiddenValue = getForbiddenValue( i );

		// Adds all possible values except the forbidden one.
		for ( j = 0, k = 0; k < domainSize; j++ )
		{
			if ( j != forbiddenValue )
			{
				domain->addValue( k, BasicCSPVariableValue::create( j ) );
				k++;
			}
		}

		domainList->setDomain( i, domain );
	}

	problem->setDomainList( domainList );

	// Create the constraints
	// first, we create a vector with all clauses each variable appears
	int numSATVars = formula.getNumVars();
	vector< vector< pair< int, int > > > variableClauses( numSATVars );
	for ( i = 0; i < numVars; i++ )
	{
		int clauseNumVars = formula.getClause( i )->getNumVars();
		for ( j = 0; j < clauseNumVars; j++ )
		{
			int var = formula.getClause( i )->getVariableIndex( j );
			variableClauses[var].push_back( make_pair( i, j ) );
		}
	}

	BasicCSPConstraintList *constraintList = BasicCSPConstraintList::create();

	// Now we build the constraints between clauses that have a propositional
	// variable in common
	for ( i = 0; i < numSATVars; i++ )
	{
		for ( j = 0; j < variableClauses[i].size(); j++ )
		{
			int clause1 = variableClauses[i][j].first;
			int ind1    = variableClauses[i][j].second;

			for ( k = j + 1; k < variableClauses[i].size(); k++ )
			{
				int clause2 = variableClauses[i][k].first;
				int ind2    = variableClauses[i][k].second;

				constraintList->addConstraint( DECSPConstraint::create( &formula, problem, clause1, clause2, ind1, ind2 ) );
			}
		}
	}

	problem->setConstraintList( constraintList );

}
//---------------------------------------------------------------------------
CSPProblem *DualEncodingSAT2CSP::getProblem() const
{
	return problem;
}
//---------------------------------------------------------------------------
bool DualEncodingSAT2CSP::getSATInterpretation( const CSPInterpretation &cspi, Interpretation &sati )
{
	// Let's walk through all CSP variables to find wich value is assigned
	// to each propositional variable.
	vector< bool > instantiated( formula.getNumVars() );
	int i, j;

	for ( i = 0; i < formula.getNumVars(); i++ )
	{
		instantiated[i] = false;
	}

	if ( cspi.getNumVariables() != formula.getNumClauses() )
	{
		return false;
	}

	for ( i = 0; i < formula.getNumClauses(); i++ )
	{
		// Get the domain of this dual variable
		CSPVariableDomain *domain = (CSPVariableDomain *)problem->getDomainList()->getDomain( i );

		// Get the value index from the interpretation
		int  valueIndex = cspi.getVariableValue( i );

		// Get the variable value object
		BasicCSPVariableValue *value = (BasicCSPVariableValue *)domain->getValue( valueIndex );

		// Get the actual value assigned to this dual variable
		int cspValue = value->getValue();

		// Now let's walk through all propositional variables in the
		// corresponding clause and check which value it got assigned
		// in the dual variable
		int clauseNumVars = formula.getClause(i)->getNumVars();
		for ( j = 0; j < clauseNumVars; j++ )
		{
			// Get the index and the sign of the jth variable
			int variable = formula.getClause(i)->getVariableIndex( j );
			bool value   = (cspValue & ( 1 << j )) != 0;

			// If this variable has already been instantiated,
			// let`s check if the value in this dual variable is consistent
			// with the previous value found.
			if ( instantiated[variable] )
			{
				if ( value != sati.getValue( variable ) )
				{
					return false;
				}
			}
			else
			{
				// If the variable has not been instantiated,
				// let`s set it`s value and the instantiated flag.
				sati.setValue( variable, value );
				instantiated[variable] = true;
			}
		}
	}

	return true;
}
//---------------------------------------------------------------------------
int DualEncodingSAT2CSP::getForbiddenValue( int clause )
{
	int value = 0;
	const Clause *pclause = formula.getClause( clause );

	for ( int i = 0; i < pclause->getNumVars(); i++ )
	{
		bool sign = pclause->isVariablePositive( i );
		if ( sign == false )
		{
			value|= ( 1 << i );
		}
	}

	return value;
}
//---------------------------------------------------------------------------


#include <iostream>

#include <util/Random.h>
#include <csp/BasicCSP.h>
#include <csp/BasicCSPConstraintList.h>
#include <csp/BasicCSPDomainList.h>
#include <csp/RandomCSP.h>
#include <csp/CSPProblem.h>

//---------------------------------------------------------------------------
RandomCSPConstraint *RandomCSPConstraint::create( CSPProblem *problem, int var1, int var2 )
{
	return new RandomCSPConstraint( problem, var1, var2 );
}
//---------------------------------------------------------------------------
void RandomCSPConstraint::release()
{
	delete this;
}
//---------------------------------------------------------------------------
void RandomCSPConstraint::addPair( int var1Value, int var2Value )
{
	BasicCSPDomainList *domainList = (BasicCSPDomainList*)problem->getDomainList();
	
	CSPVariableDomain *domain1 = domainList->getDomain( var1 );
	BasicCSPVariableValue *variableValue1 = (BasicCSPVariableValue *)domain1->getValue( var1Value );	
	int actualValue1 = variableValue1->getValue();

	CSPVariableDomain *domain2 = domainList->getDomain( var2 );
	BasicCSPVariableValue *variableValue2 = (BasicCSPVariableValue *)domain2->getValue( var2Value );	
	int actualValue2 = variableValue2->getValue();

	if ( forbidden.count( make_pair( actualValue1, actualValue2 ) ) == 0 )
	{
		forbidden.insert( make_pair( actualValue1, actualValue2 ) );
	}
}
//---------------------------------------------------------------------------
bool RandomCSPConstraint::passes( int var1Value, int var2Value ) const
{
	BasicCSPDomainList *domainList = (BasicCSPDomainList*)problem->getDomainList();
	
	CSPVariableDomain *domain1 = domainList->getDomain( var1 );
	BasicCSPVariableValue *variableValue1 = (BasicCSPVariableValue *)domain1->getValue( var1Value );	
	int actualValue1 = variableValue1->getValue();

	CSPVariableDomain *domain2 = domainList->getDomain( var2 );
	BasicCSPVariableValue *variableValue2 = (BasicCSPVariableValue *)domain2->getValue( var2Value );	
	int actualValue2 = variableValue2->getValue();

	if ( forbidden.count( make_pair( actualValue1, actualValue2 )  ) > 0 )
	{
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
Constraint *RandomCSPConstraint::clone() const
{
	RandomCSPConstraint *other = create( problem, var1, var2 );
	other->forbidden = forbidden;

	return other;
}
//---------------------------------------------------------------------------
RandomCSPConstraint::RandomCSPConstraint( CSPProblem *problem, int var1, int var2 )
: Constraint( problem, var1, var2 )
{

}
//---------------------------------------------------------------------------
CSPProblem *RandomCSPFactory::create( int n, int m, double p1, double p2, bool forceSatisfiable )
{
	int i, j;

	CSPInterpretation interpretation;

	if ( forceSatisfiable )
	{
		interpretation.setNumVariables( n );

		for ( i = 0; i < n; i++ )
		{
			interpretation.setVariableValue( i, (int)Random::s_generateUniformVariable( 0, m ) );
		}
	}

	// Create the problem object
	CSPProblem *problem = CSPProblem::create();

	problem->setNumVars( n );

	BasicCSPDomainList *domainList = BasicCSPDomainList::create();
	domainList->setNumDomains( n );

	CSPVariableDomain *domain = CSPVariableDomain::create( m );
	for ( i = 0; i < m; i++ )
	{
		domain->addValue( i, BasicCSPVariableValue::create( i ) );
	}

	for ( j = 0; j < n; j++ )
	{
		domainList->setDomain( j, domain->clone() );
	}

	domain->release();
	domain = NULL;

	problem->setDomainList( domainList );

	BasicCSPConstraintList *constraintList = BasicCSPConstraintList::create();

	for ( i = 0; i < n; i++ )
	{
		for ( j = i + 1; j < n; j++ )
		{
			double random = Random::s_generateUnitUniformVariable();
			if ( random < p1 )
			{
				constraintList->addConstraint( createConstraint( problem, i, j, m, p2, interpretation, forceSatisfiable ) );
			}
		}
	}

	problem->setConstraintList( constraintList );

	// test the problem against the interpretation
	if ( forceSatisfiable )
	{
		if ( problem->isSatisfied( interpretation ) == false )
		{
			return NULL;
		}
	}

	return problem;

}
//---------------------------------------------------------------------------
RandomCSPConstraint *RandomCSPFactory::createConstraint( CSPProblem *problem, int var1, int var2, int m, double p2, CSPInterpretation &interpretation, bool forceSatisfiable )
{
	RandomCSPConstraint *constraint = RandomCSPConstraint::create( problem, var1, var2 );

	vector< pair< int, int > > unpickedPairs;
	int var1Value, var2Value;

	bool pickAnother = false;

	if ( forceSatisfiable )
	{
		pickAnother = Random::s_generateUnitUniformVariable() < p2;
		var1Value = interpretation.getVariableValue( var1 );
		var2Value = interpretation.getVariableValue( var2 );
	}

	for ( int i = 0; i < m; i++ )
	{
		for ( int j = 0; j < m; j++ )
		{
			if ( forceSatisfiable )
			{
				if ( var1Value == i && var2Value == j )
				{
					continue;
				}
			}
			
			double random = Random::s_generateUnitUniformVariable();
			if ( random < p2 )
			{
				constraint->addPair( i, j );
			}
			else if ( forceSatisfiable && pickAnother )
			{
				unpickedPairs.push_back( make_pair( i, j ) );
			}
		}
	}

	if ( forceSatisfiable && pickAnother )
	{
		int pickIndex = (int)Random::s_generateUniformVariable( 0, unpickedPairs.size() );
		constraint->addPair( unpickedPairs[pickIndex].first, unpickedPairs[pickIndex].second );
	}

	return constraint;
}
//---------------------------------------------------------------------------


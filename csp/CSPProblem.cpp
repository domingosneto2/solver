
#include <memory.h>
#include <csp/CSPProblem.h>
#include <set>


//---------------------------------------------------------------------------
CSPExtraData::~CSPExtraData()
{
}


//---------------------------------------------------------------------------
CSPProblem *CSPProblem::create()
{
	return new CSPProblem();
}
//---------------------------------------------------------------------------
void CSPProblem::release()
{
	delete this;
}
//---------------------------------------------------------------------------
CSPProblem *CSPProblem::clone() const
{
	return new CSPProblem( *this );
}
//---------------------------------------------------------------------------
CSPProblem::CSPProblem()
{
	extraData = NULL;
	domainList = NULL;
	constraintList = NULL;
}
//---------------------------------------------------------------------------
CSPProblem::CSPProblem( const CSPProblem &other )
{
	extraData = NULL;
	domainList = NULL;
	constraintList = NULL;
	assign( other );
}
//---------------------------------------------------------------------------
CSPProblem::~CSPProblem()
{
	releaseData();
}
//---------------------------------------------------------------------------
void CSPProblem::releaseData()
{
	if ( domainList != NULL )
	{
		domainList->release();
	}

	if ( constraintList != NULL )
	{
		constraintList->release();
	}

	if ( extraData != NULL )
	{
		extraData->release();
	}

	domainList = NULL;
	constraintList = NULL;
	extraData = NULL;	
}
//---------------------------------------------------------------------------
void CSPProblem::setNumVars( int _numVars )
{
	numVars = _numVars;
}
//---------------------------------------------------------------------------
int CSPProblem::getNumVars() const
{
	return numVars;
}
//---------------------------------------------------------------------------
void CSPProblem::setDomainList( CSPDomainList  *_domainList )
{
	if ( domainList != NULL )
	{
		domainList->release();
	}
	domainList = _domainList;
}
//---------------------------------------------------------------------------
const CSPDomainList *CSPProblem::getDomainList() const
{
	return domainList;
}
//---------------------------------------------------------------------------
void CSPProblem::setConstraintList( CSPConstraintList *_constraintList )
{
	if ( constraintList != NULL )
	{
		constraintList->release();
	}

	constraintList = _constraintList;
}
//---------------------------------------------------------------------------
const CSPConstraintList *CSPProblem::getConstraintList() const
{
	return constraintList;
}
//---------------------------------------------------------------------------
void CSPProblem::assign( const CSPProblem &other )
{
	releaseData();

	numVars = other.numVars;

	if ( other.constraintList != NULL )
	{
		constraintList = other.constraintList->clone();
	}

	if ( other.domainList != NULL )
	{
		domainList = other.domainList->clone();
	}
	
	if ( other.extraData != NULL )
	{
		extraData = other.extraData->clone();
	}
}
//---------------------------------------------------------------------------
const CSPProblem &CSPProblem::operator =( const CSPProblem &other )
{
	assign( other );
	return *this;
}
//---------------------------------------------------------------------------
int CSPProblem::getNumSatisfiedConstraints( const CSPInterpretation &interpretation ) const
{
	int numSatisfiedConstraints = 0;

	constraintList->resetIterator();
	while ( constraintList->nextConstraint() )
	{
		if ( constraintList->passes( interpretation ) )
		{
			numSatisfiedConstraints++;
		}
	}

	return numSatisfiedConstraints;
}
//---------------------------------------------------------------------------
bool CSPProblem::isSatisfied( const CSPInterpretation &interpretation ) const
{
	return getNumSatisfiedConstraints( interpretation ) == constraintList->getNumConstraints();
}
//---------------------------------------------------------------------------
void CSPProblem::setExtraData( CSPExtraData *data )
{
	if ( extraData != NULL )
	{
		extraData->release();
	}
	
	extraData = data;
}
//---------------------------------------------------------------------------
const CSPExtraData *CSPProblem::getExtraData() const
{
	return extraData;
}
//---------------------------------------------------------------------------
// A class used in the arcConsistency method
struct Arc
{
	int var1;
	int var2;

	int constraint;

	bool operator < ( const Arc &other ) const
	{
		if ( var1 < other.var1 ) return true;
		else if ( var1 == other.var1 && var2 < other.var2 ) return true;
		else if ( var1 == other.var1 && var2 == other.var2 && constraint < other.constraint ) return true;
		return false;
	}
};
bool CSPProblem::arcConsistency()
{
	// For each variable, we will hold an array with
	// all constraints this variable is referenced by
	vector< vector< int > > variableConstraints;
	variableConstraints.resize( getNumVars() );

	int numConstraints = constraintList->getNumConstraints();

	int i;
	for ( i = 0; i < numConstraints; i++ )
	{
		variableConstraints[ constraintList->getVar1( i ) ].push_back( i );
		variableConstraints[ constraintList->getVar2( i ) ].push_back( i );
	}	

	set< Arc > arcs;
	// Now, let's create a list with all the constraints,
	// but this list must be bidirectional
	for ( i = 0; i < numConstraints; i++ )
	{
		Arc arc;
		arc.var1 = constraintList->getVar1( i );
		arc.var2 = constraintList->getVar2( i );
		arc.constraint = i;

		arcs.insert( arc );		

		arc.var2 = constraintList->getVar1( i );
		arc.var1 = constraintList->getVar2( i );

		arcs.insert( arc );
	}

	// Now we start to process the arcs list
	while ( arcs.size() > 0 )
	{
		Arc arc = *(arcs.begin());
		arcs.erase( arc );

		int var1 = arc.var1;
		int var2 = arc.var2;

		bool reverse = false;		
		if ( constraintList->getVar1( arc.constraint ) == var2 )
		{
			reverse = true;
		}

		// For each value in var1's domain, we check 
		// if there is a value in var2's domain that satisfies
		// the constraint. If there is no such value in var2's domain,
		// we remove the value from var1 domain, and add all constraints
		// <varX, var1> to the arcs list.
		bool bAdded = false;
		for ( i = 0; i < domainList->getDomainSize( var1 ); i++ )
		{
			bool satisfied = false;
			//for ( int j = 0; j < variableDomains[var2]->getSize(); j++ )
			for ( int j = 0; j < domainList->getDomainSize( var2 ); j++ )
			{
				if ( reverse )
				{					
					if ( constraintList->passes( arc.constraint, j, i ) )
					{
						satisfied = true;
						break;
					}
				}
				else
				{					
					if ( constraintList->passes( arc.constraint, i, j ) ) 
					{
						satisfied = true;
						break;
					}
				}
			}
			
			// couldn't find a value
			// let's remove the value from var1 and add
			// all constraints <Y, var1>
			if ( !satisfied )
			{
				domainList->getDomain( var1 )->removeValue( i );				
				if ( domainList->getDomainSize( var1 ) == 0 )
				{
					// Problem has no solution: return false
					return false;
				}
				// decrement because it will be incremented later,
				// but in the next step we need to be pointing
				// to the same index, that will contain now another value.
				i--; 

				if ( !bAdded )
				{
					for ( int j2 = 0; j2 < variableConstraints[var1].size(); j2++ )
					{
						Arc arc2;
						arc2.var2 = var1;
						arc2.constraint = variableConstraints[var1][j2];
						if ( constraintList->getVar1( arc2.constraint ) != var1 )
						{						
							arc2.var1 = constraintList->getVar1( arc2.constraint );
						}
						else
						{
							arc2.var1 = constraintList->getVar2( arc2.constraint );
						}

						if ( arc2.var1 != var2 )
						{
							if ( arcs.find( arc2 ) == arcs.end() )
							{
								arcs.insert( arc2 );
							}
						}
					}
					bAdded = true;
				}
			}
		}
	}

	return true;
}
//---------------------------------------------------------------------------



#include <stdio.h>
#include <assert.h>
#include <csp/BasicCSPConstraintList.h>


//---------------------------------------------------------------------------
BasicCSPConstraintList *BasicCSPConstraintList::create()
{
	return new BasicCSPConstraintList();
}
//---------------------------------------------------------------------------
void BasicCSPConstraintList::release()
{
	delete this;
}
//---------------------------------------------------------------------------
CSPConstraintList *BasicCSPConstraintList::clone() const
{
	return new BasicCSPConstraintList( *this );
}
//---------------------------------------------------------------------------
BasicCSPConstraintList::BasicCSPConstraintList()
{
	numConstraints = 0;
	curConstraint = -1;
}
//---------------------------------------------------------------------------
BasicCSPConstraintList::BasicCSPConstraintList( const BasicCSPConstraintList &other )
{
	numConstraints = other.numConstraints;
	curConstraint = other.curConstraint;

	constraints.resize( other.constraints.size() );

	for ( int i = 0; i < numConstraints; i++ )
	{
		if ( other.constraints[i] != NULL )
		{
			constraints[i] = other.constraints[i]->clone();
		}
		else
		{
			constraints[i] = NULL;
		}
	}
}
//---------------------------------------------------------------------------
BasicCSPConstraintList::~BasicCSPConstraintList()
{
	for ( int i = 0; i < numConstraints; i++ )
	{
		if ( constraints[i] != NULL )
		{
			constraints[i]->release();
		}
	}
}
//---------------------------------------------------------------------------
void BasicCSPConstraintList::addConstraint( Constraint *constraint )
{
	constraints.push_back( constraint );
	numConstraints++;
}
//---------------------------------------------------------------------------
int BasicCSPConstraintList::getNumConstraints() const
{
	return numConstraints;
}
//---------------------------------------------------------------------------	
bool BasicCSPConstraintList::passes( int constraint, int var1Value, int var2Value ) const
{
	assert( constraints[constraint] != NULL );

	return constraints[constraint]->passes( var1Value, var2Value );
}
//---------------------------------------------------------------------------
int  BasicCSPConstraintList::getVar1( int constraint ) const
{
	assert( constraints[constraint] != NULL );

	return constraints[constraint]->getVar1();
}
//---------------------------------------------------------------------------
int  BasicCSPConstraintList::getVar2( int constraint ) const
{
	assert( constraints[constraint] != NULL );

	return constraints[constraint]->getVar2();
}
//---------------------------------------------------------------------------
bool BasicCSPConstraintList::passes( int constraint, const CSPInterpretation &interpretation ) const
{
	assert( constraints[constraint] != NULL );

	return constraints[constraint]->passes( interpretation );
}
//---------------------------------------------------------------------------
void BasicCSPConstraintList::resetIterator()
{
	curConstraint = -1;
}
//---------------------------------------------------------------------------
bool BasicCSPConstraintList::nextConstraint()
{
	if ( curConstraint == numConstraints - 1 )
	{
		return false;
	}

	curConstraint++;
	return true;
}
//---------------------------------------------------------------------------
int  BasicCSPConstraintList::getCurrentConstraint()
{
	return curConstraint;
}
//---------------------------------------------------------------------------
int  BasicCSPConstraintList::getVar1() const
{
	return getVar1( curConstraint );
}
//---------------------------------------------------------------------------
int  BasicCSPConstraintList::getVar2() const
{
	return getVar2( curConstraint );
}
//---------------------------------------------------------------------------
bool BasicCSPConstraintList::passes( int var1Value, int var2Value ) const
{
	return passes( curConstraint, var1Value, var2Value );
}
//---------------------------------------------------------------------------
bool BasicCSPConstraintList::passes( const CSPInterpretation &interpretation ) const
{
	return passes( curConstraint, interpretation );
}
//---------------------------------------------------------------------------


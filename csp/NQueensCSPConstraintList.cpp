
#include <assert.h>
#include <math.h>
#include <csp/NQueensCSPConstraintList.h>


#define ABS( a ) ( a < 0 ? -(a) : (a) )
//---------------------------------------------------------------------------
NQueensCSPConstraintList::NQueensCSPConstraintList( int n )
{
	// Default initialization
	nVars = n;
	var1 = 0;
	var2 = 0;
	constraint = -1;
}
//---------------------------------------------------------------------------
NQueensCSPConstraintList* NQueensCSPConstraintList::create( int n )
{
	// create and return a new instance
	return new NQueensCSPConstraintList( n );
}
//---------------------------------------------------------------------------
void NQueensCSPConstraintList::release()
{
	// delete itself
	delete this;
}
//---------------------------------------------------------------------------
CSPConstraintList *NQueensCSPConstraintList::clone() const
{
	// return a copy of self
	NQueensCSPConstraintList *ret = new NQueensCSPConstraintList( nVars );
	ret->var1 = var1;
	ret->var2 = var2;
	ret->constraint = constraint;

	return ret;
}
//---------------------------------------------------------------------------
int NQueensCSPConstraintList::getNumConstraints() const
{
	// the number of constraints.
	// there is a constraint between every pair (a, b) of variables, 
	// where a != b.  Since the pair is not ordered (a,b) == (b,a)
	// we divide by two.	
	return ( nVars * nVars - nVars ) / 2;
}
//---------------------------------------------------------------------------
bool NQueensCSPConstraintList::passes( int constraint, int var1Value, int var2Value ) const
{
	int var1 = getVar1( constraint );
	int var2 = getVar2( constraint );

	return passes( var1, var2, var1Value, var2Value );	
}
//---------------------------------------------------------------------------
int  NQueensCSPConstraintList::getVar1( int constraint ) const
{
	return (int)floor( getI( nVars, constraint ) );
}
//---------------------------------------------------------------------------
int  NQueensCSPConstraintList::getVar2( int constraint ) const
{
	return (int)getJ( nVars, constraint );
}
//---------------------------------------------------------------------------
bool NQueensCSPConstraintList::passes( int constraint, const CSPInterpretation &interpretation ) const
{
	int var1 = getVar1( constraint );
	int var2 = getVar2( constraint );

	int var1Value = interpretation.getVariableValue( var1 );
	int var2Value = interpretation.getVariableValue( var2 );

	return passes( var1, var2, var1Value, var2Value );	
}
//---------------------------------------------------------------------------
void NQueensCSPConstraintList::resetIterator()
{
	// restart the iterator
	var1 = 0;
	var2 = 0;
	constraint = -1;
}
//---------------------------------------------------------------------------
bool NQueensCSPConstraintList::nextConstraint()
{
	// jump to the next constraint
	var2++;
	if ( var2 == nVars )
	{
		var1++;
		if ( var1 == nVars - 1)
		{
			return false;
		}
		var2 = var1 + 1;
	}

	constraint++;

	return true;
}
//---------------------------------------------------------------------------
int  NQueensCSPConstraintList::getCurrentConstraint()
{
	return constraint;
}
//---------------------------------------------------------------------------
int  NQueensCSPConstraintList::getVar1() const
{
	return var1;
}
//---------------------------------------------------------------------------
int  NQueensCSPConstraintList::getVar2() const
{
	return var2;
}
//---------------------------------------------------------------------------
bool NQueensCSPConstraintList::passes( int var1Value, int var2Value ) const
{
	return passes( var1, var2, var1Value, var2Value );
}
//---------------------------------------------------------------------------
bool NQueensCSPConstraintList::passes( const CSPInterpretation &interpretation ) const
{
	int var1Value = interpretation.getVariableValue( var1 );
	int var2Value = interpretation.getVariableValue( var2 );

	return passes( var1, var2, var1Value, var2Value );
}
//---------------------------------------------------------------------------
double NQueensCSPConstraintList::getI( int N, double Si ) const
{
	return N - 0.5 - sqrt( ( N - 0.5 ) * ( N - 0.5 ) - 2.0 * Si );
}
//---------------------------------------------------------------------------
double NQueensCSPConstraintList::getJ( int N, double Si ) const
{
    double i = getI( N, Si );
    double f = floor( i );
    
    double Sf = getSi( N, f );
    
    double delta = Si - Sf;
    double j = f + 1 + delta;
    return j;
}
//---------------------------------------------------------------------------
double NQueensCSPConstraintList::getSi( int N, double i ) const
{
	return (double)N * i - i * (i + 1.0) / 2.0;
}
//---------------------------------------------------------------------------
bool NQueensCSPConstraintList::passes( int var1, int var2, int var1Value, int var2Value ) const
{
	// two queens cannot be in the same row
	if ( var1Value == var2Value )
	{
		return false;
	}

	// tow queens cannot be in the same diagonal
	if ( ABS( var1Value - var2Value ) == ABS( var1 - var2 ) )
	{
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------


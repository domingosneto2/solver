
#include <sat/Clause.h>
#include <memory.h>
#include <stdio.h>

//---------------------------------------------------------------------------
/**
 * Default constructor, creates an empty clause.
 */
Clause::Clause()
{
    numVars = 0;
}
//---------------------------------------------------------------------------
/**
 * Creates a copy of another clause.
 */
Clause::Clause( const Clause &other )
{
    numVars = 0;

	assign( other );
}
//---------------------------------------------------------------------------
/**
 * Destructor, releases allocated data.
 */
Clause::~Clause()
{

}
//---------------------------------------------------------------------------
/**
 * Sets the number of variables of this clause.
 */
void Clause::init()
{    
    numVars = 0;
	
	indexes.resize( 0 );
	signs.resize( 0 );
}
//---------------------------------------------------------------------------
/**
 * Sets the n-th variable of the clause to the m-th variable
 * of the enclosing Formula, with a given sign. 
 * <p>
 * If you call setVariable( 2, false, 3 ), it means
 * that the 4th variable of the formula appears negated as the
 * third variable of the clause.
 *
 * @param myIndex  index of the variable in the clause (0-based).
 * @param sign     if false, the variable is negated.
 * @param hisIndex index of the variable in the variable (0-based).
 *
 * 
 */
void Clause::initVariable( int myIndex, bool sign, int hisIndex )
{
    if ( myIndex >= numVars )
    {
		numVars = myIndex + 1;
        indexes.resize( numVars );
		signs.resize( numVars );
    }
    
    signs[myIndex] = sign;
    indexes[myIndex] = hisIndex;
}
//---------------------------------------------------------------------------
/** 
 * Evaluates the clause.
 *
 * This method just evaluates everytime the method is called.  
 * This can be improved a lot in local search algorithmis with
 * the help of helper structures, but it's up to the algorithm
 * implementtion to do that.
 */
bool Clause::getValue( const Interpretation &interpretation ) const
{
    for ( int i = 0; i < numVars; i++ )
    {
        bool varValue = interpretation.getValue ( indexes[i] );
        bool sign = signs[i];
        bool myVarValue = sign ? varValue : !varValue;
        
        if ( myVarValue == true )
        {
            return true;
        }
    }
    
    return false;
}
//---------------------------------------------------------------------------
int Clause::getNumVars() const
{
    return numVars;
}
//---------------------------------------------------------------------------
bool Clause::isVariablePositive( int index ) const
{
	return signs[index];
}
//---------------------------------------------------------------------------
/** 
 * Returns the index in the formula of the n-th variable of the clause.
 */
int Clause::getVariableIndex( int clauseIndex ) const
{
	return indexes[clauseIndex];
}
//---------------------------------------------------------------------------
Clause &Clause::operator = ( const Clause &other )
{
	assign( other );
	return *this;
}
//---------------------------------------------------------------------------
void Clause::assign( const Clause &other )
{
	numVars = other.numVars;

	indexes = other.indexes;
	signs   = other.signs;
}
//---------------------------------------------------------------------------

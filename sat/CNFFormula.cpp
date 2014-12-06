
#include <sat/CNFFormula.h>
#include <sat/Interpretation.h>
#include <stdio.h>

//---------------------------------------------------------------------------
/**
 * Default constructor, creates an empty formula.
 */
CNFFormula::CNFFormula()
{
    init();
}
//---------------------------------------------------------------------------
/**
 * Creates a copy of a given formula.
 */
CNFFormula::CNFFormula( const CNFFormula &other )
{
	init();
	assign( other );
}
//---------------------------------------------------------------------------
/**
 * Releases allocated memory.
 */
CNFFormula::~CNFFormula()
{
}
//---------------------------------------------------------------------------
/**
 * Resets the object.
 */
void CNFFormula::init()
{
	numClauses = numVariables = 0;
	clauses.resize( 0 );
}
//---------------------------------------------------------------------------
/**
 * Sets the number of variables.
 *
 * This method only increases the number of variables.  It has no effect
 * if the number of variables is already larger than i.
 */
void CNFFormula::setNumVars( int i )
{
	if ( numVariables < i )
	{
		numVariables = i;
	}
}
//---------------------------------------------------------------------------
/**
 * Initializes a clause.
 *
 * This method resets a clause and prepares it to be built with calls
 * to initClauseVar.
 */
void CNFFormula::initClause( int i )
{
	if ( numClauses <= i )
	{
		numClauses = i + 1;
		clauses.resize( i + 1 );
	}

	clauses[i].init();
}
//---------------------------------------------------------------------------
/**
 * Sets the n-th variable of a clause.
 *
 * This function parameters tells what clause will be affected,
 * the position of the variable in the clause, the sign (if the parameter is
 * false, the variable is negated), and the index of the variable itself.
 *
 * For example, if you have a formula that defines 10 different variables, 
 * and the second clause of this formula has two variables, identified 
 * by the indexes 3 and 7, where the second varialbe appears negated, you would
 * call:
 * formula.initClause( 1 );
 * formula.initClauseVar( 1, 0, true, 3 );
 * formula.initClauseVar( 1, 1, false, 7 );
 * 
 * 
 * Parameters:
 *   clause: the index of the affected clause.
 *   clauseIndex:  the position of the variable in the clause.
 *   sign:  false if the variable is negated; true otherwise.
 *   varIndex:  the index of the variable.
 */
void CNFFormula::initClauseVar( int clause, int clauseIndex, bool sign, int varIndex )
{
    // Check the parameters.
    // We should have a better error handling here!  But for now we just
    // return.
    if ( clause >= numClauses )
    {
        return;
    }

	// Resize the numVars counter if needed
	if ( varIndex >= numVariables )
	{
		numVariables = varIndex + 1;
	}	
    
    // Call the corresponding method in the clause object.
    clauses[clause].initVariable( clauseIndex, sign, varIndex );
}
//---------------------------------------------------------------------------
/**
 * Interpretates a clause and returns its truth-value.
 *
 */
bool CNFFormula::getClauseValue( int index, const Interpretation &interpretation )
{
    // Check the parameters.
    // We should have a better error handling here!  But for now we just
    // return a value.
    if ( index >= numClauses )
    {
        return false;
    }
    
    // Call the corresponding method in the clause object.
    return clauses[index].getValue( interpretation );
}
//---------------------------------------------------------------------------    
/**
 * Evaluates the formula given an interpretation.
 *
 * The Interpretation object holds a value for each variable defined
 * in the formula.
 */
bool CNFFormula::getValue( const Interpretation &interpretation )
{
    // We have to evaluate each clause until we finish
    // or we a clause evaluates to false.
    for ( int i = 0; i < numClauses; i++ )
    {
        // Evaluate the i-th clause.  If it evaluates
        // to false then the whole formula is false
        // and we can skip the remaining clauses.
        if ( clauses[i].getValue( interpretation ) == false )
        {
            return false;
        }
    }
    
    // If we got here then the formula evaluates to true.    
    return true;
}
//---------------------------------------------------------------------------
int CNFFormula::getNumVars() const
{
    return numVariables;
}
//---------------------------------------------------------------------------
int CNFFormula::getNumClauses() const
{
    return numClauses;
}
//---------------------------------------------------------------------------
const Clause *CNFFormula::getClause( int index ) const
{
	return &(clauses[index]);
}
//---------------------------------------------------------------------------
/**
 * A private method that implements the copy of one formula
 * to another.
 */
void CNFFormula::assign( const CNFFormula &other )
{
    // First, we remove any previously allocated data.
	init();

    // Assing the new values for the count variables.
	numVariables = other.numVariables;
	numClauses = other.numClauses;

    clauses = other.clauses;
	
}
//---------------------------------------------------------------------------
CNFFormula &CNFFormula::operator =( const CNFFormula &other )
{
	assign( other );
	return *this;
}
//---------------------------------------------------------------------------
/**
 * Returns the number of satisfied clauses, given an Interpretation.
 *
 * This method is useful for local search algorithms.
 */
int CNFFormula::getNumSatisfiedClauses( const Interpretation &interpretation ) const
{
	int num = 0;
	for ( int i = 0; i < numClauses; i++ )
	{
		if ( clauses[i].getValue( interpretation ) )
		{
			num++;
		}
	}

	return num;
}
//---------------------------------------------------------------------------


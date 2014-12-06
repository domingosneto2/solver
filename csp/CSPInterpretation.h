
#ifndef _CSP_INTERPRETATION_CPP_
#define _CSP_INTERPRETATION_CPP_

//---------------------------------------------------------------------------
/**
 * A candidate solution of a CSP.
 *
 * It contains assignments to every variable of the CSP.
 */
class CSPInterpretation
{
	public:
	CSPInterpretation();
	explicit CSPInterpretation( int numVariables );
	CSPInterpretation( const CSPInterpretation &other );
	~CSPInterpretation();

	void setNumVariables( int numVariables );
	int getNumVariables() const;

	CSPInterpretation &operator = ( const CSPInterpretation &other );
	
	/**
	 * Sets a value to a given variable in this candidate solution.
	 * Note that if the domain list is not a Virtual domain list, the
	 * 'valueIndex' parameter is an index to the value
	 * in the variable's domain.  To get the value itself, you need
	 * to look at the variable's domain in the CSPProblem class.
	 *
	 * This method doesn't validate the input.  It's up to you to ensure
	 * that variable and valueIndex are valid indexes.
	 */
	void setVariableValue( int variable, int valueIndex );

	/**
	 * Returns the index of the value of a given variable.  
	 *
	 * Note that if the domain list os not a Virtual domain list, 
	 * the return value is an index to the variable's value
	 * in the variable's domain.  To get the value itself, you need
	 * to look for the variable's domain in the CSPProblem class.
	 */
	const int getVariableValue( int variable ) const;

	private:
	void clear();
	void assign( const CSPInterpretation &other );
	int *variableValues;
	int numVariables;

};
//---------------------------------------------------------------------------

#endif

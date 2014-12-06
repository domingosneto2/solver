
#ifndef _CSP_VARIABLE_DOMAIN_H_
#define _CSP_VARIABLE_DOMAIN_H_

#include <vector>
using namespace std;

#include <csp/CSPVariableValue.h>

//---------------------------------------------------------------------------
/**
 * A variable domain in a CSP.
 *
 * A domain contains the list of all possible values that can
 * be assigned to a variable of the problem.
 */
class CSPVariableDomain
{
	public:	
	/**
	 * Creates a new CSPVariableDomain object with a given domain size.
	 */
	static CSPVariableDomain *create( int domainSize );	

	/**
	 * Returns a copy of this object.
	 */
	CSPVariableDomain *clone() const;

	/**
	 * Deletes the object.
	 */
	void release();

	/**
	 * Adds a value to the domain.
	 *
	 * Note that the 'value' parameter's ownership will belong to
	 * this class.  Therefore, If you have a CSPVariableValue object
	 * whose ownership you wish to keep, you should call
	 * <code>addValue( n, myValue.clone() )</code>.
	 */
	void addValue( int index, CSPVariableValue *value );

	/**
	 * Returns the value of a domain. The ownership of the returned
	 * object belongs to this class.  Therefore, if you wish to have
	 * ownership over a copy of the returned object, you should call
	 * <code>getValue( n )->clone()</code>. Also notice that if
	 * you delete the CSPVariableDomain object, the reference will
	 * be invalidated.
	 */
	const CSPVariableValue *getValue( int index ) const;

	/*
	 * Assigns to this object the value of another.
	 */
	//CSPVariableDomain &operator=( const CSPVariableDomain &other );

	int getSize() const;

	/**
	 * Removes a value from this domain.
	 */
	void removeValue( int index );

	protected:
	void assign( const CSPVariableDomain &other );
	void clearValues();
	vector< CSPVariableValue * > values;
	int domainSize;

	private:
	//CSPVariableDomain();
	explicit CSPVariableDomain( int domainSize );
	explicit CSPVariableDomain( const CSPVariableDomain &other );
	~CSPVariableDomain();
};
//---------------------------------------------------------------------------

#endif


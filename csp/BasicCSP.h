
#ifndef _BASIC_CSP_H_
#define _BASIC_CSP_H_

#include <csp/CSPProblem.h>
#include <csp/Constraint.h>

//---------------------------------------------------------------------------
/**
 * The subclass of CSPVariableValue for the Basic CSP implementation.
 * <p>
 * This is an implementation of the CSPVariableValue class that maps
 * variable values to integers.
 */
class BasicCSPVariableValue : public CSPVariableValue
{
	public:	
	/**
	 * Creates a new BasicCSPVariableValue object.
	 *
	 * The constructor is protected because classes that 
	 * inherit from CSPVariableValue should never be created
	 * on the stack, only in the heap.  This construct ensures that.
	 */
	static BasicCSPVariableValue *create( int value );

	// Inherited from CSPVariableValue
	virtual bool equals( const CSPVariableValue& other ) const;
	virtual CSPVariableValue *clone() const;
	virtual void set( const CSPVariableValue &other );
	virtual void release();

	// Specific for this implementation
	int getValue() const;

	protected:
	BasicCSPVariableValue( int value );
	int value;
};

#endif


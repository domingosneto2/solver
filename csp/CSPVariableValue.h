
#ifndef _CSP_VARIABLE_VALUE_H_
#define _CSP_VARIABLE_VALUE_H_

//---------------------------------------------------------------------------
/**
 * A single variable value in a CSP.
 *
 * This is an abstract class that represents a single variable value
 * in a CSP.  In order to implement an specific CSP problem that uses the 
 * BasicCSPDomainList class you have to subclass this class.
 *
 * There is already a default implementation, called BasicCSPVariableValue,
 * that maps variable domains to integer values.  When the CSP problem
 * that you want to solve has integers as variable values you can use
 * this class.
 */
class CSPVariableValue
{
	public:
	virtual bool equals( const CSPVariableValue& other ) const = 0;
	virtual CSPVariableValue *clone() const = 0;
	virtual void set( const CSPVariableValue &other ) = 0;
	virtual void release() = 0;

	protected:
	CSPVariableValue();
	virtual ~CSPVariableValue();
};
//---------------------------------------------------------------------------

#endif


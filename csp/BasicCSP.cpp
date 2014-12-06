
#include <csp/BasicCSP.h>


//---------------------------------------------------------------------------
BasicCSPVariableValue *BasicCSPVariableValue::create( int value )
{
	return new BasicCSPVariableValue( value );
}
//---------------------------------------------------------------------------
/**
 * Returns true if both objects hold the same value.
 */
bool BasicCSPVariableValue::equals( const CSPVariableValue& other ) const
{
	BasicCSPVariableValue *pOther = (BasicCSPVariableValue *)&other;

	return value == pOther->value;
}
//---------------------------------------------------------------------------
/**
 * Returns a copy of this object.
 */
CSPVariableValue *BasicCSPVariableValue::clone() const
{
	return new BasicCSPVariableValue( value );
}
//---------------------------------------------------------------------------
/**
 * Assigns the value of another object to this one.
 */
void BasicCSPVariableValue::set( const CSPVariableValue &other )
{
	BasicCSPVariableValue *pOther = (BasicCSPVariableValue *)&other;

	value = pOther->value;
}
//---------------------------------------------------------------------------
/**
 * Releases the memory allocated by this object.
 */
void BasicCSPVariableValue::release()
{
	delete this;
}
//---------------------------------------------------------------------------
int BasicCSPVariableValue::getValue() const
{
	return value;
}
//---------------------------------------------------------------------------
BasicCSPVariableValue::BasicCSPVariableValue( int _value )
{
	value = _value;
}
//---------------------------------------------------------------------------

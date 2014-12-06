
#ifndef _DUAL_ENCODING_SAT_2_CSP_H
#define _DUAL_ENCODING_SAT_2_CSP_H

#include <sat2csp/SAT2CSP.h>
#include <csp/Constraint.h>
#include <csp/CSPVariableValue.h>

//---------------------------------------------------------------------------
class DECSPConstraint : public Constraint
{
	public:
	static DECSPConstraint *create( CNFFormula *formula, CSPProblem *problem, int var1, int var2, int ind1, int ind2 );
	virtual void release();

	virtual bool passes( int var1Value, int var2Value ) const;
	virtual Constraint *clone() const;

	protected:
	DECSPConstraint( CNFFormula *formula, CSPProblem *problem, int var1, int var2, int ind1, int ind2);
	~DECSPConstraint();

	int ind1, ind2;
	CNFFormula *formula;
};
//---------------------------------------------------------------------------
/**
 * Base class for SAT to CSP converters.
 *
 * There will be a derived class for each implemented encoding.
 *
 * This class has methods for setting the SAT problem to be converted,
 * and then methods to retrieve the corresponding CSP.  There is also
 * a method that will translate a CSP candidate solution into a
 * SAT interpretation.
 */
class DualEncodingSAT2CSP : public SAT2CSP
{
	public:
	static DualEncodingSAT2CSP *create();
	virtual void release();
	virtual void setFormula( const CNFFormula *formula );
	virtual CSPProblem *getProblem() const;

	virtual bool getSATInterpretation( const CSPInterpretation &cspi, Interpretation &sati );

	protected:
	DualEncodingSAT2CSP();
	~DualEncodingSAT2CSP();
	CNFFormula formula;
	CSPProblem *problem;

	private:
	int getForbiddenValue( int clause );
};
//---------------------------------------------------------------------------

#endif

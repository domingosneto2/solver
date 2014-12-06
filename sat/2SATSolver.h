
#ifndef _2SAT_SOLVER_H
#define _2SAT_SOLVER_H

#include <sat/CNFFormula.h>
#include <sat/Interpretation.h>

//------------------------------------------------------------------------------
/**
 *
 * Aqui definimos uma classe que resolve o problema SAT usando o algoritmo
 * 2-SAT.  O problema SAT � representado atrav�s de um objeto CNFFormula.
 *
 * Veja a documenta��o da classe CNFFormula e dos m�todos desta classe para
 * mais detalhes.
 */
class TwoSATSolver
{
	public:
	TwoSATSolver( CNFFormula formula );
	
	 bool solve(Interpretation&param);

	private:
	CNFFormula formula;
};

#endif


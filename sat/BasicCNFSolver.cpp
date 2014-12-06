
#include <sat/Interpretation.h>
#include <sat/BasicCNFSolver.h>

//---------------------------------------------------------------------------
void BasicCNFSolver::solve( CNFFormula *formula, Interpretation &interpretation )
{
    // set all variable values to false
    for ( int i = 0; i < formula->getNumVars(); i++ )
    {
        interpretation.setValue( i, false );
    }
    
    // start the search
    search( formula, interpretation,  0 );
}
//---------------------------------------------------------------------------
// The recursive method of the depth search.
bool BasicCNFSolver::search( CNFFormula *formula, Interpretation &interpretation, int index )
{
    // Get the current var value, to restore it if needed
    bool curVarValue = interpretation.getValue( index );
    
    // Set the variable value to true    
    interpretation.setValue(index, true );    
    if ( formula->getValue( interpretation ) == true )
    {
        return true;
    }
    // Else, search downwards
    if ( index < formula->getNumVars() - 1 )
    {
        if ( search( formula, interpretation, index + 1 ) == true )
        {
            return true;
        }
    }
    
    // Set the variable value to false
    interpretation.setValue(index, false );    
    if ( formula->getValue( interpretation ) == true )
    {
        return true;
    }
    // Else, search downwards
    if ( index < formula->getNumVars() - 1 )
    {
        if ( search( formula, interpretation , index + 1 ) == true )
        {
            return true;
        }
    }
    
    // Restore the value
    interpretation.setValue( index, curVarValue );    
    return false;
}
//---------------------------------------------------------------------------

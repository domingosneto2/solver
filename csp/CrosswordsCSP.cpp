
#include <csp/BasicCSP.h>
#include <csp/CrosswordsCSP.h>
#include <csp/BasicCSPDomainList.h>
#include <csp/BasicCSPConstraintList.h>

//---------------------------------------------------------------------------
CrosswordCSPExtraData *CrosswordCSPExtraData::create()
{
	return new CrosswordCSPExtraData();
}
//---------------------------------------------------------------------------
void CrosswordCSPExtraData::release()
{
	delete this;
}
//---------------------------------------------------------------------------
CSPExtraData * CrosswordCSPExtraData::clone()
{
	CrosswordCSPExtraData *other = create();
	
	if ( dictionary != NULL )
	{
		other->setDictionary( *dictionary );
	}

	return other;
}
//---------------------------------------------------------------------------
WordDictionary *CrosswordCSPExtraData::getDictionary() const
{
	return dictionary;
}
//---------------------------------------------------------------------------
void CrosswordCSPExtraData::setDictionary( const WordDictionary &_dictionary )
{
	if ( dictionary != NULL )
	{
		delete dictionary;
	}

	dictionary = new WordDictionary( _dictionary );
}
//---------------------------------------------------------------------------
CrosswordCSPExtraData::CrosswordCSPExtraData()
{
	dictionary = NULL;
}
//---------------------------------------------------------------------------
CrosswordCSPExtraData::~CrosswordCSPExtraData()
{
	if ( dictionary != NULL )
	{
		delete dictionary;
	}
}
//---------------------------------------------------------------------------
/**
 * Releases the object.
 */
void CrosswordConstraint::release()
{
	delete this;
}
//---------------------------------------------------------------------------
/**
 * Create a constraint of the A type.
 */
CrosswordConstraint *CrosswordConstraint::createTypeA( CSPProblem *problem, int var1, int var2 )
{
	return new CrosswordConstraint( problem, var1, var2, 0 );
}
//---------------------------------------------------------------------------
/**
 * Create a constraint of the B type.
 */
CrosswordConstraint *CrosswordConstraint::createTypeB( CSPProblem *problem, int var1, int var2 )
{
	return new CrosswordConstraint( problem, var1, var2, 1 );
}
//---------------------------------------------------------------------------
/**
 * Returns true if the values pass the constraint.
 * <p>
 * Note that the var1Value and var2Value parameters are indexes
 * to the values and not the values themselves.
 */
bool CrosswordConstraint::passes( int var1Value, int var2Value ) const
{
	BasicCSPDomainList *domainList = (BasicCSPDomainList *)problem->getDomainList();

	const CSPVariableDomain *domain1 = domainList->getDomain( var1 );
	const CSPVariableDomain *domain2 = domainList->getDomain( var2 );

	// Get the value objects, base on the indexes passed as parameters
	BasicCSPVariableValue *value1 = (BasicCSPVariableValue*)(domain1->getValue( var1Value ));
	BasicCSPVariableValue *value2 = (BasicCSPVariableValue*)(domain2->getValue( var2Value ));

	// Get the values themselves
	int ivalue1 = value1->getValue();
	int ivalue2 = value2->getValue();	

	// But the values are also indexes to the word dictionary
	// Lets get the dictionary
	CrosswordCSPExtraData *extraData = (CrosswordCSPExtraData *)problem->getExtraData();
	WordDictionary *dictionary = extraData->getDictionary();

	// Get the strings pointed by the values
	const char *str1 = dictionary->getWord( ivalue1 );
	const char *str2 = dictionary->getWord( ivalue2 );

	// If we have a constraint of type A, the letter in common must be the same.
	if ( type == 0 )
	{
		int row = var1;
		int col = var2 - dictionary->getWordLen();

		if ( str1[col] == str2[row] )
		{
			return true;
		}
		return false;
	}
	// If we have a constraint of type B, the words must be different.
	else
	{
		if ( strcmp( str1, str2 ) == 0 )
		{
			return false;
		}
		{
			return true;
		}
	}
}
//---------------------------------------------------------------------------
Constraint*CrosswordConstraint::clone() const
{
	return new CrosswordConstraint( problem, var1, var2, type );
}
//---------------------------------------------------------------------------
CrosswordConstraint::CrosswordConstraint( CSPProblem *problem, int var1, int var2, int _type )
	: Constraint( problem, var1, var2 )
{
	type = _type;
}
//---------------------------------------------------------------------------
/**
 * Create a new instance of the Crossword CSP problem.
 * <p>
 * This method receive as a parameters the dictionary, the dictionary size and
 * the word size.
 */
CSPProblem *CrosswordsCSPFactory::create( const char **_dictionary, int dictionarySize, int wordSize )
{	
	// Create the WordDictionary object and set it's values
	WordDictionary dictionary( wordSize );
	int i;

	for ( i = 0; i < dictionarySize; i++ )
	{
		dictionary.addWord( _dictionary[i] );
	}

	// Create the ExtraData object and put the WordDictionary in it
	CrosswordCSPExtraData * extraData = CrosswordCSPExtraData::create();
	extraData->setDictionary( dictionary );

	// Create the CSPProblem and put the ExtraData object in it
	CSPProblem *problem = CSPProblem::create();
	problem->setExtraData( extraData );

	// Set the number of variables and the number of constraints
	problem->setNumVars( wordSize * 2 );


	// Create the domain list.  It is a BasicCSPDomainList,
	// this way we can run arcConsistency on this problem.
	BasicCSPDomainList *domainList = BasicCSPDomainList::create();
	domainList->setNumDomains( wordSize * 2 );

	// Initialize the domain of each variable.
	CSPVariableDomain *domain= CSPVariableDomain::create( dictionarySize );
	for ( i = 0; i < dictionarySize; i++ )
	{
		domain->addValue( i, BasicCSPVariableValue::create( i ) );
	}

	// Let's set the variable domains
	for ( i = 0; i < wordSize * 2; i ++ )
	{
		domainList->setDomain( i, domain->clone() );
	}

	domain->release();
	domain = NULL;

	// put the domain list in the problem object
	problem->setDomainList( domainList );


	// Create the constraint list
	BasicCSPConstraintList *constraintList = BasicCSPConstraintList::create();

	// Let's create the constraints between rows and columns
	for ( i = 0; i < wordSize; i++ )
	{
		for ( int j = 0; j < wordSize; j++ )
		{
			constraintList->addConstraint( CrosswordConstraint::createTypeA( problem, i, j + wordSize ) );
		}
	}


	// Let's create the constraints between variables
	for ( int i2 = 0; i2 < wordSize * 2; i2++ )
	{
		for ( int j2 = i2 + 1; j2 < wordSize * 2; j2++ )
		{
			constraintList->addConstraint( CrosswordConstraint::createTypeB( problem, i2, j2 ) );
		}
	}

	problem->setConstraintList( constraintList );

	return problem;
}
//---------------------------------------------------------------------------

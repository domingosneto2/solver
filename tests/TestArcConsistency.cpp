#include <iostream>
#include <csp/CrosswordsCSP.h>
#include <csp/BasicCSP.h>
#include <csp/BasicCSPDomainList.h>

//-----------------------------------------------------------------------------
/* Here we test CSPProblem's arcConsistency method, using the 
 * crosswords construct.
 */

//static char *dictionary[] = { "add", "nao", "dug", "and", "dau", "dog" };
//static int dictSize = 6;
//static int wordlen = 3;

static char *dictionary[] = { "add", "ado", "age", "aid", "and", "bag", "dau", "dog", "dug", "ear", "eft", "nao", "rat" };
static int dictSize = 13;
static int wordlen = 3;

//static char *dictionary[] = { "add", "ado", "age", "aid", "and", "bag", "dau", "dog", "dug", "ear", "eft", "nao", "rat",
//							  "lut", "fut", "fag", "fat", "lom", "sit", "dut", "fog", "luk", "sat", "sms", "xml", "rpc"
//};
//static int dictSize = 26;
//static int wordlen = 3;

int testArcConsistency( int argc, char **argv )
{
	//cout << "testArcConsistency" << endl;

	CSPProblem *problem = CrosswordsCSPFactory::create( (const char **)dictionary, dictSize, wordlen );

	cout << "Before arc consistency: " << endl;
	// We output the variables domain sizes
	int i;
	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		cout << i << ": " << problem->getDomainList()->getDomainSize( i ) << endl;
	}

	// Now, we run arc consistency
	problem->arcConsistency();
	BasicCSPDomainList *domainList = (BasicCSPDomainList *)problem->getDomainList();

	cout << "After arc consistency: " << endl;
	for ( i = 0; i < problem->getNumVars(); i++ )
	{
		cout << i << ": " << domainList->getDomainSize( i ) << endl;
		const CSPVariableDomain *domain = domainList->getDomain( i );
		for ( int j = 0; j < domain->getSize(); j++ )
		{
			BasicCSPVariableValue *value = (BasicCSPVariableValue *)(domain->getValue( j ));
			cout << "\t" << dictionary[ value->getValue() ] << endl;
		}
	}

	problem->release();


	return 0;
};


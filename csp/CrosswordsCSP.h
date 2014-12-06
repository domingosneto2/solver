
#ifndef _CROSSWORDS_CSP_H_
#define _CROSSWORDS_CSP_H_

#include <csp/CSPProblem.h>
#include <csp/Constraint.h>

#include <stdio.h>
#include <memory.h>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
/**
 * A helper class for the Crosswords CSP construct.
 */
class WordDictionary
{
	public:
	WordDictionary( int _wordlen )
	{
		wordlen = _wordlen;
	}
	explicit WordDictionary( const WordDictionary &other )
	{
		wordlen = other.wordlen;
		
		words.resize( other.words.size() );
		for ( int i = 0; i < words.size(); i++ )
		{
			if ( other.words[i] != NULL )
			{
				words[i] = new char[wordlen + 1];
				memcpy( words[i], other.words[i], wordlen );
				words[i][wordlen] = 0;
			}
		}
	}
	~WordDictionary()
	{
		for ( int i = 0; i < words.size(); i++ )
		{
			if ( words[i] != NULL )
			{
				delete[]words[i];
			}
		}
	}

	void addWord( const char *word )
	{
		char *c = new char[wordlen + 1];
		memcpy( c, word, wordlen );
		c[wordlen] = 0;

		words.push_back( c );
	}
	const char * getWord( int index ) const
	{
		return words[index];
	}

	int getSize() const
	{
		return words.size();
	}

	int getWordLen() const
	{
		return wordlen;
	}

	private:
	vector< char * >words;
	int wordlen;
};
//---------------------------------------------------------------------------
class CrosswordCSPExtraData : public CSPExtraData
{
	public:
	static CrosswordCSPExtraData *create();
	void release();
	CSPExtraData * clone();

	WordDictionary *getDictionary() const;
	void setDictionary( const WordDictionary &dictionary );

	protected:
	CrosswordCSPExtraData();	
	~CrosswordCSPExtraData();

	WordDictionary *dictionary;
};
//---------------------------------------------------------------------------
/**
 * A crossword CSP constraint.
 * <p>
 * The crossword CSP has two types of constraints:
 * <ul>
 * <li>Type A:  The letter in common between the given row and the given column mus be  equal in both variables.
 * <li>Type B:  The words assigned to the given pair of variables must be different.
 * </ul>
 *
 * The constraint will get the dictionary information from the extraData field of the problem.
 * This field must be of type CrosswordCSPExtraData
 */
class CrosswordConstraint : public Constraint
{
	public:
	void release();
	static CrosswordConstraint *createTypeA( CSPProblem *problem, int var1, int var2 );
	static CrosswordConstraint *createTypeB( CSPProblem *problem, int var1, int var2 );

	bool passes( int var1Value, int var2Value ) const;
	Constraint *clone() const;

	protected:
	CrosswordConstraint( CSPProblem *problem, int var1, int var2, int type );
		
	int type;
	int letter;	
};
//---------------------------------------------------------------------------
/**
 * A factory that creates an instance of the Crosswords CSP problem. 
 * <p>
 * This class is usedto hide the complexity of creating the CSPProblem object 
 * and setting it's various initialization parameters.
 * <p>
 * The Crosswords CSP problem is described as follows:
 * <p>
 * Suppose you have a nxn board and a dictionary with m words with n letters each.
 * You have to find a way to arrange theses words in the rows and columns of 
 * the board, without repetition.
 * <p>
 * Example:<br>
 * n = 3<br>
 * m = 13<br>
 * dictionary = "add", "ado", "age", "aid", "and", "bag", "dau", "dog", 
 *              "dug", "ear", "eft", "nao", "rat"
 * <p>
 * A possible solution would be:
 * <p>
 * a d d<br>
 * n a o<br>
 * d u g<br>
 * <p>
 * In this implementation, the first three variables represent the rows
 * and the remaining three variables represent the columns.
 * The variable values are indexes to a word dictionary that is represented
 * by a WordDictionary object.  This object is stored in a CrosswordCSPExtraData
 * object that extends the CSPExtraData class and is retrieved by the 
 * getExtraData method.
 */
class CrosswordsCSPFactory
{
	public:
	static CSPProblem *create( const char **dictionary, int dictonarySize, int wordSize );	
};
//---------------------------------------------------------------------------

#endif

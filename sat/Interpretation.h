
#ifndef _INTERPRETATION_H
#define _INTERPRETATION_H


//---------------------------------------------------------------------------
/**
 * Defines a logical interpretation of a formula.
 *
 * This class assigns values to variables of a logical formula.  It is
 * not associated explicitly to a Formula object;  therefore, it can
 * be use as an interpretation of any formula with the same number
 * of variables.
 *
 * The values are stored as bits in a vector.
 */
class Interpretation
{
	public:
	typedef unsigned long inner_type;

	explicit Interpretation( int size );
	Interpretation( const Interpretation &other );
	~Interpretation();

	Interpretation& operator=( const Interpretation &other );
	void assign( const Interpretation &other );

	/**
	 * Assigns a bit vector to this interpretatio object.
	 * <p>
	 * Notice that the bit vector will belong to this object.
	 * If you want to assing a copy of a given bit vector you should
	 * call assignCopy instead.
	 * <p>
	 * OBS: This method will be deprecated in future versions.
	 */
	void assign( void *vector, int size );

	/**
	 * Assigns a bit vector to this interpretation object.
	 * <p>
	 * Unlike the assign method, this method will store a copy
	 * of the vector passed as parmeter, instead of the vector
	 * itself.
	 */
	void assignCopy( void *vector, int size );

	bool getValue( int index ) const;
	void setValue( int index, bool value );

	void flip( int index );

	int getSize() const;

	static bool getValue( void *vector, int index );
	static void setValue( void *vector, int index, bool value );

	static void flip( void *vector, int index );

	private:
	
	inner_type *vector;
	int vectorSize;
	int size;
	bool owner;
};
//---------------------------------------------------------------------------

#endif


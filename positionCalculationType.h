/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __positionCalculationType_H
#define __positionCalculationType_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class positionCalculationType: public Atomic
{
public:
	positionCalculationType( const string &name = "positionCalculationType" ) ;	 // Default constructor
	~positionCalculationType();					// Destructor
	virtual string className() const
		{return "positionCalculationType";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	// [(!) TODO: declare ports, distributions and other private varibles here]
	Port &positionOut;
	Port &positionDiffOut;
	const Port &speedIn;
	/***********      Example declarations   **********************************/
	// const Port &in;	// this is an input port named 'in'
	// Port &out ;   	// this is an output port named 'out'
	// Distribution *dist ;
	// Distribution &distribution()	{ return *dist; }
	/**************************************************************************/

	// [(!) declare common variables]
	double currentPosition;
	double positionDifference;
	double previousSpeed;

	Time calculationTime;
	Time lastUpdateTime;
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	
};	// class positionCalculationType


#endif   //__positionCalculationType_H 

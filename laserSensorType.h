/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __laserSensorType_H
#define __laserSensorType_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class laserSensorType: public Atomic
{
public:
	laserSensorType( const string &name = "laserSensorType" ) ;	 // Default constructor
	~laserSensorType();					// Destructor
	virtual string className() const
		{return "laserSensorType";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	// [(!) TODO: declare ports, distributions and other private varibles here]

	const Port &positionIn;
	const Port &actualHeightIn;
	Port &laserReadingOut;
	/***********      Example declarations   **********************************/
	// const Port &in;	// this is an input port named 'in'
	// Port &out ;   	// this is an output port named 'out'
	// Distribution *dist ;
	// Distribution &distribution()	{ return *dist; }
	/**************************************************************************/

	double currentPosition;
	double currentHeight;
	double laserReading;
	// [(!) declare common variables]
	Time laserReadTime;
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	
};	// class laserSensorType


#endif   //__laserSensorType_H 

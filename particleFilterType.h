/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __particleFilterType_H
#define __particleFilterType_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;
#define NUM_PARTICLES 100

struct particleStruct{
	double weight;
	double location;
};

/** declarations **/
class particleFilterType: public Atomic
{
public:
	particleFilterType( const string &name = "particleFilterType" ) ;	 // Default constructor
	~particleFilterType();					// Destructor
	virtual string className() const
		{return "particleFilterType";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	// [(!) TODO: declare ports, distributions and other private varibles here]
	/***********      Example declarations   **********************************/
	// const Port &in;	// this is an input port named 'in'
	// Port &out ;   	// this is an output port named 'out'
	// Distribution *dist ;
	// Distribution &distribution()	{ return *dist; }
	/**************************************************************************/

	Port &estimatedPoseOut;
	const Port &laserReadingIn;
	const Port &positionDifferenceIn;
	const Port &actualHeightIn;

	particleStruct particles[NUM_PARTICLES];
	particleStruct resampledParticles[NUM_PARTICLES];
	double actualHeight;
	double laserReading;
	double sigmaMN; //standard deviation of measurement noise
	double measDiff;
	double weightSum;
	double weightCutOff;
	double sampleSum;
	double maxWeight;
	double estimatedPose;
	int maxWeightIndex;
	Time pfCalculationTime;
	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	
};	// class particleFilterType


#endif   //__particleFilterType_H 

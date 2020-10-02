/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "particleFilterType.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator

#include "groundTruth.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


/*******************************************************************
* Function Name: particleFilterType
* Description: constructor
********************************************************************/
particleFilterType::particleFilterType( const string &name )
: Atomic( name )
,estimatedPoseOut(addOutputPort("Estimated_Position"))
,laserReadingIn(addInputPort("Laser_reading"))
,positionDifferenceIn(addInputPort("Position_difference"))
,actualHeightIn(addInputPort("Height"))
,pfCalculationTime(0,0,0,2)
{
	sigmaMN = 0.01; //standard deviation of measurements of the laser sensor, this would be available in the sensor data sheet of a real sensor
	srand((unsigned)time(NULL));
	for(int i=0; i<NUM_PARTICLES; i++)
	{
		particles[i].weight = 1/NUM_PARTICLES;
		particles[i].location = 2*((double) rand() / (RAND_MAX)) - 1 ; //generate uniform random particles between -1 and +1
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &particleFilterType::initFunction()
{
	// [(!) Initialize common variables]
	this->elapsed = Time::Zero;
 	this->timeLeft = Time::Inf;
 	this->sigma = Time::Inf;
 	//this->sigma = Time::Zero; // force an internal transition in t=0;
 	
 	passivate(); //wait till inputs from other blocks arrive to run the particle filter
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &particleFilterType::externalFunction( const ExternalMessage &msg )
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
 	this->timeLeft = this->sigma - this->elapsed; 

 	if(msg.port() == laserReadingIn)
 	{
 		laserReading = msg.value();
 		weightSum = 0;

 		for(int i=0;i<NUM_PARTICLES; i++)
 		{
 			measDiff = actualHeight - getGroundHeight(particles[i].location) - laserReading;
 			particles[i].weight = 1/(2.506628*sigmaMN)*exp(measDiff*measDiff/(2*sigmaMN*sigmaMN)); //estimate weight using standard normal pdf
 			weightSum+=particles[i].weight;
 		}
 		for(int i=0;i<NUM_PARTICLES; i++)
 		{
 			weightCutOff = weightSum*((double) rand() / (RAND_MAX)); //random number between 0 and weight sum
 			sampleSum = 0;
 			for(int j=0; j<NUM_PARTICLES; j++)
 			{
 				sampleSum += particles[j].weight;
 				if(sampleSum >= weightCutOff)
 				{
 					resampledParticles[i].location = particles[j].location;
 					resampledParticles[i].weight = particles[j].weight;
 					break;
 				}
 			}
 		}

 		maxWeight = 0;
 		for(int i=0; i<NUM_PARTICLES; i++)
 		{
 			if(resampledParticles[i].weight > maxWeight)
 			{
 				maxWeight = resampledParticles[i].weight;
 				maxWeightIndex = i;
 			}
 		}
 		//calculate new particles
 		estimatedPose = resampledParticles[maxWeightIndex].location;
 		for(int i=0;i<NUM_PARTICLES;i++)
 		{
 			particles[i].location = resampledParticles[i].location;
 			particles[i].weight = resampledParticles[i].weight;
 		}
 		holdIn(active, pfCalculationTime);		//simulate calculation time of new particles
 	}

 	if(msg.port() == positionDifferenceIn)
 	{
 		for(int i=0;i<NUM_PARTICLES; i++)
 		{
 			particles[i].location += (msg.value() + 0.05*((double) rand() / (RAND_MAX)) -0.025); //add random noise
  		}
 	}

 	if(msg.port() == actualHeightIn)
 	{
 		actualHeight = msg.value();
 	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &particleFilterType::internalFunction( const InternalMessage & )
{

	this->sigma = Time::Inf; // stays in passive state until an external event occurs;
	holdIn( passive, this->sigma  );
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &particleFilterType::outputFunction( const InternalMessage &msg )
{
	sendOutput(msg.time(),estimatedPoseOut,estimatedPose);
	return *this;

}

particleFilterType::~particleFilterType()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}

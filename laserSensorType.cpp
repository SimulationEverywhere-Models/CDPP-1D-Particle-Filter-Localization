/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "laserSensorType.h"           // base header
#include "groundTruth.h"
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: laserSensorType
* Description: constructor
********************************************************************/
laserSensorType::laserSensorType( const string &name )
: Atomic( name )
// TODO: add ports here if needed (Remember to add them to the .h file also). Each in a new line.
// Ej:
// ,out(addOutputPort( "out" ))
// , in(addInputPort( "in" ))
, positionIn(addInputPort("Position"))
, actualHeightIn(addInputPort("Height"))
, laserReadingOut(addOutputPort("Laser_Reading"))
, laserReadTime( 0, 0, 0, 10 )
{
	currentHeight = 0;
	currentPosition = 0;
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &laserSensorType::initFunction()
{
	// [(!) Initialize common variables]
	this->elapsed = Time::Zero;
 	this->timeLeft = Time::Inf;
 	this->sigma = Time::Inf; // stays in active state until an external event occurs;
 	//this->sigma = Time::Zero; // force an internal transition in t=0;
 	
 	// set next transition
 	holdIn( passive, this->sigma  ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &laserSensorType::externalFunction( const ExternalMessage &msg )
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
 	this->timeLeft = this->sigma - this->elapsed; 
	
 	if(msg.port() == positionIn)
 	{
 		currentPosition = msg.value();
 		laserReading = currentHeight - getGroundHeight(currentPosition);
 		holdIn( active, laserReadTime );  //simulate the delay in reading laser sensor measurements
 	}

 	if(msg.port() == actualHeightIn)
 	{
 		currentHeight = msg.value();
 	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &laserSensorType::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here


	this->sigma = Time::Inf; // stays in passive state until an external event occurs;
	holdIn( passive, this->sigma  );
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &laserSensorType::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	//std::cout<<"laser: "<<laserReading<<std::endl;
	sendOutput(msg.time(),laserReadingOut, laserReading);
	return *this;

}

laserSensorType::~laserSensorType()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}

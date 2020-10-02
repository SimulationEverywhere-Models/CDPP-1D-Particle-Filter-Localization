/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "positionCalculationType.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: positionCalculationType
* Description: constructor
********************************************************************/
positionCalculationType::positionCalculationType( const string &name )
: Atomic( name )
,positionOut(addOutputPort("Position"))
,positionDiffOut(addOutputPort("Position_Diff"))
,speedIn(addInputPort("Speed"))
,calculationTime(0,0,0,1)	//allocate 1ms to simulate the delay in calculating position
{
	currentPosition = 0.0; //initialize to initial pose
	previousSpeed = 0.0; //initial speed initialized to 0
	lastUpdateTime = Time::Zero;
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &positionCalculationType::initFunction()
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
Model &positionCalculationType::externalFunction( const ExternalMessage &msg )
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
 	this->timeLeft = this->sigma - this->elapsed;

 	if(msg.port() == speedIn)
 	{
 		positionDifference = (msg.value() + previousSpeed)/2 * (msg.time() - lastUpdateTime).asMsecs() / 1000;
 		currentPosition += positionDifference;
 		previousSpeed = msg.value();
 		holdIn( active, calculationTime );  //simulate the time to calculate position in a real system
 		lastUpdateTime = msg.time();
 	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &positionCalculationType::internalFunction( const InternalMessage & )
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
Model &positionCalculationType::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	sendOutput(msg.time(),positionOut,currentPosition);
	sendOutput(msg.time(),positionDiffOut, positionDifference);
	//std::cout<<"Position output: "<<currentPosition<<std::endl;
	return *this;

}

positionCalculationType::~positionCalculationType()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}

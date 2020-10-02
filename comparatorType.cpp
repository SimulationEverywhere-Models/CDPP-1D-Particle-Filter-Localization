/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "comparatorType.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: comparatorType
* Description: constructor
********************************************************************/
comparatorType::comparatorType( const string &name )
: Atomic( name )
// TODO: add ports here if needed (Remember to add them to the .h file also). Each in a new line.
// Ej:
// ,out(addOutputPort( "out" ))
// , in(addInputPort( "in" ))
,pfEstimatedPosIn(addInputPort("Estimated_pose_PF"))
,odometryPosIn(addInputPort("Odometry_Pos"))
,errorOut(addOutputPort("Error"))
{
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &comparatorType::initFunction()
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
Model &comparatorType::externalFunction( const ExternalMessage &msg )
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
 	this->timeLeft = this->sigma - this->elapsed; 

 	if(msg.port() == pfEstimatedPosIn)
 	{
 		pfPosition = msg.value();
 		error = pfPosition - odomPosition;
 		holdIn(active,Time::Zero); //force output
 	}

 	if(msg.port() == odometryPosIn)
 	{
 		odomPosition = msg.value();
 	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &comparatorType::internalFunction( const InternalMessage & )
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
Model &comparatorType::outputFunction( const InternalMessage &msg )
{
	sendOutput(msg.time(), errorOut, error);
	return *this;

}

comparatorType::~comparatorType()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}

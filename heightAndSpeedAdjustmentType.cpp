/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "heightAndSpeedAdjustmentType.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: heightAndSpeedAdjustmentType
* Description: constructor
********************************************************************/
heightAndSpeedAdjustmentType::heightAndSpeedAdjustmentType( const string &name )
: Atomic( name )
// TODO: add ports here if needed (Remember to add them to the .h file also). Each in a new line.
// Ej:
, actualHeightOut(addOutputPort( "ActualHeight" ))
, actualSpeedOut(addOutputPort( "ActualSpeed"))
, desiredHeightIn(addInputPort("DesiredHeight"))
, desiredSpeedIn(addInputPort( "DesiredSpeed" ))
, publishPeriod(0,0,0,100)
{

	//String time( MainSimulator::Instance().getParameter( description(), "Publish period" ) ) ;
	actualSpeed = 0;
	actualHeight = 10;
	referenceSpeed = 0;
	referenceHeight = 0;

	kPSpeed = 0.05;
	kPHeight = 0.05;
	/*if (time != "")
	{
		publishPeriod = time;
	}*/
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &heightAndSpeedAdjustmentType::initFunction()
{
	// [(!) Initialize common variables]
	this->elapsed = Time::Zero;
 	this->timeLeft = Time::Inf;
 	this->sigma = Time::Zero; // force an internal transition in t=0;
 	
 	// set next transition
 	holdIn( active, this->sigma  ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &heightAndSpeedAdjustmentType::externalFunction( const ExternalMessage &msg )
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
 	this->timeLeft = this->sigma - this->elapsed; 

 	if(msg.port() == desiredHeightIn)
 	{
 		referenceHeight = msg.value();
 	}
 	if(msg.port() == desiredSpeedIn)
 	{
 		referenceSpeed = msg.value();
 	}
	
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &heightAndSpeedAdjustmentType::internalFunction( const InternalMessage & )
{
	if(referenceSpeed == actualSpeed && referenceHeight == actualHeight && actualHeight == 0 && actualSpeed == 0)
	{
		std::cout<<"Helicopter halted"<<std::endl;
		passivate(); //the helicopter has come to a halt
	}
	else
	{
		speedError = referenceSpeed - actualSpeed;
		if(fabs(speedError)<0.02/kPSpeed)
		{
			actualSpeed = referenceSpeed;  //filter out small errors
		}
		else
		{
			actualSpeed += speedError * kPSpeed; //adjust speed
		}

		heightError = referenceHeight - actualHeight;
		if(fabs(heightError)<0.02/kPHeight)
		{
			actualHeight = referenceHeight; //filter out small errors
		}
		else
		{
			actualHeight += heightError * kPHeight;	//adjust height
		}

		holdIn(active, this->publishPeriod);	//hold in active till next speed update
	}
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &heightAndSpeedAdjustmentType::outputFunction( const InternalMessage &msg )
{
	sendOutput(msg.time(), actualSpeedOut, actualSpeed);
	sendOutput(msg.time(), actualHeightOut, actualHeight);
	return *this;

}

heightAndSpeedAdjustmentType::~heightAndSpeedAdjustmentType()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}

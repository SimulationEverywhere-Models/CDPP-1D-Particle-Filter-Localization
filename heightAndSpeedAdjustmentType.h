/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __heightAndSpeedAdjustmentType_H
#define __heightAndSpeedAdjustmentType_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/

/** declarations **/
class heightAndSpeedAdjustmentType: public Atomic
{
public:
	heightAndSpeedAdjustmentType( const string &name = "heightAndSpeedAdjustmentType" ) ;	 // Default constructor
	~heightAndSpeedAdjustmentType();					// Destructor
	virtual string className() const
		{return "heightAndSpeedAdjustmentType";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &desiredHeightIn;
	const Port &desiredSpeedIn;
	Port &actualHeightOut;
	Port &actualSpeedOut;

	double referenceHeight,referenceSpeed,actualSpeed,actualHeight;
	double kPSpeed,kDSpeed,kISpeed,speedError,speedIntegral,speedDerivative;
	double kPHeight,kDHeight,kIHeight,heightError,heightIntegral,heightDerivative;
	Time publishPeriod;
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	
};	// class heightAndSpeedAdjustmentType


#endif   //__heightAndSpeedAdjustmentType_H 

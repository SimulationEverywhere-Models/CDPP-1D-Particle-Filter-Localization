[Top]
components : heightAndSpeedAdjustment@heightAndSpeedAdjustmentType 
out : actualHeightOut actualSpeedOut 
in : desiredSpeedIn desiredHeightIn 
Link : desiredSpeedIn DesiredSpeed@heightAndSpeedAdjustment
Link : desiredHeightIn DesiredHeight@heightAndSpeedAdjustment
Link : ActualHeight@heightAndSpeedAdjustment actualHeightOut
Link : ActualSpeed@heightAndSpeedAdjustment actualSpeedOut

[heightAndSpeedAdjustment]



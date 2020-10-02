[Top]
components : heightAndSpeedAdjustment@heightAndSpeedAdjustmentType comparator@comparatorType flightComputer 
out : Error 
in : speed height 
Link : Error@comparator Error
Link : height DesiredHeight@heightAndSpeedAdjustment
Link : speed DesiredSpeed@heightAndSpeedAdjustment
Link : ActualHeight@heightAndSpeedAdjustment height@flightComputer
Link : ActualSpeed@heightAndSpeedAdjustment speed@flightComputer
Link : position@flightComputer Odometry_Pos@comparator
Link : estimated_position@flightComputer Estimated_pose_PF@comparator

[heightAndSpeedAdjustment]
Publish period : 00:00:10:000

[comparator]

[flightComputer]
components : positionCalculation@positionCalculationType laserSensor@laserSensorType particleFilter@particleFilterType 
out : position estimated_position 
in : speed height 
Link : speed Speed@positionCalculation
Link : height Height@laserSensor
Link : height Height@particleFilter
Link : Position@positionCalculation Position@laserSensor
Link : Position_Diff@positionCalculation Position_difference@particleFilter
Link : Laser_Reading@laserSensor Laser_reading@particleFilter
Link : Position@positionCalculation position
Link : Estimated_Position@particleFilter estimated_position

[positionCalculation]

[laserSensor]

[particleFilter]




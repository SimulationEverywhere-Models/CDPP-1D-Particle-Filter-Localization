/*******************************************************************
*
*  Auto Generated File
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  This registration file is used to describe the atomic models that can be used to compose coupled models.
*
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico
#include "ggad.h"       // DEVS-Graphs interpreter
#include "heightAndSpeedAdjustmentType.h"        // class heightAndSpeedAdjustmentType
#include "positionCalculationType.h"	// class positionCalculationType
#include "laserSensorType.h"	// class laserSensorType
#include "particleFilterType.h"	// class particleFilterType
#include "comparatorType.h"	// class comparatorType

void MainSimulator::registerNewAtomics()
{
	// Register Built-in models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Ggad>() , "Ggad" ) ; // DEVS-GRAPHS interpreter

	// Register custom models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<heightAndSpeedAdjustmentType>(), "heightAndSpeedAdjustmentType" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<positionCalculationType>() , "positionCalculationType" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<laserSensorType>() , "laserSensorType" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<particleFilterType>() , "particleFilterType" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<comparatorType>() , "comparatorType" ) ;
}

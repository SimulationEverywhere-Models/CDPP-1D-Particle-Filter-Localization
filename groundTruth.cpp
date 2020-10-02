#include "groundTruth.h"
#include <math.h>
#include <stdlib.h>

double getGroundHeight(double position)
{
	double groundHeight;
	groundHeight = ((1-(position)/30)*sin(position)+((position)/30)*sin(1.5*(position)));
	groundHeight = -fabs(groundHeight);
	return groundHeight;
}

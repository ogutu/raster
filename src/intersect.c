#include    <R.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include "Rmath.h"


/*
By Paul Bourke
http://paulbourke.net/geometry/lineline2d/
Determine the intersection point of two line segments
Return FALSE if the lines don't intersect
*/
int intersectSegments( double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, 
						double *x, double *y, double *xa, double *ya) {
   double mua,mub;
   double denom,numera,numerb;
   double EPS = 0.000000001;

    *x = 0.0;
    *y = 0;
    *xa = 0;
    *ya = 0;
 
   denom  = (y4-y3) * (x2-x1) - (x4-x3) * (y2-y1);
   numera = (x4-x3) * (y1-y3) - (y4-y3) * (x1-x3);
   numerb = (x2-x1) * (y1-y3) - (y2-y1) * (x1-x3);

   /* Are the line coincident? */
   if (fabs(numera) < EPS && fabs(numerb) < EPS && fabs(denom) < EPS) {
	 // changes by RH
	 // return two points if lines coincide.
		double xmin;
		double ymin;
		double xmax;
		double ymax;
		if (x1 > x3) {
			xmin = x1;
			ymin = y1;
		} else {
			xmin = x3;
			ymin = y3;
		}
		if (x2 > x4) {
			xmax = x2;
			ymax = y2;
		} else {
			xmax = x4;
			ymax = y4;
		}
		*x = xmin;
		*xa = xmax;
		*y = ymin;
		*ya = ymax;
		return(2);
   }

   /* Are the line parallel */
   if (fabs(denom) < EPS) {
      return(0);
   }

   /* Is the intersection along the the segments */
   mua = numera / denom;
   mub = numerb / denom;
   if (mua < 0 || mua > 1 || mub < 0 || mub > 1) {
      return(0);
   }
   *x = x1 + mua * (x2 - x1);
   *y = y1 + mua * (y2 - y1);
   return(1);
}


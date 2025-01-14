/**
 * @file stats.h
 * @description declaration of Stats class used for fast computation of
 *              colour information from rectangular image regions
 * 
 *              THIS FILE WILL NOT BE SUBMITTED
 */

#ifndef _STATS_H_
#define _STATS_H_

#include "util/PNG.h"
#include "util/HSLAPixel.h"
#include <utility>
#include <cmath>
#include <vector>

using namespace std;
using namespace util;

#define PI 3.14159265

class Stats {

    private:
        /**
         *  SOME INFORMATION ABOUT AVERAGING MULTIPLE HUE VALUES:
         *  The hue value of a pixel is typically an angular measure, reported in 
         *  degrees: h \in [0,360), where h=0, and h=360 are both red. Note that
         *  the interval is open at 360 (i.e. a hue of 360 will be stored as h=0).
         *  In order to implement averages and distances, we need to translate the
         *  angular measures into (x,y) in the cartesian coordinate system. We just
         *  use x=cos(h), and y=sin(h), though you'll have to dig through your
         *  trig memories, because the stl versions of the trig functions require
         *  radian arguments, instead of degrees. Also note that to convert back
         *  from the cartesian coordinates to hue, you should use c++ function
         *  atan2.
         */

        /** sumHueX[i][j] contains the cumulative sum of the X component of the 
         *  hue, as described above. The sum is taken over all pixels in the 
         *  range (0,0) to (i,j). (you may decide to use (0,0) to (j,i), if you
         *  prefer.) This table can be built in time proportional to the size of
         *  the table itself (constant per cell), and it's up to you to figure out
         *  how to do it.
         */
	    vector< vector< double >> sumHueX;

        /** sumHueY[i][j] contains the cumulative sum of the Y component of the 
         *  hue, as described above. The sum is taken over all pixels in the 
         *  range (0,0) to (i,j). (you may decide to use (0,0) to (j,i), if you
         *  prefer.) This table can be built in time proportional to the size of
         *  the table itself (constant per cell), and it's up to you to figure out
         *  how to do it.
         */
	    vector< vector< double >> sumHueY;

        /** sumSat[i][j] contains the cumulative sum of the saturation component 
         *  of the pixel (the s in HSLA). The sum is taken over all pixels in the 
         *  range (0,0) to (i,j). (you may decide to use (0,0) to (j,i), if you
         *  prefer.) This table can be built in time proportional to the size of
         *  the table itself (constant per cell), and it's up to you to figure out
         *  how to do it.
         */
	    vector< vector< double >> sumSat;

        /** sumLum[i][j] contains the cumulative sum of the luminance component 
         *  of the pixel (the l in HSLA). The sum is taken over all pixels in the 
         *  range (0,0) to (i,j). (you may decide to use (0,0) to (j,i), if you
         *  prefer.) This table can be built in time proportional to the size of
         *  the table itself (constant per cell), and it's up to you to figure out
         *  how to do it.
         */
	    vector< vector< double >> sumLum;

        /** hist[i][j][k]: hist[i][j] contains a histogram of the hue values 
         *   0 to 360 into bins of width 10, over the pixels in the rectangle
         *   defined by (0,0) through (i,j). Thus, hist[i][j][k] contains
         *   the number of pixels whose hue value h, is: k*10 <= h < (k+1)*10
         *   over the rectangle. 
         */
        vector<vector<vector<unsigned int>>> hist;


    public:
        
        /**
         * Parameterized constructor
	     * Initialize the private vectors so that, for each color channel, 
	     * (x,y) is the cumulative sum of the the color values from (0,0)
	     * to (x,y). 
         * Note that the hue (h) value of each pixel is represented by
         * its cartesian coordinates: X = cos(h) and Y = sin(h). 
         * This is done to simplify distance and average computation.
         */
	    Stats(const PNG& im); 

	    /**
         * Given a rectangle, return the average color value over the rectangle.
	     * Each color component of the pixel is the average value of that 
	     * component over the rectangle.
	     * @param ul is (x,y) of the upper left corner of the rectangle 
	     * @param lr is (x,y) of the lower right corner of the rectangle
         * 
         * The average hue is computed from the cumulative X and Y values
         * as the arctan(y/x), adjusted to be in the range 0 (inclusive)
         * to 360 (non-inclusive).
         * You should research the functions for computing arctan in c++.
         * Finally, the alpha component of the average should be set to 1.0
         */
	    HSLAPixel GetAvg(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);

	    /**
         * Given a rectangle, return the number of pixels in the rectangle
	     * @param ul is (x,y) of the upper left corner of the rectangle 
	     * @param lr is (x,y) of the lower right corner of the rectangle
         */
	    long RectArea(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);

        /**
         * Given a rectangle, return the total entropy over that rectangle.
	     * @param ul is (x,y) of the upper left corner of the rectangle 
	     * @param lr is (x,y) of the lower right corner of the rectangle
         * 
         * Entropy is computed from the hist table, as 
         * follows: E = -Sum(p_i log(p_i)), where p_i is the fraction of
         * pixels in bin i, and the sum is taken over all the bins. 
         * bins holding no pixels should not be included in the sum.
         */
        double Entropy(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);

    private:
        /**
         * Add your own private member attributes or functions into stats_private.h
         */
        #include "stats_private.h"

};

#endif

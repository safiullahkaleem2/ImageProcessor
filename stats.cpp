/**
 * @file stats.cpp
 * @description implementation of Stats class used for fast computation of
 *              colour information from rectangular image regions
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

#include "stats.h"

#define NUMBINS 36 // number of histogram bins

Stats::Stats(const PNG &im)
{
    // complete your implementation below
    height = im.height();
    width = im.width();
    firstFourResizer();
    histResizer();

    double prevSumHueX = 0;
    double prevSumHueY = 0;
    double prevSumSat = 0;
    double prevSumLum = 0;


    for (unsigned int row = 0; row < height; row++) {
    for (unsigned int col = 0; col < width; col++) {
        HSLAPixel *pixel = im.getPixel(col, row);
        double hue = pixel->h;
        double lum = pixel->l;
        double sat = pixel->s;
       double hueX = cos(hue * PI / 180);
        double hueY = sin(hue * PI / 180);
        sumHueX[row][col] = prevSumHueX + hueX;
         sumHueY[row][col] = prevSumHueY + hueY;
        sumSat[row][col] = prevSumSat + sat;
         sumLum[row][col] = prevSumLum + lum;
        prevSumHueX += hueX;
        prevSumHueY += hueY;
        prevSumSat += sat;
        prevSumLum += lum;
    }
}


for (unsigned int row = 0; row < height; row++) {
    for (unsigned int col = 0; col < width; col++) {
        if (row == 0 && col == 0) {
        HSLAPixel *pixel = im.getPixel(col, row);
        double hue = pixel->h;
        unsigned int binNumber = static_cast<unsigned int>(floor(hue / 10));
        hist[row][col][binNumber] += 1;
        }

        else if (row == 0) {
        HSLAPixel *pixel = im.getPixel(col, row);
        double hue = pixel->h;
            unsigned int binNumber = static_cast<unsigned int>(floor(hue / 10));
        hist[row][col] = hist[row][col - 1];
        hist[row][col][binNumber] += 1;
        }

        else if (col == 0) {
        HSLAPixel *pixel = im.getPixel(col, row);
        double hue = pixel->h;
            unsigned int binNumber = static_cast<unsigned int>(floor(hue / 10));
        hist[row][col] = hist[row - 1][col];
        hist[row][col][binNumber] += 1;
        }

        else {
        HSLAPixel *pixel = im.getPixel(col, row);
        double hue = pixel->h;
           unsigned int binNumber = static_cast<unsigned int>(floor(hue / 10));

        hist[row][col] =  operation(hist[row - 1][col],hist[row][col - 1],hist[row - 1][col - 1]);
        hist[row][col][binNumber] += 1;
        }
    }

    }

    
}

void Stats::histResizer()
{
    hist.resize(height);
    for (unsigned int i = 0; i < height; i++)
    {
        hist[i].resize(width);
        for (unsigned int j = 0; j < width; j++) {
        vector<unsigned int> newVector(36, 0);
              hist[i][j] = newVector;
            
        }
    }
}


void Stats::firstFourResizer()
{
    sumHueX.resize(height);
    sumHueY.resize(height);
    sumSat.resize(height);
    sumLum.resize(height);

    for (unsigned int row = 0; row < height; row++)
    {
        sumHueX[row].resize(width);
        sumHueY[row].resize(width);
        sumSat[row].resize(width);
        sumLum[row].resize(width); 
    }
}

long Stats::RectArea(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{
    // replace the stub below with your completed implementation
    unsigned int x1 = ul.first;
    unsigned int x2 = lr.first;
    unsigned int y1 = ul.second;
    unsigned int y2 = lr.second;
    
    return ((x2-x1) + 1) *((y2-y1) +1);
}

HSLAPixel Stats::GetAvg(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{   unsigned int x1 = ul.first;
    unsigned int x2 = lr.first;
    unsigned int y1 = ul.second;
    unsigned int y2 = lr.second;
    double cumHueX = 0;
    double cumHueY = 0;
    double cumSat = 0;
    double cumLum = 0;
    long area = RectArea(ul, lr);
    for(unsigned int i = 0; i <= y2 - y1; i++) {

        if (x1+i == 0 && y1+i ==0) {
        cumHueX = cumHueX + sumHueX[y1 + i][x2]; 
        cumHueY =  cumHueY + sumHueY[ y1 + i][x2];
        cumSat = cumSat + sumSat[y1 + i][x2]; 
        cumLum = cumLum + sumLum[y1 + i][x2]; 
        }

        else {
        cumHueX = cumHueX + sumHueX[y1 + i][x2] - sumHueX[prevfinderY(x1, y1 + i)][prevfinderX(x1)];
        cumHueY =  cumHueY + sumHueY[ y1 + i][x2] - sumHueY[prevfinderY(x1, y1 + i)][prevfinderX(x1)];
        cumSat = cumSat + sumSat[y1 + i][x2] - sumSat[prevfinderY(x1, y1 + i)][prevfinderX(x1)];
        cumLum = cumLum + sumLum[ y1 + i][x2] - sumLum[prevfinderY(x1, y1 + i)][prevfinderX(x1)];
        }
    }

    double hue = atan2(cumHueY, cumHueX) * 180/PI;
    if (hue < 0) {
      hue = 360 - (hue * (- 1));
    }
    double sat = static_cast<double>(cumSat) / area;
    double lum = static_cast<double>(cumLum) / area;
    double alpha = 1.0;
    return HSLAPixel(hue, sat, lum, alpha);
    }



double Stats::Entropy(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr)
{ 	    vector<unsigned int> distribution;
    unsigned int x1 = ul.first;
    unsigned int x2 = lr.first;
    unsigned int y1 = ul.second;
    unsigned int y2 = lr.second;
    vector<unsigned int> histogram = hist[y2][x2];
    double entropy = 0;
    long area = RectArea(ul,lr);
     
   	
    if ((x1 == 0 && y1 == 0)) {
    
        distribution = hist[y2][x2];
    for (unsigned int i = 0; i < 36; i++) {
    if (distribution[i] > 0 ) {
            entropy += ((double) distribution[i]/(double) area)
                                    * log2((double) distribution[i]/(double) area);
    }

    }


	      }
    else if (x1 == 0) 
    { 
    vector<unsigned int> newVector(36, 0);
    unsigned int upperx = x2;
    unsigned int uppery = y1 - 1;
    vector<unsigned int> upper = hist[uppery][upperx];
    distribution = operationEnthropy(histogram,newVector,upper,newVector);
    for (unsigned int i = 0; i < 36; i++) {
    if (distribution[i] > 0 ) {
            entropy += ((double) distribution[i]/(double) area)
                                    * log2((double) distribution[i]/(double) area);
    }

    }
    }

    else if (y1 == 0) 
    { 
    vector<unsigned int> newVector(36, 0);
     unsigned int leftx = x1 - 1;
     unsigned int lefty = y2;
    vector<unsigned int> left = hist[lefty][leftx];
    distribution = operationEnthropy(histogram,left,newVector,newVector);
    for (unsigned int i = 0; i < 36; i++) {
    if (distribution[i] > 0 ) {
            entropy += ((double) distribution[i]/(double) area)
                                    * log2((double) distribution[i]/(double) area);
    }

    }
    }
    else {
       
        unsigned int upperx = x2;
    unsigned int uppery = y1 - 1;
        unsigned int ulx = x1 - 1;
     unsigned int uly = y1 - 1;
      unsigned int leftx = x1 - 1;
     unsigned int lefty = y2;
 

    vector<unsigned int> left = hist[lefty][leftx];
    vector<unsigned int> upper = hist[uppery][upperx];
    vector<unsigned int> upperleft = hist[uly][ulx];
    distribution = operationEnthropy(histogram,left,upper,upperleft);
    for (unsigned int i = 0; i < 36; i++) {
    if (distribution[i] > 0 ) {
            entropy += ((double) distribution[i]/(double) area)
                                    * log2((double) distribution[i]/(double) area);
    }

    }
    }

if (entropy == 0)
{
    return entropy; 
}


    return -1 * entropy;
}

/**
 * Add your private Stats function implementations below
 */

unsigned int Stats:: prevfinderX(unsigned int x) {
    if (x == 0) {
        return width - 1;
    }

    return x - 1;

}
unsigned int Stats::prevfinderY(unsigned int x, unsigned int y) {
    if (x == 0) {
        return y - 1;
    }

    return y;


}

vector<unsigned int> Stats::operation(vector<unsigned int>& a1,vector<unsigned int>& a2, vector<unsigned int>& s1) {
vector<unsigned int> newVector(36, 0);
for (unsigned int i = 0; i < 36; i++) {
    newVector[i] = a1[i] + a2[i] - s1[i];

}
    return  newVector;
}


vector<int> Stats::caster(vector<unsigned int>& a1) {
vector<int> newVector(36, 0);
for (unsigned int i = 0; i < 36; i++) {
    newVector[i] = int(a1[i]);

}
    return  newVector;
}


vector<unsigned int> Stats::operationEnthropy(vector<unsigned int>& a1,vector<unsigned int>& s1, vector<unsigned int>& s2,vector<unsigned int>& a2) {
vector<unsigned int > newVector(36, 0);

for (unsigned int i = 0; i < 36; i++) {

    newVector[i] = a1[i] + a2[i] - s1[i] - s2[i];

}
    return  newVector;
}





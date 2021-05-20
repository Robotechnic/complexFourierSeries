#ifndef FOURIERFUNCTION_H
#define FOURIERFUNCTION_H

#include <vector>
#include "ofVec2f.h"
#include "ofVec3f.h"
#include "of3dUtils.h"
#include "ofGraphics.h"
#include "ofLog.h"
#include "ofAppRunner.h"
#include "ofMath.h"

using namespace std;

class fourierFunction
{
public:
    fourierFunction();
    fourierFunction(int precision, float step=1);

    void closeFunction();
    void calculateCoefs();

    void drawPoint();
    void drawVectors();
    void evolve();

    void clear();

    void addPoint(ofVec2f point);
    void inline addPoint(float x, float y){this->addPoint({x,y});}

    float step;

private:
    vector <ofVec2f>points;
    void addPointToPoint(ofVec2f start,ofVec2f stop);

    vector <ofVec2f>rotationsCoef;
    ofVec2f getNvalue(int n);

    bool processed;

    int precision;

    vector <ofVec2f>functionPoints;
    float ft;
    bool firstStep;
    int animationLenght;
};

#endif // FOURIERFUNCTION_H

#include "fourierfunction.h"

fourierFunction::fourierFunction() :
    precision(10),
    processed(false),
    step(1),
    firstStep(true),
    animationLenght(0),
    ft(0)
{

}

fourierFunction::fourierFunction(int precision, float step) :
    precision(precision),
    processed(false),
    step(step),
    firstStep(true),
    animationLenght(0),
    ft(0)
{

}

void fourierFunction::closeFunction(){
    this->addPointToPoint(this->points.at(this->points.size()-1),this->points.at(0));

    animationLenght = this->points.size()*0.9;
}

void fourierFunction::addPoint(ofVec2f point){
    if (!processed){
        int size{static_cast<int>(this->points.size())};
        if (size > 0){
            float distance{this->points.at(size-1).distance(point)};
            if (distance > 1){
                //calculate all points between the two points
                this->addPointToPoint(this->points.at(size-1),point);
            } else if (distance == 0){
                return;
            }
        }
        this->points.push_back(point);
    }
}

void fourierFunction::addPointToPoint(ofVec2f start, ofVec2f end){
    ofVec2f director = end - start;
    director.normalize();
    while (end.distance(start) > 1){
        start += director;
        this->points.push_back(start);
    }
}

void fourierFunction::calculateCoefs(){
    processed = true;
    ofVec2f p,expCoef;
    ofVec2f integral;
    this->rotationsCoef.clear();
    for (int n = -this->precision; n<=this->precision; n++){
        integral = ofVec2f{0,0};
        for (int t = 0; t<this->points.size(); t++){
            p = this->points.at(t);
            expCoef = ofVec2f(cos(-2*PI*n*t/this->points.size()),sin(-2*PI*n*t/this->points.size())); //e^{-n*2*pi*t*i}
            integral += ofVec2f(
                                   (p.x*expCoef.x-p.y*expCoef.y),
                                   (p.x*expCoef.y+p.y*expCoef.x)
                               );
        }


        this->rotationsCoef.push_back(integral);
    }
}


void fourierFunction::drawPoint(){
    if (this->processed){
       ofSetColor(255);

       int start = 0;
       if (!firstStep){
           start = -animationLenght+ft;
       }

       ofLog()<<start<<" "<<ft;

       for (int i = start; i<ft; i++){
           ofDrawRectangle(this->points.at((i < 0 ? this->points.size() + i : i)) ,1,1);
       }
    } else {
        ofSetColor(255);
        for (ofVec2f p : this->points){
            ofDrawRectangle(p ,1,1);
        }
    }
}

ofVec2f fourierFunction::getNvalue(int n) {
    if (!this->processed)
        return ofVec2f{0,0};


    n = n>this->precision ? this->precision : n;
    n = n<-this->precision ? -this->precision : n;

    ofVec2f coef = this->rotationsCoef.at(n+this->precision);
    ofVec2f expCoef = {static_cast<float>(cos(2*PI*n*this->ft/this->points.size())),
                       static_cast<float>(sin(2*PI*n*this->ft/this->points.size()))};


    return ofVec2f{
                     static_cast<float>(coef.x*expCoef.x-coef.y*expCoef.y)/this->points.size(),
                     static_cast<float>(coef.x*expCoef.y+coef.y*expCoef.x)/this->points.size()
                 };
}

void fourierFunction::drawVectors(){
    if (!this->processed)
        return;

    ofVec2f pos;
    ofVec2f lastPos;
    lastPos = this->getNvalue(0); //with this line, the vectors always stay at center
    pos += lastPos;

    ofSetColor(100,255,200);
    for (int n = 1; n<=this->precision; n++){
        lastPos = pos;
        pos += this->getNvalue(n);
        ofDrawArrow(ofVec3f(lastPos.x,lastPos.y,1),ofVec3f(pos.x,pos.y,1),3);
        lastPos = pos;
        pos += this->getNvalue(-n);
        ofDrawArrow(ofVec3f(lastPos.x,lastPos.y,1),ofVec3f(pos.x,pos.y,1),3);
    }

    ofSetColor(0,255,0);
    ofDrawCircle(pos,2);
}

void fourierFunction::evolve() {
    if (this->processed){
        ft = ft>=this->points.size()-1 ? 0 : ft+1;
        if (this->firstStep && ft > animationLenght){
            firstStep = false;
        }
    }
}


void fourierFunction::clear(){
    this->points.clear();
    this->rotationsCoef.clear();
    this->processed = false;
    this->firstStep = true;
}

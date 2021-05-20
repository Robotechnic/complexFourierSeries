#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    f = fourierFunction{20};
    //ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
   f.evolve();
}

//--------------------------------------------------------------
void ofApp::draw(){
    f.drawPoint();
    f.drawVectors();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'p'){
        f.closeFunction();
        f.calculateCoefs();
    }
    if (key == 'e'){
        f.evolve();
    }



    if (key == 'c'){
        f.clear();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    f.addPoint(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    f.addPoint(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

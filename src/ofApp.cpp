#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    f = fourierFunction{20};

    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);

    gui->addHeader("Settings");
    gui->addFRM();
    gui->addButton("Clear (c)");
    gui->addSlider("Scale",1,100)->bind(f.scale);
    ofxDatGuiSlider *s = gui->addSlider("Speed",0.01,1);
    s->bind(f.speed);
    s->setValue(1);

    gui->onButtonEvent([&](ofxDatGuiButtonEvent e){
        if (e.target->is("Clear (c)")){
            f.clear();
        }
    });

    gui->setAutoDraw(false);

    ofxDatGuiLog::quiet();
}

//--------------------------------------------------------------
void ofApp::update(){
   f.evolve();
   gui->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    if (f.getProcessed() && f.scale>1){
        ofTranslate(ofVec2f{static_cast<float>(ofGetWidth()/2),static_cast<float>(ofGetHeight()/2)}-f.getCurrentPoint()*f.scale);
        ofScale(f.scale);
    }

    f.drawPoint();
    f.drawVectors();
    ofPopMatrix();
    gui->draw();
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

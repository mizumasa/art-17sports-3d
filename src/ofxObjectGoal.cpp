#include "ofxObjectGoal.h"

//--------------------------------------------------------------
ofxObjectGoal::ofxObjectGoal(){
    model.loadModel("Basketball_Hoop.3DS");
}

//--------------------------------------------------------------
void ofxObjectGoal::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    
    /*ofTranslate(vf_Pos);
    ofRotateZ(-f_AnglePan);
    ofRotateX(f_AngleTilt);
     */
    //ofDrawCircle(0,0,0,40);
    ofTranslate(0,65*1.99, -28*1.99);
    ofScale(0.45955,0.45955,0.45955);

    ofRotateX(-90);
    ofRotateY(-180);
    ofScale(0.45955,0.45955,0.45955);
    model.drawFaces();
    ofPopStyle();
    ofPopMatrix();
}


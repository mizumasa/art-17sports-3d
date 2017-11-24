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
    ofTranslate(0, 8, 90);
    ofTranslate(0, GOAL_Y_OFFSET, 0);
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, 6, 0);
    ofScale(0.45955,0.45955,0.45955);
    ofScale(0.5,0.5,0.5);
    ofRotateX(-90);
    ofSetColor(100, 100, 100);
    ofDrawCylinder(0, 200, -3, 20, GOAL_HEIGHT*3);
    ofPopStyle();
    ofPopMatrix();
    
    ofScale(0.45955,0.45955,0.45955);
    ofScale(0.5,0.5,0.5);
    ofRotateX(-90);
    ofRotateY(-180);
    //ofScale(0.45955,0.45955,0.45955);
    model.drawFaces();
    ofPopStyle();
    ofPopMatrix();
}


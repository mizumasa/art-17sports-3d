#include "ofxObjectGoal.h"

//--------------------------------------------------------------
ofxObjectGoal::ofxObjectGoal(){
    model.loadModel("Basketball_Hoop.3DS");
    goalPanel.load("goalPanel.png");
}

void ofxObjectGoal::panelDraw(){
    ofPushMatrix();
    ofTranslate(0,147,26);
    ofScale(6.0/100,6.0/100,6.0/100);
    ofRotateX(90);
    goalPanel.draw(-goalPanel.getWidth()/2,-goalPanel.getHeight()/2 , goalPanel.getWidth(), goalPanel.getHeight());
    ofPopMatrix();
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
    ofTranslate(0, 8, 90-89.47);
    ofTranslate(0, GOAL_Y_OFFSET, 0);
    ofScale(0.45955,0.45955,0.45955);
    ofScale(0.4,0.4,0.4);
    ofRotateX(-90);
    ofRotateY(-180);
    //ofScale(0.45955,0.45955,0.45955);
    model.drawFaces();
    ofPopStyle();
    ofPopMatrix();
}


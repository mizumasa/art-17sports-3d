#include "ofxObjectBall.h"

//--------------------------------------------------------------
ofxObjectBall::ofxObjectBall(){
    model.loadModel("Basketball_Ball.3DS");
    vf_Pos = ofVec3f(0, 0, 30);
    vf_Speed = ofVec3f(0, 0, 0);
    vf_RotateSpeed = ofVec3f(2, 14, 0);
    vf_Rotate = ofVec3f(0, 0, 0);
    vf_Gravity = ofVec3f(0, 0, -0.1);
}

//--------------------------------------------------------------
void ofxObjectBall::update(){
    vf_Speed += vf_Gravity;
    vf_Rotate += vf_RotateSpeed;
    vf_Pos += vf_Speed;
}

void ofxObjectBall::setSpeed(ofVec3f _vf_Speed){
    vf_Speed = _vf_Speed;
}

//--------------------------------------------------------------
void ofxObjectBall::draw(float f,float f2){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofTranslate(vf_Pos);
    ofScale(0.02,0.02,0.02);
    ofRotateX(vf_Rotate[0]);
    ofRotateY(vf_Rotate[1]);
    ofRotateZ(vf_Rotate[2]);
    ofNoFill();
    ofDrawSphere(0, 0, 0, 240);
    ofTranslate(ofVec3f(0,250,0));
    model.drawFaces();
    ofPopStyle();
    ofPopMatrix();
}


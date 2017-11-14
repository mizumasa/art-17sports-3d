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
    vf_Speed -= vf_Speed/80.0;
    vf_Rotate += vf_RotateSpeed;
    vf_Pos += vf_Speed;
    if(vf_Pos[2]<GROUND_LEVEL){
        vf_Pos[2] = GROUND_LEVEL;
    }
    if(vf_Pos[1]>COURT_HEIGHT_HALF){
        vf_Speed[1] = -vf_Speed[1];
    }
}

void ofxObjectBall::setSpeed(ofVec3f _vf_Speed){
    vf_Speed = _vf_Speed;
}

void ofxObjectBall::throwTo(ofVec3f _vf_Pos, float _speed){
    vf_Speed = (_vf_Pos - vf_Pos);
    vf_Speed = _speed * vf_Speed / vf_Speed.length();
}


//--------------------------------------------------------------
void ofxObjectBall::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofTranslate(vf_Pos);
    ofScale(0.02,0.02,0.02);
    ofRotateX(vf_Rotate[0]);
    ofRotateY(vf_Rotate[1]);
    ofRotateZ(vf_Rotate[2]);
    ofNoFill();
    //ofDrawSphere(0, 0, 0, 240);
    ofTranslate(ofVec3f(0,250,0));
    model.drawFaces();
    ofPopStyle();
    ofPopMatrix();
}


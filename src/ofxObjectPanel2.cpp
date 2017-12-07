#include "ofxObjectPanel2.h"

//--------------------------------------------------------------
ofxObjectPanel2::ofxObjectPanel2(){
    vf_Pos = ofVec3f(0, 0, 0);
    vf_Speed = ofVec3f(0, 0, 0);
    //vf_RotateSpeed = ofVec3f(2, 14, 0);
    vf_RotateSpeed = ofVec3f(0, 0, 0);
    vf_Rotate = ofVec3f(0, 0, 0);
    vf_Gravity = ofVec3f(0, 0, 0);
    t_Count = 0;
    b_Pose = true;
    b_Left = false;
}
//--------------------------------------------------------------
void ofxObjectPanel2::setLeft(bool b_){
    b_Left = b_;
}

//--------------------------------------------------------------
void ofxObjectPanel2::start(){
    b_Pose = false;
    vf_RotateSpeed = ofVec3f(ofRandom(3,4), ofRandom(0,13), ofRandom(0,13));
    vf_Gravity = ofVec3f(0, 0.5, 0);
    vf_Speed = ofVec3f(ofRandom(-10.0, 10.0), ofRandom(0,10.0), 0);
}
//--------------------------------------------------------------
void ofxObjectPanel2::update(){
    t_Count += 1;
    if(t_Count > FLY_TIME){
        //b_Pose = true;
    }else{
        if(b_Left){
            //nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            //ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }else{
            //nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            //ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }
    }
    if(!b_Pose){
        vf_Speed += vf_Gravity;
        vf_Speed -= vf_Speed/80.0;
        vf_Rotate += vf_RotateSpeed;
        vf_Pos += vf_Speed;
    }
}

void ofxObjectPanel2::setStartPos(ofVec2f _startPos){
    startPos = _startPos;
}

void ofxObjectPanel2::noGravity(){
    vf_Gravity = ofVec3f(0,0,0);
}
void ofxObjectPanel2::setGravity(float _gravity){
    vf_Gravity = ofVec3f(0,_gravity,0);
}


//--------------------------------------------------------------
void ofxObjectPanel2::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(int(color[0]), int(color[1]), int(color[2]));
    
    //ofTranslate(vf_Pos);
    //ofScale(ofGetWidth()/MACBOOKPRO_W, ofGetHeight()/MACBOOKPRO_H);
    ofTranslate(nowPos+vf_Pos);
    //ofTranslate(tCenter - t1);
    ofRotateX(vf_Rotate[0]);
    ofRotateY(vf_Rotate[1]);
    ofRotateZ(vf_Rotate[2]);
    //ofTranslate(t1 - tCenter);
    ofFill();
    //ofDrawTriangle( ofVec2f(0,0), t2-t1, t3-t1);
    ofPopStyle();
    ofPopMatrix();
}


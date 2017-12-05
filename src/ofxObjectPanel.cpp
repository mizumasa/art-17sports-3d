#include "ofxObjectPanel.h"

//--------------------------------------------------------------
ofxObjectPanel::ofxObjectPanel(){
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
void ofxObjectPanel::setLeft(bool b_){
    b_Left = b_;
}

//--------------------------------------------------------------
void ofxObjectPanel::start(){
    b_Pose = false;
    vf_RotateSpeed = ofVec3f(ofRandom(3,4), ofRandom(0,13), ofRandom(0,13));
    vf_Gravity = ofVec3f(0, 0.5, 0);
    vf_Speed = ofVec3f(ofRandom(-10.0, 10.0), ofRandom(0,10.0), 0);
}
//--------------------------------------------------------------
void ofxObjectPanel::update(){
    t_Count += 1;
    if(t_Count > FLY_TIME){
        //b_Pose = true;
    }else{
        if(b_Left){
            nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }else{
            nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }
    }
    if(!b_Pose){
        vf_Speed += vf_Gravity;
        vf_Speed -= vf_Speed/80.0;
        vf_Rotate += vf_RotateSpeed;
        vf_Pos += vf_Speed;
    }
}

void ofxObjectPanel::setStartPos(ofVec2f _startPos,ofVec2f _t1,ofVec2f _t2,ofVec2f _t3){
    startPos = _startPos;
    t1 = _t1;
    t2 = _t2;
    t3 = _t3;
    tCenter = (t1+t2+t3)/3;
}

void ofxObjectPanel::noGravity(){
    vf_Gravity = ofVec3f(0,0,0);
}
void ofxObjectPanel::setGravity(float _gravity){
    vf_Gravity = ofVec3f(0,_gravity,0);
}

/*

void ofxObjectPanel::releaseGoal(){
    if(b_GoalLoop){
        b_GoalLoop = false;
        vf_Speed = ofVec3f(
                           (cos((t_Count-f_SlowCountSum)/5.0)),
                           -sin((t_Count-f_SlowCountSum)/5.0),
                           0
                           );
        setGravity(0.2);
    }
}
void ofxObjectPanel::releaseOut(){
    if(b_GoalLoop){
        b_GoalLoop = false;
        vf_Speed = ofVec3f(
                           (-cos((t_Count-f_SlowCountSum)/5.0)),
                           sin((t_Count-f_SlowCountSum)/5.0),
                           0
                           );
        setGravity(0.2);
    }
}

void ofxObjectPanel::setSpeed(ofVec3f _vf_Speed){
    vf_Speed = _vf_Speed;
}

void ofxObjectPanel::throwTo(ofVec3f _vf_Pos, float _speed){
    vf_Speed = (_vf_Pos - vf_Pos);
    vf_Speed = _speed * vf_Speed / vf_Speed.length();
}

void ofxObjectPanel::setGoalLoop(){
    b_GoalLoop = true;
    f_SlowCount = 0;
    f_SlowCountSum = 0;
}

void ofxObjectPanel::startGoalLoopSlow(){
    f_SlowCount = 0.01;
}

void ofxObjectPanel::setPos(ofVec3f _vf_Pos, ofVec3f _vf_Rotate){
    vf_Pos = _vf_Pos;
    vf_Rotate = _vf_Rotate;
}

ofVec3f ofxObjectPanel::getPos(){
    return vf_Pos;
}

void ofxObjectPanel::togglePose(){
    b_Pose = !b_Pose;
}
void ofxObjectPanel::clearPose(){
    b_Pose = false;;
}

void ofxObjectPanel::startReplay(){
    i_ReplayCount = 1;
}
void ofxObjectPanel::startReverse(){
    i_ReverseCount = 1;
}
void ofxObjectPanel::clearHistory(){
    vv_RouteHistory.clear();
    i_ReplayCount = 0;
    i_ReverseCount = 0;
    i_NowHistoryPos = -1;
}

bool ofxObjectPanel::isReversePlaying(){
    return (i_ReverseCount > 0);
}

*/

//--------------------------------------------------------------
void ofxObjectPanel::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    //ofTranslate(vf_Pos);
    ofScale(ofGetWidth()/1280.0, ofGetHeight()/800.0);
    ofTranslate(nowPos+vf_Pos);
    ofTranslate(tCenter - t1);
    ofRotateX(vf_Rotate[0]);
    ofRotateY(vf_Rotate[1]);
    ofRotateZ(vf_Rotate[2]);
    ofTranslate(t1 - tCenter);
    ofFill();
    ofDrawTriangle( ofVec2f(0,0), t2-t1, t3-t1);
    ofPopStyle();
    ofPopMatrix();
}


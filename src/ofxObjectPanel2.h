/*
 *
 */
#pragma once

#ifndef __ofxObjectPanel2__
#define __ofxObjectPanel2__

#include "ofMain.h"
#include "common.h"


class ofxObjectPanel2{
public:
    ofxObjectPanel2();
    void start();
    void draw();
    void update();
    void setLeft(bool b_);
    void noGravity();
    void setStartPos(ofVec2f _startPos);
    void setGravity(float _gravity);
    uint64_t t_Count;
    
private:
    ofVec3f vf_Gravity;
    ofVec3f vf_Speed;
    ofVec3f vf_RotateSpeed;
    ofVec3f vf_Pos;
    ofVec3f vf_Rotate;

    bool b_Pose;
    bool b_Left;
    ofVec2f startPos;
    ofVec2f nowPos;
    ofVec3f color;
};

#endif

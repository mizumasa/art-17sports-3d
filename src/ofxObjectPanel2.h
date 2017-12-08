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
    bool getEnd();
    uint64_t t_Count;
    
private:
    ofVec3f vf_Gravity;
    ofVec3f vf_Speed;
    ofVec3f vf_RotateSpeed;
    ofVec3f vf_Pos;
    ofVec3f vf_Rotate;

    bool b_Pose;
    bool b_End;
    bool b_Left;
    int i_Size;
    ofVec2f startPos;
    ofVec2f nowPos;
    ofVec3f color;
};

class ofxObjectPanels2{
public:
    ofxObjectPanels2();
    void draw();
    void update();
    void noGravity();
    void setGravity(float _gravity);
    void add(ofVec2f _startPos,bool _left);
    uint64_t t_Count;
    
private:
    bool b_Pose;
    //bool b_Left;
    vector<ofxObjectPanel2> v_Panel;
};
#endif

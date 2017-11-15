/*
 *
 */
#pragma once

#ifndef __ofxObjectBall__
#define __ofxObjectBall__

#include "ofMain.h"
#include "common.h"

#include "ofxAssimpModelLoader.h"

class ofxObjectBall{
public:
    ofxObjectBall();
    void draw();
    void update();
    void setSpeed(ofVec3f _vf_Speed);
    void throwTo(ofVec3f _vf_Pos, float _speed);
    void setPos(ofVec3f _vf_Pos, ofVec3f _vf_Rotate);
    void noGravity();
    void setGoalLoop();
    void setGravity(float _gravity);

private:
    ofxAssimpModelLoader model;
    ofVec3f vf_Gravity;
    ofVec3f vf_Speed;
    ofVec3f vf_RotateSpeed;
    ofVec3f vf_Pos;
    ofVec3f vf_Rotate;
    bool b_GoalLoop;
    uint64_t t_Count;
};

#endif

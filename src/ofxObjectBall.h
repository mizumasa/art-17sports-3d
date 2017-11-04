/*
 *
 */
#pragma once

#ifndef __ofxObjectBall__
#define __ofxObjectBall__

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ofxObjectBall{
public:
    ofxObjectBall();
    void draw(float f,float f2);
    void update();
    void setSpeed(ofVec3f _vf_Speed);
private:
    ofxAssimpModelLoader model;
    ofVec3f vf_Gravity;
    ofVec3f vf_Speed;
    ofVec3f vf_RotateSpeed;
    ofVec3f vf_Pos;
    ofVec3f vf_Rotate;
};

#endif

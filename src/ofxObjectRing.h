/*
 *
 */
#pragma once

#ifndef __ofxObjectRing__
#define __ofxObjectRing__

#include "ofMain.h"
#include "common.h"

class ofxObjectRing{
public:
    ofxObjectRing(ofVec3f _vf_pos);
    void draw();
    void update();
    void setSpeed();
    bool isEnd();
    void setRotate(float _angle);

private:
    ofVec3f vf_Pos;
    int i_Count;
    bool b_Finished;
    float f_angle;
};

class ofxObjectRings{
public:
    ofxObjectRings();
    void draw();
    void update();
    void add(ofVec3f _vf_pos);
private:
    vector<ofxObjectRing> vf_Object;
};


#endif

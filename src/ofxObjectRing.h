/*
 *
 */
#pragma once

#ifndef __ofxObjectRing__
#define __ofxObjectRing__

#include "ofMain.h"
#include "common.h"
#include "ofxObjectParticle.h"

class ofxObjectRing{
public:
    ofxObjectRing(ofVec3f _vf_pos);
    void draw();
    bool update(float ballPosY);
    void setSpeed();
    bool b_Finished;
    bool isEnd();
    void setRotate(float _angle);
    ofxObjectRingParticle objectRingParticle;
    bool b_DrawParticle;

private:
    ofVec3f vf_Pos;
    int i_Count;
    float f_angle;
    ofImage imgRing;
};

class ofxObjectRings{
public:
    ofxObjectRings();
    void init();
    void draw();
    void update(float ballPosY);
    void add(ofVec3f _vf_pos);
private:
    int i_ParticleUseIdx;
    vector<ofxObjectRing> vf_Object;
};


#endif

/*
 *
 */
#pragma once

#ifndef __ofxObjectEffect__
#define __ofxObjectEffect__

#include "ofMain.h"
#include "common.h"



class ofxObjectEffect{
public:
    ofxObjectEffect(ofVec3f _vf_pos);
    void draw();
    void update();
    void setSpeed();
    bool isEnd();
private:
    ofVec3f vf_Pos;
    int i_Count;
    bool b_Finished;
};

class ofxObjectEffects{
public:
    ofxObjectEffects();
    void draw();
    void update();
    void add(ofVec3f _vf_pos);
private:
    vector<ofxObjectEffect> vf_Object;
};



class ofxObjectCircle: public ofxObjectEffect{
};

class ofxObjectCircles: public ofxObjectEffects{
};


#endif

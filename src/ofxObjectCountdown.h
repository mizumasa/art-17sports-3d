/*
 *
 */
#pragma once

#ifndef __ofxObjectCountdown__
#define __ofxObjectCountdown__

#include "ofMain.h"
#include "common.h"

class ofxObjectCountdown{
public:
    ofxObjectCountdown();
    void draw();
    void update();
    bool getEnd();
    uint64_t t_Count;
    ofImage image;
private:
    bool b_End;
};

class ofxObjectCountdowns{
public:
    ofxObjectCountdowns();
    void draw();
    void update();
    void start(int countnum);
private:
    vector<ofxObjectCountdown> v_Panel;
    vector<ofImage> v_Image;
    vector<vector<ofSoundPlayer>> vv_Sound;
    int i_power;
};
#endif

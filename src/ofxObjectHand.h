/*
 *
 */
#pragma once

#ifndef __ofxObjectHand__
#define __ofxObjectHand__

#include "ofMain.h"
#include "common.h"

class ofxObjectHands{
public:
    ofxObjectHands();
    void play(int mode);
    void update();
    void draw();
private:
    uint64_t t_Count;
    int i_mode;
    vector<vector<ofImage>> vv_image;
};

#endif

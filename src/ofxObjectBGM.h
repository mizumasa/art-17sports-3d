/*
 *
 */
#pragma once

#ifndef __ofxObjectBGM__
#define __ofxObjectBGM__

#include "ofMain.h"
#include "common.h"

class ofxObjectBGM{
public:
    ofxObjectBGM();
    void play();
    void update();
    void setFo();
    void setDown();
    void setUp();
    uint64_t t_Count;
    ofSoundPlayer bgm;
private:
    int i_FoCount;
    int i_DownCount;
    int i_UpCount;
};

#endif

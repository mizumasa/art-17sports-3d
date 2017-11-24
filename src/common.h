#pragma once

#ifndef __ofxCommon__
#define __ofxCommon__

#include "ofMain.h"

#define GROUND_LEVEL -55
#define COURT_WIDTH_HALF 86
#define COURT_HEIGHT_HALF 142
#define GOAL_HEIGHT 130
//#define GOAL_Y_OFFSET 20
#define GOAL_Y_OFFSET 10

#define PORT 12345

#define OPENPOSE_RESIZE_RATE 0.1
#define OPENPOSE_CAP_HEIGHT 720
#define OPENPOSE_CAP_WIDTH 1280

enum ACT_MODE
{
    ACT_MODE_MOVIE = 0,
    ACT_MODE_CAPTURE = 1,
    ACT_MODE_CG = 2,
};

class ofxScheduleSeg{
public:
    ofxScheduleSeg();
    ACT_MODE actMode;
    int i_MovieId;
    string s_Name;
    ofVideoPlayer video;
private:
};

ofxScheduleSeg::ofxScheduleSeg(){
    s_Name = "none";
    i_MovieId = 0;
}

#endif

/*
 *
*/
#pragma once

#ifndef __ofxTimeLine__
#define __ofxTimeLine__

#include "ofMain.h"

#define SCENE1_START 0
#define SCENE2_START 10
#define COUNT_2_SEC 0.8
#define COUNT_3_SEC 0.7
#define COUNT_4_SEC 0.6
#define COUNT_5_SEC 0.5
#define COUNT_6_SEC 0.4
#define COUNT_7_SEC 0.4

#define TIMELINE_SPEED 1
#define STEP_NUM 35
#define ACT_ID_NUM 11

enum ACT_ID{
    AID_INIT = 0,
    AID_COUNT_1,
    AID_CHANGE_TO_THROW_1,
    AID_COUNT_2,
    AID_CHANGE_TO_THROW_2,
};

class ofxTimeLine : public ofBaseApp{
public:
    ofxTimeLine();
    void setup();
    void update(float pos);
    void draw();
    void clear();
    bool getState(int actId);
    int getParam(int actId);
    
private:
    vector<ofVec2f> vvf_TimeLineTime;
    vector<int> vi_TimeLineActId;
    vector<int> vi_TimeLineParam;
    vector<bool> vb_TimeLineUsedFlag;
    
    vector<bool> vb_ActState;
    vector<bool> vb_ActOnceFlag;
    vector<int> vb_ActParam;
};

#endif

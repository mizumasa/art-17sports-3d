/*
 *
*/
#pragma once

#ifndef __ofxTimeLine__
#define __ofxTimeLine__

#include "ofMain.h"

#define TIMELINE_SPEED 1
#define STEP_NUM 29
#define ACT_ID_NUM 12

enum ACT_ID{
    AID_INIT = 0,
    AID_CHANGE_ANGLE,
    AID_MOVE_ANGLE,
    AID_MOVE_HUMAN,
    AID_HUMAN_ZOOM_IN,
    AID_FADEOUT,//5
    AID_CHANGE_SCENE_TO_CHROME,
    AID_FADEIN,
    AID_CHANGE_SITE,
    AID_SCROLL,
    AID_HUMAN_ZOOM_OUT,//10
    AID_LOOP_BACK,
    AID_CHANGE_SCENE_TO_WORLD,
    AID_MOVE_TO_NEWFACE,
    AID_SITE_START,
    AID_NEWFACE_CAME,//15
    AID_MOVE_HUMAN_DUMMY,
    AID_LOGO_OFF,
    AID_LOGO_ON,
    AID_ROLLCAM_IN,
    AID_ROLLCAM_OUT,
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

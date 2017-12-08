/*
 *
 */
#pragma once

#ifndef __ofxObjectPanel__
#define __ofxObjectPanel__

#include "ofMain.h"
#include "common.h"


#define MACBOOKPRO_W 1280.0
#define MACBOOKPRO_H 800.0


class ofxObjectPanel{
public:
    ofxObjectPanel();
    void start();
    void draw();
    void update();
    void setLeft(bool b_);
    //void setSpeed(ofVec3f _vf_Speed);
    //void throwTo(ofVec3f _vf_Pos, float _speed);
    //void releaseGoal();
    //void releaseOut();

    //void setPos(ofVec3f _vf_Pos, ofVec3f _vf_Rotate);
    //ofVec3f getPos();
    void noGravity();
    void setStartPos(ofVec2f _startPos,ofVec2f _t1,ofVec2f _t2,ofVec2f _t3);
    //void setGoalLoop();
    //void startGoalLoopSlow();
    void setGravity(float _gravity);
    uint64_t t_Count;

    //void togglePose();
    //void clearPose();
    //void startReplay();
    //void startReverse();
    //void clearHistory();
    //bool isReversePlaying();

private:
    ofVec3f vf_Gravity;
    ofVec3f vf_Speed;
    ofVec3f vf_RotateSpeed;
    ofVec3f vf_Pos;
    ofVec3f vf_Rotate;
    //bool b_GoalLoop;
    //float f_SlowCount;
    //float f_SlowCountSum;
    
    //int i_ReplayCount;
    //int i_ReverseCount;
    //vector<ofVec3f> vv_RouteHistory;
    //int i_NowHistoryPos;
    bool b_Pose;
    bool b_Left;
    ofVec2f startPos, t1, t2, t3;
    ofVec2f tCenter;
    ofVec2f nowPos;
    ofVec3f color;
};


class ofxObjectPanelFrame{
public:
    ofxObjectPanelFrame();
    void start();
    void draw();
    void update();
    void noGravity();
    void setPoint(ofVec2f _pos);
    void setGravity(float _gravity);
    uint64_t t_Count;
    
private:
    ofVec3f vf_Gravity;
    ofVec3f vf_Speed;
    ofVec3f vf_RotateSpeed;
    ofVec3f vf_Pos;
    ofVec3f vf_Rotate;
    bool b_Pose;
    bool b_Left;
    vector<ofVec2f> vf_Points;
    ofVec2f tCenter;
    ofVec2f nowPos;
    ofVec3f color;
};

class ofxObjectFrame{
public:
    ofxObjectFrame();
    void draw();
    void update();
    void noGravity();
    void setGravity(float _gravity);
    void setPoints();
    uint64_t t_Count;
    
private:
    bool b_Pose;
    bool b_Left;
    vector<ofxObjectPanelFrame> v_Frame;
};



#endif

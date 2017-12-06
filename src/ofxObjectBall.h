/*
 *
 */
#pragma once

#ifndef __ofxObjectBall__
#define __ofxObjectBall__

#include "ofMain.h"
#include "common.h"

#include "ofxAssimpModelLoader.h"

//#define GOAL_LOOP_RADIUS  (16.9/2)
#define GOAL_LOOP_RADIUS  7.8
#define PATH_SAVE_NUM 200

class ofxObjectBall{
public:
    ofxObjectBall();
    void draw();
    void update();
    void setSpeed(ofVec3f _vf_Speed);
    void throwTo(ofVec3f _vf_Pos, float _speed);
    void releaseGoal();
    void releaseOut();

    void setPos(ofVec3f _vf_Pos, ofVec3f _vf_Rotate);
    ofVec3f getPos();
    void noGravity();
    void setGoalLoop();
    void setNoResistance();
    void startGoalLoopSlow();
    void setGravity(float _gravity);
    uint64_t t_Count;

    void togglePose();
    void clearPose();
    void startReplay();
    void startReverse();
    void clearHistory();
    bool isReversePlaying();
    ofVec3f vf_Speed;
    bool b_Slow;
    ofVec3f vf_SlowShift;

private:
    ofxAssimpModelLoader model;
    ofVec3f vf_Gravity;
    ofVec3f vf_RotateSpeed;
    ofVec3f vf_Pos;
    ofVec3f vf_Rotate;
    bool b_GoalLoop;
    float f_SlowCount;
    float f_SlowCountSum;
    
    int i_ReplayCount;
    int i_ReverseCount;
    vector<ofVec3f> vv_RouteHistory;
    int i_NowHistoryPos;
    bool b_Pose;
    bool b_NoResistance;
};

#endif

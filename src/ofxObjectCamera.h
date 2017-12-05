/*
 *
 */
#pragma once

#ifndef __ofxObjectCamera__
#define __ofxObjectCamera__

#include "ofMain.h"

#define MOVE_RADIUS_MIN 100
#define MOVE_RADIUS_MAX 150
#define MOVE_RADIUS_MIN2 250
#define MOVE_RADIUS_MAX2 350
#define MOVE_CUT_COUNT 120

class ofxObjectCamera :public ofEasyCam{
public:
    ofxObjectCamera();
    void setAutoMove();
    bool getAutoMove();
    void setChaseBall(int _val);
    int getChaseBall();
    void changeMode();
    void update();
    void setPos(float _f_Pan,float _f_Tilt,float _f_Distance);
    ofVec3f getPos();
private:
    bool b_AutoMove;
    int i_ChaseBallID;
    int i_AutoCount;
    
    int i_Mode;
    float f_PosPan;
    float f_PosTilt;
    float f_PosDistance;
    ofVec3f vf_Pos;
};


#endif

/*
 *
 */
#pragma once

#ifndef __ofxObjectParent__
#define __ofxObjectParent__

#include "ofMain.h"

class ofxObjectParent{
public:
    ofxObjectParent();
    void setup();
    void set(string s);
    void update(int _i_AngleSpeed);
    void drawLineTo(ofVec3f _pos);
    void drawLineDir(ofVec3f _direction);
    void drawLineDirMulti(ofVec3f _direction);
    virtual void setPos(float _f_Pan,float _f_Tilt,float _f_Distance);
    ofVec3f getPos();
    ofVec3f getNorm();
    void setAngle(float _f_Pan,float _f_Tilt);
    void setRandomAngle();
    void moveAngle(float _f_Pan,float _f_Tilt);
    void setNormalVec(ofVec3f _norm);
    void setAngleBetween(ofVec3f _pos1,ofVec3f _pos2);
    /*
     In this case
     Pan+: to right
     Tilt+: go up
     
     In general
     Roll+: right side down
     Pitch+: go up
     Yaw+: to right
     */
    ofVec3f convPanTilt2Vec(float _f_Pan,float _f_Tilt);
    ofVec2f convVec2PanTilt(ofVec3f _vec);

protected:
    float f_PosPan;
    float f_PosTilt;
    float f_PosDistance;
    float f_AnglePan;
    float f_AngleTilt;
    float f_AnglePanDest;
    float f_AngleTiltDest;
    ofVec3f vf_NormalVec;
    ofVec3f vf_Pos;
    //float f_PosX;
    //float f_PosY;
    //float f_PosZ;
};


#endif

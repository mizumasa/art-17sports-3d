#pragma once

#include "ofMain.h"
#include "ofxObjectMirror.h"
#include "ofxObjectHuman.h"
#include "ofxObjectLight.h"
#include "ofxObjectCamera.h"
#include "ofxObjectGoal.h"
#include "ofxObjectBall.h"
#include "ofxObjectPanel.h"
#include "ofxObjectPanel2.h"
#include "ofxObjectEffect.h"
#include "ofxObjectRing.h"
#include "ofxGui.h"
#include "ofxBlackMagic.h"
#include "common.h"
#include "ofxOsc.h"
#include "ofxOscBone.h"
#include "ofxPostGlitch.h"

#include "ofxTimeLine.h"

#include "ofxFboBlur.h"
#include "ofxAssimpModelLoader.h"
#include "ofxObjectParticle.h"



#define USE_BLACKMAGIC 0
//#define BLACKMAGIC_W 1920
//#define BLACKMAGIC_H 1080
//#define BLACKMAGIC_FPS 30
#define BLACKMAGIC_W 1280
#define BLACKMAGIC_H 720
#define BLACKMAGIC_FPS 60
#define WEBCAM_W 1280
#define WEBCAM_H 720
#define CAPTURE_W 1280
#define CAPTURE_H 720


#define MIR_X_NUM 5
#define MIR_X_ANG 9*1.5
#define MIR_Y_NUM 5
#define MIR_Y_ANG 9*1.5

#define NUM 500
#define SIZE 10

#define RADIUS 700


class RateTimer {
protected:
    float lastTick, averagePeriod, smoothing;
    bool secondTick;
public:
    RateTimer() :
    smoothing(.9) {
        reset();
    }
    void reset() {
        lastTick = 0, averagePeriod = 0, secondTick = false;
    }
    void setSmoothing(float smoothing) {
        this->smoothing = smoothing;
    }
    float getFramerate() {
        return averagePeriod == 0 ? 0 : 1 / averagePeriod;
    }
    void tick() {
        float curTick = ofGetElapsedTimef();
        if(lastTick == 0) {
            secondTick = true;
        } else {
            float curDiff = curTick - lastTick;;
            if(secondTick) {
                averagePeriod = curDiff;
                secondTick = false;
            } else {
                averagePeriod = ofLerp(curDiff, averagePeriod, smoothing);
            }
        }
        lastTick = curTick;
    }
};

class ofApp : public ofBaseApp{
public:

    void setup();
    void update();
    void update3D();
    void draw();
    void drawInput();
    void draw3D();
    void exit();
    void changeToField();
    void changeToGoal();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void scheduleChange();
    
    void setupRight();
    void updateRight();
    void drawRight();
    void setupLeft();
    void updateLeft();
    void drawLeft();

    bool b_UpdateFbo;
    bool b_GuiDraw;
    bool b_TestLight;
    ofLight testLight;
    
    ofLight areaLight;
    ofLight ballLight;
    
    ofMaterial materialPlane;
    ofMaterial materialPlaneBlack;

    int i_test;
    
    vector<ofxObjectMirror> v_ObjectMirror;
    vector<ofxObjectHuman> v_ObjectHuman;
    vector<ofxObjectLight> v_ObjectLight;
    vector<ofxObjectLight> v_ObjectLight2;

    int i_Camera;
    bool b_Render;
    
    vector<ofxObjectCamera> v_Camera;
    
    ofxFboBlur gpuBlur;
    
    ofxPanel gui;
    ofxIntSlider pi_AngleSpeed;
    ofxFloatSlider pf_Buf1;
    ofxFloatSlider pf_Buf2;
    ofxFloatSlider pf_Buf3;
    ofxFloatSlider pf_Buf4;
    ofxFloatSlider pf_Buf5;
    ofxFloatSlider pf_Buf6;
    ofxFloatSlider pf_Buf7;
    ofxFloatSlider pf_Buf8;
    ofxFloatSlider pf_Buf9;

    ofxAssimpModelLoader model;
    ofImage imgCourt;
    ofxObjectGoal modelGoal;
    ofxObjectBall modelBall;
    bool b_BallColor;
    ofxObjectParticle ballParticle;
    ofxObjectBall modelGoalBall;//goal boal
    ofxObjectBall modelGameBall;

    ofxObjectEffects objectEffect;
    ofxObjectRings objectRing;

    ofxTimeLine timeline;
    int i_SceneID;
    int i_SceneIDPre;

    ofxBlackMagic cam;
    ofVideoGrabber camMac;
    RateTimer timer;
    ofPixels camPixels;
    ofImage camImg;
    bool b_CamStart;

    ofxOscReceiver receiver;
    
    
    ofImage            lenna;
    bool            bDrawLenna;
    bool            bShowHelp;
    
    ofFbo            myFbo;
    ofxPostGlitch    myGlitch;
    
    ofXml XML;
    ofXml SCHEDULE;
    int i_WindowMode;
    int i_GameMode;
    string s_RightIP;
    
    //vector<ofVideoPlayer> v_Player;
    vector<ofxScheduleSeg> v_ScheduleSeg;
    int i_NowScheduleId;
    bool b_ScheduleStart;
    bool b_SchedulePlaying;
    ofImage i_BigSightMask;
    ofImage i_BigSightMask2;
    int i_BigSightMaskMode;
    ofSoundPlayer bgm;
    ofSoundPlayer buzzer;
    vector<ofxObjectPanel> v_ObjectPanel;
    ofxObjectFrame objectFrame;
    int i_PanelScore;
};



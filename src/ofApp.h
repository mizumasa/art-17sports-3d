#pragma once

#include "ofMain.h"
#include "ofxObjectMirror.h"
#include "ofxObjectHuman.h"
#include "ofxObjectLight.h"
#include "ofxObjectCamera.h"
#include "ofxObjectGoal.h"
#include "ofxObjectBall.h"
#include "ofxObjectEffect.h"
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
#define BLACKMAGIC_W 1920
#define BLACKMAGIC_H 1080
#define WEBCAM_W 1280
#define WEBCAM_H 720

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
    void draw();
    void drawInput();
    void draw3D();
    void exit();
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
    bool b_UpdateFbo;
    bool b_GuiDraw;
    bool b_TestLight;
    ofLight testLight;
    
    ofLight areaLight;
    ofLight ballLight;
    ofPlanePrimitive plane;
    
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

    ofxAssimpModelLoader model;
    ofImage imgCourt;
    ofxObjectGoal modelGoal;
    ofxObjectBall modelBall;
    bool b_BallColor;
    ofxObjectParticle ballParticle;
    ofxObjectBall modelGoalBall;//goal boal

    ofxObjectEffects objectEffect;
    
    ofxTimeLine timeline;
    int i_SceneID;

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
};


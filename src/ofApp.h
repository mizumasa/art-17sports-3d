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
#include "common.h"

#include "ofxFboBlur.h"
#include "ofxAssimpModelLoader.h"

#define MIR_X_NUM 5
#define MIR_X_ANG 9*1.5
#define MIR_Y_NUM 5
#define MIR_Y_ANG 9*1.5

#define NUM 500
#define SIZE 10

#define RADIUS 700


class ofApp : public ofBaseApp{
public:

    void setup();
    void update();
    void draw();
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
    ofPlanePrimitive plane;
    
    ofMaterial materialPlane;
    ofMaterial materialPlaneBlack;
    
    int i_test;
    
    vector<ofxObjectMirror> v_ObjectMirror;
    vector<ofxObjectHuman> v_ObjectHuman;
    vector<ofxObjectLight> v_ObjectLight;
    
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
    ofxObjectGoal modelGoal;
    ofxObjectBall modelBall;
    
    ofxObjectEffects objectEffect;
    
};

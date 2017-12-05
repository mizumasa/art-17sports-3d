#include "ofxObjectRing.h"
#define RING_NUM 8

float ring_path[RING_NUM][3] = {
    {0, -87.835, -40.0654},
    {0, -59.5048, -30.1963},
    {0, -31.1745, -20.3271},
    {0, -2.84435, -10.458},
    {0, 25.4858, -0.58882},
    {0, 53.8161, 9.28031},
    {0, 82.1463, 19.1495},
    {0, 110.476, 29.0186}
};

//--------------------------------------------------------------
ofxObjectRings::ofxObjectRings(){
    for(int i=0; i<RING_NUM ;i++){
        add(ofVec3f(ring_path[i][0],ring_path[i][1],ring_path[i][2]));
    }
}

//--------------------------------------------------------------
void ofxObjectRings::update(){
    for(int i=0;i<vf_Object.size();i++){
        vf_Object[i].update();
        if(vf_Object[i].isEnd()){
            vf_Object.erase(vf_Object.begin() + i);
        }
    }
}


//--------------------------------------------------------------
void ofxObjectRings::draw(){
    bool buf;
    buf = ofGetLightingEnabled();
    if(buf)ofDisableLighting();
    ofGetLightingEnabled();
    for(int i=0;i<vf_Object.size();i++){
        vf_Object[i].draw();
    }
    if(buf)ofEnableLighting();
}
//--------------------------------------------------------------
void ofxObjectRings::add(ofVec3f _vf_pos){
    ofxObjectRing buf(_vf_pos);
    vf_Object.push_back(buf);
}




//--------------------------------------------------------------
ofxObjectRing::ofxObjectRing(ofVec3f _vf_Pos){
    vf_Pos = _vf_Pos;
    b_Finished = false;
    i_Count = 0;
}

//--------------------------------------------------------------
void ofxObjectRing::update(){
    i_Count += 1;
    /*if(i_Count > 30){
        b_Finished = true;
    }*/
}

void ofxObjectRing::setSpeed(){
}

bool ofxObjectRing::isEnd(){
    return b_Finished;
}

//--------------------------------------------------------------
void ofxObjectRing::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255, 190);
    ofSetCircleResolution(200);
    ofSetLineWidth(6.0);
    ofTranslate(vf_Pos);
    ofNoFill();
    ofRotateX(90);
    ofDrawCircle(0,0,0,6);
    /*ofDrawCircle(0,0,0,i_Count);
    if(i_Count>10){
        ofDrawCircle(0,0,0,i_Count-10);
    }*/
    ofPopStyle();
    ofPopMatrix();
}


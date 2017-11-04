#include "ofxObjectEffect.h"



//--------------------------------------------------------------
ofxObjectEffects::ofxObjectEffects(){
}

//--------------------------------------------------------------
void ofxObjectEffects::update(){
    for(int i=0;i<vf_Object.size();i++){
        vf_Object[i].update();
        if(vf_Object[i].isEnd()){
            vf_Object.erase(vf_Object.begin() + i);
        }
    }
}


//--------------------------------------------------------------
void ofxObjectEffects::draw(){
    for(int i=0;i<vf_Object.size();i++){
        vf_Object[i].draw();
    }
}
//--------------------------------------------------------------
void ofxObjectEffects::add(ofVec3f _vf_pos){
    ofxObjectEffect buf(_vf_pos);
    vf_Object.push_back(buf);
}




//--------------------------------------------------------------
ofxObjectEffect::ofxObjectEffect(ofVec3f _vf_Pos){
    vf_Pos = _vf_Pos;
    b_Finished = false;
    i_Count = 0;
}

//--------------------------------------------------------------
void ofxObjectEffect::update(){
    i_Count += 1;
    if(i_Count > 30){
        b_Finished = true;
    }
}

void ofxObjectEffect::setSpeed(){
}

bool ofxObjectEffect::isEnd(){
    return b_Finished;
}

//--------------------------------------------------------------
void ofxObjectEffect::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofTranslate(vf_Pos);
    ofNoFill();
    ofDrawCircle(0,0,0,i_Count);
    if(i_Count>10){
        ofDrawCircle(0,0,0,i_Count-10);
    }
    ofPopStyle();
    ofPopMatrix();
}


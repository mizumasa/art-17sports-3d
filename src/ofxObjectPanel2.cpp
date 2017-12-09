#include "ofxObjectPanel2.h"

//--------------------------------------------------------------
ofxObjectPanel2::ofxObjectPanel2(){
    vf_Pos = ofVec3f(0, 0, 0);
    vf_Speed = ofVec3f(0, 0, 0);
    //vf_RotateSpeed = ofVec3f(2, 14, 0);
    vf_RotateSpeed = ofVec3f(0, 0, 0);
    vf_Rotate = ofVec3f(0, 0, 0);
    vf_Gravity = ofVec3f(0, 0, 0);
    t_Count = 0;
    b_Pose = true;
    b_Left = false;
    b_End = false;
    i_Size = 0;
    color = ofVec3f(255,255,255);
}
//--------------------------------------------------------------
bool ofxObjectPanel2::getEnd(){
    return b_End;
}

//--------------------------------------------------------------
void ofxObjectPanel2::setLeft(bool b_){
    b_Left = b_;
}

//--------------------------------------------------------------
void ofxObjectPanel2::start(){
    b_Pose = false;
    vf_RotateSpeed = ofVec3f(ofRandom(3,4), ofRandom(0,13), ofRandom(0,13));
    vf_Gravity = ofVec3f(0, 0.5, 0);
    vf_Speed = ofVec3f(ofRandom(-10.0, 10.0), ofRandom(0,10.0), 0);
}
//--------------------------------------------------------------
void ofxObjectPanel2::update(){
    t_Count += 1;
    if(t_Count > FLY_TIME){
        //b_Pose = true;
        b_End = true;
    }else{
        if(b_Left){
            if(t_Count < FLY_TIME/2.0){
                i_Size = t_Count;
                nowPos = startPos + ofVec2f(0,i_Size*10);
            }else{
                b_End = true;
            }
        }else{
            if(t_Count >= FLY_TIME/2.0){
                i_Size = t_Count;
                nowPos =  ofVec2f(ofGetWidth()/2.0 + endPos[0]*20,
                                  ofGetHeight()/2.0 - 30  + endPos[1]*20+ (FLY_TIME - i_Size)*10);
            }else{
                i_Size = 0;
            }
        }
    }
    if(!b_Pose){
        vf_Speed += vf_Gravity;
        vf_Speed -= vf_Speed/80.0;
        vf_Rotate += vf_RotateSpeed;
        vf_Pos += vf_Speed;
    }
}

void ofxObjectPanel2::setStartPos(ofVec2f _startPos){
    startPos = _startPos;
}

void ofxObjectPanel2::setEndPos(ofVec2f _endPos){
    endPos = _endPos;
}

void ofxObjectPanel2::noGravity(){
    vf_Gravity = ofVec3f(0,0,0);
}
void ofxObjectPanel2::setGravity(float _gravity){
    vf_Gravity = ofVec3f(0,_gravity,0);
}


//--------------------------------------------------------------
void ofxObjectPanel2::draw(){
    if(!b_End){
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(int(color[0]), int(color[1]), int(color[2]));
        //ofScale(ofGetWidth()/MACBOOKPRO_W, ofGetHeight()/MACBOOKPRO_H);
        //ofTranslate(nowPos+vf_Pos);
        //ofTranslate(tCenter - t1);
        //ofRotateX(vf_Rotate[0]);
        //ofRotateY(vf_Rotate[1]);
        //ofRotateZ(vf_Rotate[2]);
        //ofTranslate(t1 - tCenter);
        ofFill();
        ofDrawCircle(nowPos, i_Size*3);
        //ofDrawTriangle( ofVec2f(0,0), t2-t1, t3-t1);
        ofPopStyle();
        ofPopMatrix();
    }
}



ofxObjectPanels2::ofxObjectPanels2(){
}

void ofxObjectPanels2::add(ofVec2f _startPos, ofVec3f _ballShift ,bool _left){
    ofxObjectPanel2 bufPanel;
    bufPanel.setStartPos(_startPos);
    bufPanel.setEndPos(ofVec2f(_ballShift[0], - _ballShift[2]));
    bufPanel.setLeft(_left);
    v_Panel.push_back(bufPanel);
}

void ofxObjectPanels2::draw(){
    for(int i=0;i<v_Panel.size();i++){
        v_Panel[i].draw();
    }
}
void ofxObjectPanels2::update(){
    for(int i=0;i<v_Panel.size();i++){
        v_Panel[i].update();
    }
}
void ofxObjectPanels2::noGravity(){
    for(int i=0;i<v_Panel.size();i++){
        v_Panel[i].noGravity();
    }
}
void ofxObjectPanels2::setGravity(float _gravity){
    for(int i=0;i<v_Panel.size();i++){
        v_Panel[i].setGravity(_gravity);
    }
}

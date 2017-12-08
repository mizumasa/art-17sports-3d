#include "ofxObjectPanel.h"

#define FRAME_NUM 16
#define LEFT_FRAME_WIDTH 57
#define RIGHT_FRAME_WIDTH 56

int frame_pos[FRAME_NUM][4][2]={{{128 - LEFT_FRAME_WIDTH, 62}, {128, 62}, {188, 159}, {188 - LEFT_FRAME_WIDTH, 159}},
    {{188 - LEFT_FRAME_WIDTH, 159}, {188, 159}, {249, 254}, {249 - LEFT_FRAME_WIDTH, 254}},
    {{249 - LEFT_FRAME_WIDTH, 254}, {249, 254}, {308, 347}, {308 - LEFT_FRAME_WIDTH, 347}},
    {{308 - LEFT_FRAME_WIDTH, 347}, {308, 347}, {366, 438}, {366 - LEFT_FRAME_WIDTH, 438}},
    {{366 - LEFT_FRAME_WIDTH, 438}, {366, 438}, {423, 527}, {423 - LEFT_FRAME_WIDTH, 527}},
    {{423 - LEFT_FRAME_WIDTH, 527}, {423, 527}, {479, 615}, {479 - LEFT_FRAME_WIDTH, 615}},
    {{479 - LEFT_FRAME_WIDTH, 615}, {479, 615}, {532, 699}, {532 - LEFT_FRAME_WIDTH, 699}},
    {{532 - LEFT_FRAME_WIDTH, 699}, {532, 699}, {585, 780}, {585 - LEFT_FRAME_WIDTH, 780}},
    {{690, 780}, {690 + RIGHT_FRAME_WIDTH, 780}, {743 + RIGHT_FRAME_WIDTH, 699}, {743, 699}},
    {{743, 699}, {743 + RIGHT_FRAME_WIDTH, 699}, {797 + RIGHT_FRAME_WIDTH, 615}, {797, 615}},
    {{797, 615}, {797 + RIGHT_FRAME_WIDTH, 615}, {853 + RIGHT_FRAME_WIDTH, 527}, {853, 527}},
    {{853, 527}, {853 + RIGHT_FRAME_WIDTH, 527}, {910 + RIGHT_FRAME_WIDTH, 438}, {910, 438}},
    {{910, 438}, {910 + RIGHT_FRAME_WIDTH, 438}, {968 + RIGHT_FRAME_WIDTH, 347}, {968, 347}},
    {{968, 347}, {968 + RIGHT_FRAME_WIDTH, 347}, {1027 + RIGHT_FRAME_WIDTH, 254}, {1027, 254}},
    {{1027, 254}, {1027 + RIGHT_FRAME_WIDTH, 254}, {1087 + RIGHT_FRAME_WIDTH, 159}, {1087, 159}},
    {{1087, 159}, {1087 + RIGHT_FRAME_WIDTH, 159}, {1150 + RIGHT_FRAME_WIDTH, 62}, {1150, 62}}};
//--------------------------------------------------------------
ofxObjectPanel::ofxObjectPanel(){
    vf_Pos = ofVec3f(0, 0, 0);
    vf_Speed = ofVec3f(0, 0, 0);
    //vf_RotateSpeed = ofVec3f(2, 14, 0);
    vf_RotateSpeed = ofVec3f(0, 0, 0);
    vf_Rotate = ofVec3f(0, 0, 0);
    vf_Gravity = ofVec3f(0, 0, 0);
    t_Count = 0;
    b_Pose = true;
    b_Left = false;
}
//--------------------------------------------------------------
void ofxObjectPanel::setLeft(bool b_){
    b_Left = b_;
}

//--------------------------------------------------------------
void ofxObjectPanel::start(){
    b_Pose = false;
    vf_RotateSpeed = ofVec3f(ofRandom(3,4), ofRandom(0,13), ofRandom(0,13));
    vf_Gravity = ofVec3f(0, 0.5, 0);
    vf_Speed = ofVec3f(ofRandom(-10.0, 10.0), ofRandom(0,10.0), 0);
}
//--------------------------------------------------------------
void ofxObjectPanel::update(){
    t_Count += 1;
    if(t_Count > FLY_TIME){
        //b_Pose = true;
    }else{
        if(b_Left){
            nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }else{
            nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }
    }
    if(!b_Pose){
        vf_Speed += vf_Gravity;
        vf_Speed -= vf_Speed/80.0;
        vf_Rotate += vf_RotateSpeed;
        vf_Pos += vf_Speed;
    }
}

void ofxObjectPanel::setStartPos(ofVec2f _startPos,ofVec2f _t1,ofVec2f _t2,ofVec2f _t3){
    startPos = _startPos;
    t1 = _t1;
    t2 = _t2;
    t3 = _t3;
    tCenter = (t1+t2+t3)/3;
    color = ofVec3f(116,6,22) * tCenter[1] / MACBOOKPRO_H + ofVec3f(240,160,185) * (MACBOOKPRO_H - tCenter[1]) / MACBOOKPRO_H;
}

void ofxObjectPanel::noGravity(){
    vf_Gravity = ofVec3f(0,0,0);
}
void ofxObjectPanel::setGravity(float _gravity){
    vf_Gravity = ofVec3f(0,_gravity,0);
}

//--------------------------------------------------------------
void ofxObjectPanel::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(int(color[0]), int(color[1]), int(color[2]));
    
    //ofTranslate(vf_Pos);
    ofTranslate(nowPos+vf_Pos);
    ofTranslate(tCenter - t1);
    ofRotateX(vf_Rotate[0]);
    ofRotateY(vf_Rotate[1]);
    ofRotateZ(vf_Rotate[2]);
    ofTranslate(t1 - tCenter);
    ofFill();
    ofDrawTriangle( ofVec2f(0,0), t2-t1, t3-t1);
    ofPopStyle();
    ofPopMatrix();
}




//--------------------------------------------------------------
ofxObjectPanelFrame::ofxObjectPanelFrame(){
    vf_Pos = ofVec3f(0, 0, 0);
    vf_Speed = ofVec3f(0, 0, 0);
    vf_RotateSpeed = ofVec3f(0, 0, 0);
    vf_Rotate = ofVec3f(0, 0, 0);
    vf_Gravity = ofVec3f(0, 0, 0);
    t_Count = 0;
    b_Pose = true;
    b_Left = false;
}

//--------------------------------------------------------------
void ofxObjectPanelFrame::start(){
    b_Pose = false;
    vf_RotateSpeed = ofVec3f(ofRandom(3,4), ofRandom(0,13), ofRandom(0,13));
    vf_Gravity = ofVec3f(0, 0.5, 0);
    vf_Speed = ofVec3f(ofRandom(-10.0, 10.0), ofRandom(0,10.0), 0);
}
//--------------------------------------------------------------
void ofxObjectPanelFrame::update(){
    t_Count += 1;
    /*if(t_Count > FLY_TIME){
        //b_Pose = true;
    }else{
        if(b_Left){
            nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }else{
            nowPos = ( startPos * (FLY_TIME - t_Count) + t1 * t_Count )/FLY_TIME +
            ofVec2f(0,-100)*sin(PI*t_Count/FLY_TIME);
        }
    }*/
    if(!b_Pose){
        vf_Speed += vf_Gravity;
        vf_Speed -= vf_Speed/80.0;
        vf_Rotate += vf_RotateSpeed;
        vf_Pos += vf_Speed;
    }
}

void ofxObjectPanelFrame::setPoint(ofVec2f _pos){
    if(vf_Points.size() == 0){
        color = ofVec3f(int( 255 * _pos[1] / ofGetHeight()),100,100);
    }
    vf_Points.push_back(_pos);
}

void ofxObjectPanelFrame::noGravity(){
    vf_Gravity = ofVec3f(0,0,0);
}
void ofxObjectPanelFrame::setGravity(float _gravity){
    vf_Gravity = ofVec3f(0,_gravity,0);
}

//--------------------------------------------------------------
void ofxObjectPanelFrame::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(int(color[0]), int(color[1]), int(color[2]));
    
    ofScale(ofGetWidth()/MACBOOKPRO_W, ofGetHeight()/MACBOOKPRO_H);
    ofTranslate(nowPos+vf_Pos);
    //ofTranslate(tCenter - t1);
    ofRotateX(vf_Rotate[0]);
    ofRotateY(vf_Rotate[1]);
    ofRotateZ(vf_Rotate[2]);
    //ofTranslate(t1 - tCenter);
    ofFill();
    //ofDrawTriangle( ofVec2f(0,0), t2-t1, t3-t1);
    ofDrawTriangle(vf_Points[0],vf_Points[1],vf_Points[2]);
    ofDrawTriangle(vf_Points[0],vf_Points[2],vf_Points[3]);
    cout << vf_Points[0] << endl;
    ofPopStyle();
    ofPopMatrix();
}


ofxObjectFrame::ofxObjectFrame(){
}

void ofxObjectFrame::setPoints(){
    for(int i =0;i<FRAME_NUM;i++){
        ofxObjectPanelFrame bufPanel;
        bufPanel.setPoint(ofVec2f(frame_pos[i][0][0],frame_pos[i][0][1]));
        bufPanel.setPoint(ofVec2f(frame_pos[i][1][0],frame_pos[i][1][1]));
        bufPanel.setPoint(ofVec2f(frame_pos[i][2][0],frame_pos[i][2][1]));
        bufPanel.setPoint(ofVec2f(frame_pos[i][3][0],frame_pos[i][3][1]));
        v_Frame.push_back(bufPanel);
    }
}

void ofxObjectFrame::draw(){
    for(int i=0;i<v_Frame.size();i++){
        v_Frame[i].draw();
    }
}
void ofxObjectFrame::update(){
    for(int i=0;i<v_Frame.size();i++){
        v_Frame[i].update();
    }
}
void ofxObjectFrame::noGravity(){
    for(int i=0;i<v_Frame.size();i++){
        v_Frame[i].noGravity();
    }
}
void ofxObjectFrame::setGravity(float _gravity){
    for(int i=0;i<v_Frame.size();i++){
        v_Frame[i].setGravity(_gravity);
    }
}

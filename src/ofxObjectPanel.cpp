#include "ofxObjectPanel.h"

#define FRAME_NUM 25
//#define LEFT_FRAME_WIDTH 57
//#define RIGHT_FRAME_WIDTH 56
#define LEFT_FRAME_WIDTH 72
#define RIGHT_FRAME_WIDTH 71
#define FRAME_TOP_X 31
#define FRAME_TOP_Y 50

int frameColorMode[2][3]={
    {45,255,254},
    {252,36,224}
};

int colorMode[2][2][3]={
    {{183,38,251},{250,39,244}},
    {{254,222,50},{209,251,53}}
};

int frame_pos[FRAME_NUM][4][2]={
    //{{128 - LEFT_FRAME_WIDTH, 62}, {128, 62}, {188, 159}, {188 - LEFT_FRAME_WIDTH, 159}},
    {{128 - LEFT_FRAME_WIDTH, 62}, {95, 12}, {188, 159}, {188 - LEFT_FRAME_WIDTH, 159}},
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
    //{{1087, 159}, {1087 + RIGHT_FRAME_WIDTH, 159}, {1150 + RIGHT_FRAME_WIDTH, 62}, {1150, 62}}
    {{1087, 159}, {1087 + RIGHT_FRAME_WIDTH, 159}, {1150 + RIGHT_FRAME_WIDTH, 62}, {1181, 12}},
    {{128-FRAME_TOP_X, 62-FRAME_TOP_Y}, {240-FRAME_TOP_X, 62-FRAME_TOP_Y}, {240, 62}, {128, 62}},
    {{240-FRAME_TOP_X, 62-FRAME_TOP_Y}, {354-FRAME_TOP_X, 62-FRAME_TOP_Y}, {354, 62}, {240, 62}},
    {{354-FRAME_TOP_X, 62-FRAME_TOP_Y}, {467-FRAME_TOP_X, 62-FRAME_TOP_Y}, {467, 62}, {354, 62}},
    {{467-FRAME_TOP_X, 62-FRAME_TOP_Y}, {581-FRAME_TOP_X, 62-FRAME_TOP_Y}, {581, 62}, {467, 62}},
    {{581-FRAME_TOP_X, 62-FRAME_TOP_Y}, {694-FRAME_TOP_X, 62-FRAME_TOP_Y}, {694, 62}, {581, 62}},
    {{694-FRAME_TOP_X, 62-FRAME_TOP_Y}, {809-FRAME_TOP_X, 62-FRAME_TOP_Y}, {809, 62}, {694, 62}},
    {{809-FRAME_TOP_X, 62-FRAME_TOP_Y}, {922-FRAME_TOP_X, 62-FRAME_TOP_Y}, {922, 62}, {809, 62}},
    {{922-FRAME_TOP_X, 62-FRAME_TOP_Y}, {1036-FRAME_TOP_X, 62-FRAME_TOP_Y}, {1036, 62}, {922, 62}},
    {{1036-FRAME_TOP_X, 62-FRAME_TOP_Y}, {1150+FRAME_TOP_X, 62-FRAME_TOP_Y}, {1150, 62}, {1036, 62}}
};
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
    i_ColorMode = 0;
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
    color = ofVec3f(ofClamp(colorMode[i_ColorMode][0][0] + ofRandom(-20,20),0,255),
                    ofClamp(colorMode[i_ColorMode][0][1] + ofRandom(-20,20),0,255),
                    ofClamp(colorMode[i_ColorMode][0][2] + ofRandom(-20,20),0,255))
    * tCenter[1] / MACBOOKPRO_H +
    ofVec3f(ofClamp(colorMode[i_ColorMode][1][0] + ofRandom(-20,20),0,255),
            ofClamp(colorMode[i_ColorMode][1][1] + ofRandom(-20,20),0,255),
            ofClamp(colorMode[i_ColorMode][1][2] + ofRandom(-20,20),0,255)) * (MACBOOKPRO_H - tCenter[1]) / MACBOOKPRO_H;
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
    if(b_Left){
        ofScale(0.3, 0.3);
    }
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
    i_Alpha = 255;
}

//--------------------------------------------------------------
void ofxObjectPanelFrame::start(){
    b_Pose = false;
    vf_RotateSpeed = ofVec3f(ofRandom(3,4), ofRandom(0,13), ofRandom(0,13));
    vf_Gravity = ofVec3f(0, 0.5, 0);
    vf_Speed = ofVec3f(ofRandom(-10.0, 10.0), ofRandom(0,10.0), 0);
}
//--------------------------------------------------------------
void ofxObjectPanelFrame::update(int _i_Alpha){
    t_Count += 1;
    i_Alpha = _i_Alpha;
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
    //ofSetColor(int(color[0]), int(color[1]), int(color[2]));
    ofEnableAlphaBlending();
    ofSetColor(
               frameColorMode[i_ColorMode][0],
               frameColorMode[i_ColorMode][1],
               frameColorMode[i_ColorMode][2],
               i_Alpha
    );
    
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
    //cout << vf_Points[0] << endl;
    ofPopStyle();
    ofPopMatrix();
}


ofxObjectFrame::ofxObjectFrame(){
    b_Blink = false;
    t_Count = 0;
    i_BlinkCount = 0;
    b_Visible = true;
    i_Alpha = 255;
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
    if(b_Blink and (t_Count%2==0)){
        return;
    }
    if(b_Visible){
        for(int i=0;i<v_Frame.size();i++){
            v_Frame[i].draw();
        }
    }
}
void ofxObjectFrame::update(){
    t_Count += 1;
    for(int i=0;i<v_Frame.size();i++){
        v_Frame[i].i_ColorMode = i_ColorMode;
        v_Frame[i].update(i_Alpha);
    }
    if(i_BlinkCount){
        i_BlinkCount ++;
        if(i_BlinkCount > i_BlinkMax){
            i_BlinkCount = 0;
            b_Blink = false;
        }
    }
}

void ofxObjectFrame::setBlink(bool _state){
    b_Blink = _state;
}

void ofxObjectFrame::setBlinkTimer(int i_time){
    i_BlinkMax = i_time;
    b_Blink = true;
    i_BlinkCount = 1;
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

void ofxObjectFrame::setVisual(int i_mode){
    switch(i_mode){
        case 0://visible
            b_Visible = true;
            i_Alpha = 255;
            break;
        case 1://alpha
            b_Visible = true;
            i_Alpha = 120;
            break;
        case 2://no visible
            b_Visible = false;
            break;
    }
}


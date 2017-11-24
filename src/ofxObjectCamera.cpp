#include "ofxObjectCamera.h"

//--------------------------------------------------------------
ofxObjectCamera::ofxObjectCamera(){
    b_AutoMove=false;
    b_ChaseBall=false;
    i_Mode = 0;
    i_AutoCount = 0;
    f_PosPan = 0;
    f_PosTilt = 0;
    f_PosDistance = 0;
}

//--------------------------------------------------------------
void ofxObjectCamera::setAutoMove(){
    b_AutoMove=true;
    changeMode();
}

//--------------------------------------------------------------
void ofxObjectCamera::setChaseBall(){
    b_ChaseBall=true;
}
//--------------------------------------------------------------
bool ofxObjectCamera::getChaseBall(){
    return b_ChaseBall;
}

//--------------------------------------------------------------
void ofxObjectCamera::changeMode(){
    //i_Mode = int(ofRandom(0, 2))%2;
    i_Mode = (i_Mode+1)%2;
    float distanceBuf;
    distanceBuf = ofRandom(-1, 1);
    if(distanceBuf>0){
        distanceBuf = ofRandom(MOVE_RADIUS_MIN,MOVE_RADIUS_MAX);
    }else{
        distanceBuf = ofRandom(MOVE_RADIUS_MIN2,MOVE_RADIUS_MAX2);
    }
    switch (i_Mode) {
        case 0:
            setPos(ofRandom(120, 180), 10, distanceBuf);
            lookAt(ofVec3f(0,MOVE_RADIUS_MAX,-100), ofVec3f(0,0,1));
            break;
        case 1:
            setPos(ofRandom(-120, -180), 10, distanceBuf);
            lookAt(ofVec3f(0,MOVE_RADIUS_MAX,-100), ofVec3f(0,0,1));
            break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void ofxObjectCamera::setPos(float _f_Pan,float _f_Tilt,float _f_Distance){
    f_PosPan = _f_Pan;
    f_PosTilt = _f_Tilt;
    f_PosDistance = _f_Distance;
    vf_Pos.x = _f_Distance * cos(PI * _f_Tilt / 180.0) * sin(PI * _f_Pan / 180.0);
    vf_Pos.y = _f_Distance * cos(PI * _f_Tilt / 180.0) * cos(PI * _f_Pan / 180.0);
    vf_Pos.z = _f_Distance * sin(PI * _f_Tilt / 180.0);
    setPosition(vf_Pos);
}

//--------------------------------------------------------------
void ofxObjectCamera::update(){
    if(b_AutoMove){
        switch (i_Mode) {
            case 0:
                setPos(f_PosPan+0.1, f_PosTilt, f_PosDistance);
                break;
            case 1:
                setPos(f_PosPan-0.1, f_PosTilt, f_PosDistance);
                break;
            default:
                break;
        }
        i_AutoCount += 1;
        if(i_AutoCount > MOVE_CUT_COUNT){
            i_AutoCount = 0;
            changeMode();
        }
    }
}



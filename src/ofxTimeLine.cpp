/*
 *
*/

#include "ofxTimeLine.h"

#define f_TimeLineSabi 0.262
#define f_TimeLineLag 0.001
#define SCENE1_START 0
#define SCENE2_START 10

//--------------------------------------------------------------
ofxTimeLine::ofxTimeLine(){
}
//--------------------------------------------------------------
void ofxTimeLine::setup(){
    
    float timeLineData[STEP_NUM][4] = {
        {SCENE1_START+1 ,SCENE1_START+1 +1,AID_INIT,0},
        {SCENE1_START+2 ,SCENE1_START+2 +1,AID_CHANGE_ANGLE,3},
        {SCENE1_START+3 ,SCENE1_START+3 +1,AID_MOVE_ANGLE,4},
        {SCENE1_START+4 ,SCENE1_START+4 +1,AID_CHANGE_ANGLE,5},
        {SCENE1_START+5 ,SCENE1_START+5 +1,AID_MOVE_ANGLE,6},
        
        {SCENE1_START+5 ,SCENE1_START+5 +1,AID_MOVE_HUMAN,7},
        {SCENE1_START+6 ,SCENE1_START+6 +1,AID_MOVE_HUMAN,8},
        {SCENE1_START+7 ,SCENE1_START+7 +1,AID_MOVE_HUMAN,9},
        {SCENE1_START+8 ,SCENE1_START+8 +1,AID_HUMAN_ZOOM_IN,10},
        {SCENE1_START+9 ,SCENE1_START+9 +1,AID_FADEOUT,11},
        
        {SCENE2_START,SCENE2_START+1,AID_CHANGE_SCENE_TO_CHROME,2},
        {SCENE2_START+1,SCENE2_START+1+1,AID_CHANGE_SITE,0},
        {SCENE2_START+2,SCENE2_START+2 +1,AID_FADEIN,1},
        { SCENE2_START+3,SCENE2_START+3 +1,AID_SCROLL,0},
        { SCENE2_START+4,SCENE2_START+4 +1,AID_SCROLL,0},
        
        { SCENE2_START+5,SCENE2_START+5 +1,AID_SCROLL,0},
        { SCENE2_START+6,SCENE2_START+6 +1,AID_CHANGE_SITE,0},
        { SCENE2_START+7,SCENE2_START+7 +1,AID_SCROLL,0},
        { SCENE2_START+8,SCENE2_START+8 +1,AID_SCROLL,0},
        { SCENE2_START+9,SCENE2_START+9 +1,AID_SCROLL,0},
        
        { SCENE2_START+10,SCENE2_START+10 +1,AID_CHANGE_SITE,0},
        { SCENE2_START+11,SCENE2_START+11 +1,AID_SCROLL,0},
        { SCENE2_START+12,SCENE2_START+12 +1,AID_SCROLL,0},
        { SCENE2_START+13,SCENE2_START+13 +1,AID_SCROLL,0},
        { SCENE2_START+14,SCENE2_START+14 +1,AID_FADEOUT,11},
        
        { SCENE2_START+15,SCENE2_START+15 +1,AID_CHANGE_SCENE_TO_WORLD,2},
        { SCENE2_START+16,SCENE2_START+16 +1,AID_FADEIN,1},
        { SCENE2_START+17,SCENE2_START+17 +1,AID_HUMAN_ZOOM_OUT,1},
        { SCENE2_START+18,SCENE2_START+18 +1,AID_LOOP_BACK,1},
    };

    bool onceFlag[ACT_ID_NUM] = {true,true,true,true,true,true,true,true,true,true,true,true};
    for(int i=0;i<STEP_NUM;i++){
        vvf_TimeLineTime.push_back(ofVec2f(timeLineData[i][0],timeLineData[i][1]));
        vi_TimeLineActId.push_back(timeLineData[i][2]);
        vi_TimeLineParam.push_back(timeLineData[i][3]);
        vb_TimeLineUsedFlag.push_back(false);
    }
    for(int i=0;i<ACT_ID_NUM;i++){
        vb_ActState.push_back(false);
        vb_ActOnceFlag.push_back(onceFlag[i]);
        vb_ActParam.push_back(-1);
    }
}

//--------------------------------------------------------------
void ofxTimeLine::update(float pos){
    for(int i=0;i<STEP_NUM;i++){
        if((vvf_TimeLineTime[i][0] < pos) && (pos < vvf_TimeLineTime[i][1])){
            if(vb_ActOnceFlag[vi_TimeLineActId[i]] && (vb_TimeLineUsedFlag[i])){
            }else{
                vb_ActState[vi_TimeLineActId[i]]=true;
                vb_ActParam[vi_TimeLineActId[i]]=vi_TimeLineParam[i];
                vb_TimeLineUsedFlag[i]=true;
            }
        }else if (vb_TimeLineUsedFlag[i] && (pos >= vvf_TimeLineTime[i][1])){
            vb_TimeLineUsedFlag[i]=false;
            vb_ActState[vi_TimeLineActId[i]]=false;
        }
    }
}
//--------------------------------------------------------------

void ofxTimeLine::draw(){
    for(int i=0;i<ACT_ID_NUM;i++){
        bool buf = getState(i);
        ofDrawBitmapString(buf, 800, (i+1)*30);
    }
    for(int i=0;i<STEP_NUM;i++){
        ofDrawBitmapString(vb_TimeLineUsedFlag[i], 850, (i+1)*30);
    }
}
//--------------------------------------------------------------
void ofxTimeLine::clear(){
    for(int i=0;i<STEP_NUM;i++){
        vb_TimeLineUsedFlag[i]=false;
    }
    for(int i=0;i<ACT_ID_NUM;i++){
        vb_ActState[i]=false;
    }
}
//--------------------------------------------------------------

bool ofxTimeLine::getState(int actId){
    if(vb_ActState[actId]){
        if(vb_ActOnceFlag[actId]){
            vb_ActState[actId]=false;
        }
        return true;
    }else{
        return false;
    }
}

int ofxTimeLine::getParam(int actId){
    return vb_ActParam[actId];
}

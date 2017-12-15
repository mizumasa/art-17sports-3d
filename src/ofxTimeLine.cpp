/*
 *
*/

#include "ofxTimeLine.h"

#define f_TimeLineSabi 0.262
#define f_TimeLineLag 0.001

//--------------------------------------------------------------
ofxTimeLine::ofxTimeLine(){
}
//--------------------------------------------------------------
void ofxTimeLine::setup(){
    
    float timeLineData[STEP_NUM][4] = {
        {SCENE1_START+0.1 ,SCENE1_START+0.1 +1,AID_INIT,0},
        {SCENE1_START+1 ,SCENE1_START+1 +1,AID_COUNT_1,3},
        {SCENE1_START+2 ,SCENE1_START+2 +1,AID_COUNT_1,2},
        {SCENE1_START+3 ,SCENE1_START+3 +1,AID_COUNT_1,1},
        {SCENE1_START+4 ,SCENE1_START+4 +1,AID_COUNT_1,0},
        {SCENE1_START+6 ,SCENE1_START+6 +1,AID_CHANGE_TO_THROW_1,0},
        
        {SCENE2_START+1 ,SCENE2_START+1 +1,AID_COUNT_2,0},
        {SCENE2_START+2 ,SCENE2_START+2 +1,AID_COUNT_2,1},
        {SCENE2_START+3 ,SCENE2_START+3 +1,AID_COUNT_2,2},
        {SCENE2_START+4 ,SCENE2_START+4 +1,AID_COUNT_2,3},
        {SCENE2_START+5+COUNT_2_SEC*0 ,SCENE2_START+5+COUNT_2_SEC*0 +1,AID_COUNT_2,4},
        {SCENE2_START+5+COUNT_2_SEC*1 ,SCENE2_START+5+COUNT_2_SEC*1 +1,AID_COUNT_2,5},
        {SCENE2_START+5+COUNT_2_SEC*2 ,SCENE2_START+5+COUNT_2_SEC*2 +1,AID_COUNT_2,6},
        {SCENE2_START+5+COUNT_2_SEC*3 ,SCENE2_START+5+COUNT_2_SEC*3 +1,AID_COUNT_2,7},
        {SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 0 ,SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 0 +1,AID_COUNT_2,8},
        {SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 1 ,SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 1 +1,AID_COUNT_2,9},
        {SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 2 ,SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 2 +1,AID_COUNT_2,10},
        {SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 3 ,SCENE2_START+1+(1+COUNT_2_SEC)*4 + COUNT_3_SEC * 3 +1,AID_COUNT_2,11},
        {SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 0 ,SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 0 +1,AID_COUNT_2,12},
        {SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 1 ,SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 1 +1,AID_COUNT_2,13},
        {SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 2 ,SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 2 +1,AID_COUNT_2,14},
        {SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 3 ,SCENE2_START+1+(1+COUNT_2_SEC+ COUNT_3_SEC)*4 + COUNT_4_SEC * 3 +1,AID_COUNT_2,15},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 0 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 0 +1,AID_COUNT_2,16},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 1 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 1 +1,AID_COUNT_2,17},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 2 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 2 +1,AID_COUNT_2,18},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 3 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC)*4 + COUNT_5_SEC * 3 +1,AID_COUNT_2,19},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 0 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 0 +1,AID_COUNT_2,20},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 1 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 1 +1,AID_COUNT_2,21},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 2 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 2 +1,AID_COUNT_2,22},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 3 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC)*4 + COUNT_6_SEC * 3 +1,AID_COUNT_2,23},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 0 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 0 +1,AID_COUNT_2,24},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 1 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 1 +1,AID_COUNT_2,25},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 2 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 2 +1,AID_COUNT_2,26},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 3 ,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC)*4 + COUNT_7_SEC * 3 +1,AID_COUNT_2,27},
        {SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC + COUNT_7_SEC)*4 + 1,SCENE2_START+1+(1+COUNT_2_SEC+COUNT_3_SEC+COUNT_4_SEC+COUNT_5_SEC+ COUNT_6_SEC+ COUNT_7_SEC)*4 + 1+1,AID_CHANGE_TO_THROW_2,0},

        /*
        AID_COUNT_2_1,
        AID_COUNT_2_2,
        AID_COUNT_2_3,
        AID_COUNT_2_4,
        AID_COUNT_2_5,
        AID_COUNT_2_6,
        AID_COUNT_2_7,
        AID_CHANGE_TO_THROW_2,*/
    };

    bool onceFlag[ACT_ID_NUM] = {true,true,true,true,true,true,true,true,true,true,true};
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

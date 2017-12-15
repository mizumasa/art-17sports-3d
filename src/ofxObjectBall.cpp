#include "ofxObjectBall.h"

//--------------------------------------------------------------
ofxObjectBall::ofxObjectBall(){
    model.loadModel("Basketball_Ball.3DS");
    vf_Pos = ofVec3f(0, 0, 30);
    vf_Speed = ofVec3f(0, 0, 0);
    vf_RotateSpeed = ofVec3f(2, 14, 0);
    vf_Rotate = ofVec3f(0, 0, 0);
    vf_Gravity = ofVec3f(0, 0, -0.2);
    
    vf_SlowShift = ofVec3f(0, 0, 0);
    b_GoalLoop = false;
    t_Count = 0;
    b_NoResistance = false;
    b_Slow = false;
    
}

//--------------------------------------------------------------
void ofxObjectBall::update(){
    t_Count += 1;
    
    //if(!b_Pose and !(b_Slow and (t_Count %2 == 0)) ){
    if(!b_Pose){
        vf_Speed += vf_Gravity;
        if(!b_NoResistance)vf_Speed -= vf_Speed/80.0;
        vf_Rotate += vf_RotateSpeed;
        vf_Pos += vf_Speed;
        if(vf_Pos[2]<GROUND_LEVEL+5){
            vf_Pos[2]=GROUND_LEVEL+5;
            vf_Speed[2] = -vf_Speed[2]*2/3;
            //vf_Pos[2] = GROUND_LEVEL;
            if(abs(vf_Speed[0])<0.1){
                vf_Speed[0] = vf_Speed[0]/1.5 + vf_Speed[2]*(ofRandom(0.4) - 0.2);
            }else{
                vf_Speed[0] = vf_Speed[0]/1.5;
            }
            if(vf_Pos[1]>0){
                vf_Speed[1] = vf_Speed[1]/1.5 - 1.0 * vf_Pos[1] / COURT_HEIGHT_HALF;
            }else{
                vf_Speed[1] = vf_Speed[1]/1.5;
            }
        }
        if(vf_Pos[1]>COURT_HEIGHT_HALF){
            vf_Pos[1]=COURT_HEIGHT_HALF;
            vf_Speed[1] = -vf_Speed[1]*2/3;
            vf_Speed[0] = vf_Speed[0]/1.5;
            vf_Speed[2] = vf_Speed[2]/2;
        }
        if(vf_Pos[1]< -COURT_HEIGHT_HALF){
            vf_Pos[1] = -COURT_HEIGHT_HALF;
            vf_Speed[1] = -vf_Speed[1]*2/3;
            vf_Speed[0] = vf_Speed[0]/1.5;
            vf_Speed[2] = vf_Speed[2]/2;
        }
        if(vf_Pos[0]>COURT_WIDTH_HALF){
            vf_Pos[0]=COURT_WIDTH_HALF;
            vf_Speed[0] = -vf_Speed[0]*2/3;
            vf_Speed[1] = vf_Speed[1]/1.5;
            vf_Speed[2] = vf_Speed[2]/2;
        }
        if(vf_Pos[0]<-COURT_WIDTH_HALF){
            vf_Pos[0]=-COURT_WIDTH_HALF;
            vf_Speed[0] = -vf_Speed[0]*2/3;
            vf_Speed[1] = vf_Speed[1]/1.5;
            vf_Speed[2] = vf_Speed[2]/2;
        }
        if(b_GoalLoop){
            vf_Pos = ofVec3f(GOAL_LOOP_RADIUS*(-cos((t_Count-f_SlowCountSum)/5.0)),
                             GOAL_Y_OFFSET+104.4+20+GOAL_LOOP_RADIUS*sin((t_Count-f_SlowCountSum)/5.0),
                             130.11);
            if(f_SlowCount>0){
                f_SlowCount = MIN(1.0, f_SlowCount+0.01);
                f_SlowCountSum += f_SlowCount;
            }
        }
    }
    if(!b_Pose and i_ReverseCount == 0 and i_ReplayCount == 0){
        if(t_Count%2==0){
            if(vv_RouteHistory.size()>=PATH_SAVE_NUM){
                i_NowHistoryPos = (i_NowHistoryPos + 1) % vv_RouteHistory.size();
                vv_RouteHistory[i_NowHistoryPos] = vf_Pos;
            }else{
                vv_RouteHistory.push_back(vf_Pos);
                i_NowHistoryPos = vv_RouteHistory.size()-1;
            }
        }
    }else{
        if(i_ReverseCount > 0){
            i_ReverseCount += 1;
            if(i_ReverseCount == (vv_RouteHistory.size()-1)){
                i_ReverseCount = 0;
            }else{
                vf_Pos = vv_RouteHistory[(i_NowHistoryPos - i_ReverseCount) % vv_RouteHistory.size()];
            }
        }else{
            if(i_ReplayCount > 0){
                if(t_Count%4==0){
                    i_ReplayCount += 1;
                    if(i_ReplayCount == (vv_RouteHistory.size()-1)){
                        i_ReplayCount = 0;
                    }else{
                        vf_Pos = vv_RouteHistory[(i_NowHistoryPos + i_ReplayCount) % vv_RouteHistory.size()];
                    }
                }
            }
        }
    }
}

void ofxObjectBall::releaseGoal(){
    if(b_GoalLoop){
        b_GoalLoop = false;
        vf_Speed = ofVec3f(
                           (cos((t_Count-f_SlowCountSum)/5.0)),
                           -sin((t_Count-f_SlowCountSum)/5.0),
                           0
                           );
        setGravity(0.2);
    }
}
void ofxObjectBall::releaseOut(){
    if(b_GoalLoop){
        b_GoalLoop = false;
        vf_Speed = ofVec3f(
                           (-cos((t_Count-f_SlowCountSum)/5.0)),
                           sin((t_Count-f_SlowCountSum)/5.0),
                           0
                           );
        setGravity(0.2);
    }
}

void ofxObjectBall::setSpeed(ofVec3f _vf_Speed){
    vf_Speed = _vf_Speed;
}

void ofxObjectBall::throwTo(ofVec3f _vf_Pos, float _speed){
    vf_Speed = (_vf_Pos - vf_Pos);
    vf_Speed = _speed * vf_Speed / vf_Speed.length();
    t_Count = 0;
}

void ofxObjectBall::setGoalLoop(){
    b_GoalLoop = true;
    f_SlowCount = 0;
    f_SlowCountSum = 0;
}

void ofxObjectBall::setNoResistance(){
    b_NoResistance = true;
}

void ofxObjectBall::startGoalLoopSlow(){
    f_SlowCount = 0.01;
}

void ofxObjectBall::setPos(ofVec3f _vf_Pos, ofVec3f _vf_Rotate){
    vf_Pos = _vf_Pos;
    vf_Rotate = _vf_Rotate;
}

ofVec3f ofxObjectBall::getPos(){
    return vf_Pos;
}

void ofxObjectBall::noGravity(){
    vf_Gravity = ofVec3f(0,0,0);
}
void ofxObjectBall::setGravity(float _gravity){
    vf_Gravity = ofVec3f(0,0,- _gravity);
}

void ofxObjectBall::togglePose(){
    b_Pose = !b_Pose;
}
void ofxObjectBall::clearPose(){
    b_Pose = false;
}
void ofxObjectBall::setPose(){
    b_Pose = true;
}

void ofxObjectBall::startReplay(){
    i_ReplayCount = 1;
}
void ofxObjectBall::startReverse(){
    i_ReverseCount = 1;
}
void ofxObjectBall::clearHistory(){
    vv_RouteHistory.clear();
    i_ReplayCount = 0;
    i_ReverseCount = 0;
    i_NowHistoryPos = -1;
}

bool ofxObjectBall::isReversePlaying(){
    return (i_ReverseCount > 0);
}


//--------------------------------------------------------------
void ofxObjectBall::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    if(false and b_Slow and (t_Count %2 == 0)){
        ofTranslate(vf_Pos+vf_Speed/2.0);
        ofScale(0.02,0.02,0.02);
        ofRotateX(vf_Rotate[0]+vf_RotateSpeed[0]/2.0);
        ofRotateY(vf_Rotate[1]+vf_RotateSpeed[1]/2.0);
        ofRotateZ(vf_Rotate[2]+vf_RotateSpeed[2]/2.0);
    }else{
        ofTranslate(vf_Pos + vf_SlowShift);
        ofScale(0.02,0.02,0.02);
        ofRotateX(vf_Rotate[0]);
        ofRotateY(vf_Rotate[1]);
        ofRotateZ(vf_Rotate[2]);
    }
    ofNoFill();
    //ofDrawSphere(0, 0, 0, 240);
    ofTranslate(ofVec3f(0,250,0));
    model.drawFaces();
    ofPopStyle();
    ofPopMatrix();
}


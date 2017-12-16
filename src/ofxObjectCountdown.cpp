#include "ofxObjectCountdown.h"

//--------------------------------------------------------------
ofxObjectCountdown::ofxObjectCountdown(){
    t_Count = 0;
    b_End = false;
    
    
}
//--------------------------------------------------------------
bool ofxObjectCountdown::getEnd(){
    return b_End;
}

//--------------------------------------------------------------
void ofxObjectCountdown::update(){
    t_Count += 1;
    if(t_Count>60){
        b_End = true;
    }
}

//--------------------------------------------------------------
void ofxObjectCountdown::draw(){
    ofPushMatrix();
    if(t_Count < 4){
        ofTranslate(ofGetWidth()/3.0 - (4 - t_Count) * 250, ofGetHeight()/3.0);
    }else{
        ofTranslate(ofGetWidth()/3.0, ofGetHeight()/3.0);
    }
    if(t_Count > 8) ofTranslate((t_Count - 8) * 250, 0);
    image.draw(-image.getWidth()/2.0,-image.getHeight()/2.0);
    //image.draw(0,0);
    ofPopMatrix();
}


ofxObjectCountdowns::ofxObjectCountdowns(){
    ofImage buf1,buf2,buf3;
    buf1.load("1.png");
    buf2.load("2.png");
    buf3.load("3.png");
    v_Image.push_back(buf1);
    v_Image.push_back(buf2);
    v_Image.push_back(buf3);
    i_power = 0;
    for(int i =0; i<7; i++){
        vector<ofSoundPlayer> v_Sound;
        ofSoundPlayer s3;
        ofSoundPlayer s2;
        ofSoundPlayer s1;
        ofSoundPlayer s0;
        ofSoundPlayer sp;
        s3.load("sound/"+ofToString(i+1)+"/2nd_interaction_three_"+ofToString(i+1)+"th.wav");
        s2.load("sound/"+ofToString(i+1)+"/2nd_interaction_two_"+ofToString(i+1)+"th.wav");
        s1.load("sound/"+ofToString(i+1)+"/2nd_interaction_one_"+ofToString(i+1)+"th.wav");
        s0.load("sound/"+ofToString(i+1)+"/2nd_interaction_powerup_"+ofToString(i+1)+"th.wav");
        sp.load("sound/"+ofToString(i+1)+"/2nd_interaction_se_"+ofToString(i+1)+"th.wav");
        v_Sound.push_back(s0);
        v_Sound.push_back(s1);
        v_Sound.push_back(s2);
        v_Sound.push_back(s3);
        v_Sound.push_back(sp);
        vv_Sound.push_back(v_Sound);
    }
}

//--------------------------------------------------------------
void ofxObjectCountdowns::init(){
    i_power = 0;
}

int ofxObjectCountdowns::getPower(){
    return i_LimitPower;
}

void ofxObjectCountdowns::draw(){
    for(int i=0;i<v_Panel.size();i++){
        v_Panel[i].draw();
    }
}
void ofxObjectCountdowns::update(){
    for(int i=0;i<v_Panel.size();i++){
        v_Panel[i].update();
        if(v_Panel[i].getEnd()){
            v_Panel.erase(v_Panel.begin()+i);
        }
    }
}

void ofxObjectCountdowns::start(int countnum){
    ofxObjectCountdown buf;
    if(countnum>=1){
        buf.image = v_Image[countnum-1];
        v_Panel.push_back(buf);
        vv_Sound[i_power][4].play();
    }
    vv_Sound[i_power][countnum].play();
    if(countnum == 0){
        i_power ++;
        i_LimitPower = i_power;
        if (i_power == 7){
            i_power = 0;
        }
    }
}

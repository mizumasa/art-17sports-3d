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
    if(t_Count < 6){
        ofTranslate(ofGetWidth()/2.0 - (6 - t_Count) * 170, ofGetHeight()/3.0);
    }else{
        ofTranslate(ofGetWidth()/2.0, ofGetHeight()/3.0);
    }
    if(t_Count > 16) ofTranslate((t_Count - 16) * 170, 0);
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
    buf.image = v_Image[countnum];
    v_Panel.push_back(buf);
}

#include "ofxObjectHand.h"

ofxObjectHands::ofxObjectHands(){
    t_Count = 0;
    i_mode = 0;
    int bias = 30;
    vector<ofImage> buf;
    for(int i=0;i<30;i++){//120
        ofImage buf2;
        //buf2.load("hantokei/hantokei_0"+ofToString(i+2091+bias)+".png");
        buf2.load("L/L_0"+ofToString(i+1000+bias)+".png");
        buf.push_back(buf2);
    }
    vector<ofImage> buf3;
    vv_image.push_back(buf);
    for(int i=0;i<30;i++){//120
        ofImage buf4;
        //buf4.load("tokei/tokei_0"+ofToString(i+2211+bias)+".png");
        buf4.load("R/R_0"+ofToString(i+1000+bias)+".png");
        buf3.push_back(buf4);
    }
    vv_image.push_back(buf3);
}

void ofxObjectHands::play(int mode){
    i_mode = mode;
    t_Count = 1;
}
void ofxObjectHands::draw(){
    ofPushStyle();
    ofSetColor(255,255, 255, 128);
    if(t_Count>0){
        cout << "test"<<endl;
        vv_image[i_mode][t_Count-1].draw(0,0,ofGetWidth(),ofGetHeight());//(ofGetWidth()/3,ofGetHeight()/3,ofGetWidth()/3,ofGetHeight()/3);
    }
    ofPopStyle();
}

void ofxObjectHands::update(){
    if(t_Count > 0){
        t_Count += 1;
        if(t_Count > vv_image[i_mode].size()){
            t_Count = 0;
        }
    }
}


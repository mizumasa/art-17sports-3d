/*
 *
 */
#pragma once

#ifndef __ofAppLeft__
#define __ofAppLeft__

#include "ofMain.h"
#include "ofApp.h"

void ofApp::setupLeft(){
    i_BigSightMask.load(XML.getValue<string>("//LEFTMASK"));
    i_BigSightMask2.load(XML.getValue<string>("//LEFTMASK2"));
    if(XML.exists("LEFTVIDEO"))
    {
        XML.setTo("LEFTVIDEO[0]");
        do {
            if(XML.getName() == "LEFTVIDEO" && XML.setTo("VIDEO[0]")){
                do{
                    string buf = XML.getValue<string>("NAME");
                    cout << buf << endl;
                }
                while(XML.setToSibling()); // go the next PT
                XML.setToParent();
            }
        }
        while( XML.setToSibling() ); // go to the next STROKE
    }
    
    if(SCHEDULE.exists("LEFTSCHEDULE"))
    {
        SCHEDULE.setTo("LEFTSCHEDULE[0]");
        do {
            if(SCHEDULE.getName() == "LEFTSCHEDULE" && SCHEDULE.setTo("SEG[0]")){
                do{
                    int i_buf = SCHEDULE.getValue<int>("ACTMODE");
                    string buf = SCHEDULE.getValue<string>("NAME");
                    //cout << i_buf <<":"<< buf << endl;
                    ofxScheduleSeg segBuf;
                    segBuf.s_Name = buf;
                    segBuf.actMode = (ACT_MODE)(i_buf);
                    switch(i_buf){
                        case 0:
                            cout << "video load" << buf <<endl;
                            segBuf.video.load("movie/"+buf);
                            segBuf.video.setLoopState(OF_LOOP_NONE);
                            break;
                        case 1:
                            cout << "scene load" << buf << endl;
                            break;
                    }
                    v_ScheduleSeg.push_back(segBuf);
                }
                while(SCHEDULE.setToSibling()); // go the next PT
                SCHEDULE.setToParent();
            }
        }
        while( SCHEDULE.setToSibling() ); // go to the next STROKE
    }
    
}

void ofApp::updateLeft(){
    ofSetWindowTitle("Left:"+ofToString(ofGetFrameRate()));
}

void ofApp::drawLeft(){
    ofPushStyle();
    ofPushMatrix();
    ofPopMatrix();
    ofPopStyle();
}

#endif

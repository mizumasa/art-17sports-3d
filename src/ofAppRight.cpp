/*
 *
 */
#pragma once

#ifndef __ofAppRight__
#define __ofAppRight__

#include "ofMain.h"
#include "ofApp.h"

void ofApp::setupRight(){
    s_RightIP = XML.getValue<string>("//RIGHTIP");
    cout << "right mode:" << s_RightIP << endl;
    i_BigSightMask.load(XML.getValue<string>("//RIGHTMASK"));
    i_BigSightMask2.load(XML.getValue<string>("//RIGHTMASK2"));

    if(XML.exists("RIGHTVIDEO"))
    {
        XML.setTo("RIGHTVIDEO[0]");
        do {
            if(XML.getName() == "RIGHTVIDEO" && XML.setTo("VIDEO[0]")){
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
    
    if(SCHEDULE.exists("RIGHTSCHEDULE"))
    {
        SCHEDULE.setTo("RIGHTSCHEDULE[0]");
        do {
            if(SCHEDULE.getName() == "RIGHTSCHEDULE" && SCHEDULE.setTo("SEG[0]")){
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

void ofApp::updateRight(){
    ofSetWindowTitle("Right:"+ofToString(ofGetFrameRate()));
}

void ofApp::drawRight(){
    ofPushStyle();
    ofPushMatrix();
    ofPopMatrix();
    ofPopStyle();
}

#endif

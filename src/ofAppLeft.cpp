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
    
    
    //below cam
#ifdef USE_DETECTION

#ifdef _USE_LIVE_VIDEO
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(WEB_CAM_W,WEB_CAM_H);
#else
    movie.loadMovie("MAH00013.MP4");
    movie.setVolume(0.0);
    movie.play();
#endif
    
    colorImg.allocate(WEB_CAM_W,WEB_CAM_H);
    grayImage.allocate(WEB_CAM_W,WEB_CAM_H);
    
    detect.setup();
    perspective.setup();
    b_DrawImage=true;
    
#else
#endif
    
}

void ofApp::updateLeft(){
    ofSetWindowTitle("Left:"+ofToString(ofGetFrameRate()));
    
    
    //below cam
#ifdef USE_DETECTION

#ifdef _USE_LIVE_VIDEO
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){
        perspective.setPixels(vidGrabber.getPixels());
        perspective.update();
        
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg;
        if(b_DrawImage){
            //detect.setPixels(grayImage.getPixels());
            detect.setColorPixels(colorImg.getPixels());
        }else{
            detect.setColorPixels(perspective.getPixels());
        }
    }
#else
    movie.update();
    if(movie.isFrameNew()) {
        ofPixels movieBuf;
        movieBuf = movie.getPixels();
        movieBuf.resize(CAPTURE_W,CAPTURE_H);
        perspective.setPixels(movieBuf);
        perspective.update();
        
        colorImg.setFromPixels(movieBuf);
        grayImage = colorImg;
        if(b_DrawImage){
            //detect.setPixels(grayImage.getPixels());
            detect.setColorPixels(colorImg.getPixels());
        }else{
            detect.setColorPixels(perspective.getPixels());
        }
    }
#endif
    detect.update();
    
#else
#endif
    
}

void ofApp::drawLeft(){
    ofPushStyle();
    ofPushMatrix();
    ofPopMatrix();
    ofPopStyle();
    
    
#ifdef USE_DETECTION
    ofSetColor(255);
    detect.draw();
    if(b_DrawImage){
        perspective.draw();
    }
    if(!(detect.bHideGui)){
        string info = "";
        info += "space key draw binarized image\n";
        info += " d key toggle perspective or raw image\n";
        info += " ";
        ofSetColor(255,255,255);
        ofDrawBitmapString(info, 20,ofGetHeight()/2);
    }
#endif
    
}

#endif

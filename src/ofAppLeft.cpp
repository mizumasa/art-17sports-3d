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

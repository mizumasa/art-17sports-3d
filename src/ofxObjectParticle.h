#pragma once


#ifndef __ofxObjectParticle__
#define __ofxObjectParticle__

#include "ofMain.h"
#include "ofxSPK.h"

class ofxObjectRingParticle{
public:
    void setup();
    void update();
    void addPoint(ofVec3f _pos);
    void draw();
};

class ofxObjectParticle{
public:
	void setup();
	void update();
    void addMouse();
    void addPoint(ofVec3f _pos);
    void addPoint(int x,int y);
	void draw();
};
#endif  

#pragma once


#ifndef __ofxObjectParticle__
#define __ofxObjectParticle__

#include "ofMain.h"
#include "ofxSPK.h"

class ofxObjectParticle{
public:
	void setup();
	void update();
    void addMouse();
    void addPoint(int x,int y);
	void draw();
};
#endif  

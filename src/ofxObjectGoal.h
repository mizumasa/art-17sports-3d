/*
 *
 */
#pragma once

#ifndef __ofxObjectGoal__
#define __ofxObjectGoal__

#include "ofMain.h"
#include "common.h"
#include "ofxAssimpModelLoader.h"

class ofxObjectGoal{
public:
    ofxObjectGoal();
    void draw();
private:
    ofxAssimpModelLoader model;
};

#endif

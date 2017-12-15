#pragma once

#ifndef __ofxCommon__
#define __ofxCommon__

#include "ofMain.h"

#define GROUND_LEVEL -55
#define COURT_WIDTH_HALF 86
#define COURT_HEIGHT_HALF 142
#define GOAL_HEIGHT 40
//#define GOAL_Y_OFFSET 20
#define GOAL_Y_OFFSET 10

#define PORT 12345

#define OPENPOSE_RESIZE_RATE 0.1
#define OPENPOSE_CAP_HEIGHT 720
#define OPENPOSE_CAP_WIDTH 1280

#define FLY_TIME 30

//#define USE_DETECTION

enum ACT_MODE
{
    ACT_MODE_MOVIE = 0,
    ACT_MODE_CAPTURE = 1,
    ACT_MODE_CG = 2,
};

class ofxScheduleSeg{
public:
    ofxScheduleSeg();
    ACT_MODE actMode;
    int i_MovieId;
    string s_Name;
    ofVideoPlayer video;
private:
};

ofxScheduleSeg::ofxScheduleSeg(){
    s_Name = "none";
    i_MovieId = 0;
}

#endif


/*
 <SETTING>
 <RIGHTSCHEDULE>
 <SEG><ACTMODE>0</ACTMODE><NAME>1_R.mp4</NAME></SEG>
 <SEG><ACTMODE>2</ACTMODE><NAME>power gauge1</NAME></SEG>
 <SEG><ACTMODE>2</ACTMODE><NAME>fly cg fail right</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>3_R.mp4</NAME></SEG>
 <SEG><ACTMODE>2</ACTMODE><NAME>power gauge2</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>4_R.mp4</NAME></SEG>
 <SEG><ACTMODE>2</ACTMODE><NAME>fly cg right</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>5_R.mp4</NAME></SEG>
 <SEG><ACTMODE>2</ACTMODE><NAME>fly game</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>6_R.mp4</NAME></SEG>
 </RIGHTSCHEDULE>
 <LEFTSCHEDULE>
 <SEG><ACTMODE>0</ACTMODE><NAME>1_L.mp4</NAME></SEG>
 <SEG><ACTMODE>1</ACTMODE><NAME>audience1</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>2_L.mp4</NAME></SEG>
 <SEG><ACTMODE>2</ACTMODE><NAME>fly cg fail left</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>3_L.mp4</NAME></SEG>
 <SEG><ACTMODE>1</ACTMODE><NAME>audience2</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>4_L.mp4</NAME></SEG>
 <SEG><ACTMODE>2</ACTMODE><NAME>fly cg left</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>5_L.mp4</NAME></SEG>
 <SEG><ACTMODE>1</ACTMODE><NAME>fly game audience</NAME></SEG>
 <SEG><ACTMODE>0</ACTMODE><NAME>6_L.mp4</NAME></SEG>
 </LEFTSCHEDULE>
 </SETTING>
 */

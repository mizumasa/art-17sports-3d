#include "ofMain.h"
#include "ofApp.h"

#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
	ofGLWindowSettings s;
	//s.setGLVersion(3,2);
    //s.setGLVersion(2,1);

	ofCreateWindow(s);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}

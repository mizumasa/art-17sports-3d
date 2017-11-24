#include "ofxObjectParticle.h"

ofxSPK::System sys;
ofxSPK::Group group;

ofImage sprite;

ofxSPK::Modifier rot;

//--------------------------------------------------------------
void ofxObjectParticle::setup()
{
	// setup pointsprite texture
	// NOTES: the texture size must be Power of Two,
	// and turn off arb texture option while loading
	ofDisableArbTex();
	sprite.loadImage("image.jpg");
	ofEnableArbTex();
		
	sys.setup();
	
	group.setup(sys);
	group.setColor(ofxSPK::RangeC(ofColor(255, 255), ofColor(255, 255)),
				   ofxSPK::RangeC(ofColor(0, 0), ofColor(255, 0)));
	
	group.setLifeTime(0.5, 5);
	group.setFriction(0.1);
	group.setSize(0, ofxSPK::RangeF(30, 250));
	
	group.setGravity(ofVec3f(0, -10, 0));
	group.setMass(0.1, 1);
	
	rot.setup(SPK::Vortex::create(SPK::Vector3D(ofGetWidth()/2, ofGetHeight()/2),
								  SPK::Vector3D(0, 1, 0),
								  200,
								  10), group);
	
	group.reserve(10000);
}

//--------------------------------------------------------------
void ofxObjectParticle::update()
{
	sys.update();
}

void ofxObjectParticle::addMouse()
{
    group.emitRandom(2, ofVec3f(ofGetMouseX(), ofGetMouseY()));
}

void ofxObjectParticle::addPoint(int x,int y){
    group.emitRandom(2, ofVec3f(x, y));
    sys.update();
}


//--------------------------------------------------------------
void ofxObjectParticle::draw()
{
    ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	// sys.debugDraw();
    sprite.bind();
	ofEnablePointSprites();
	sys.draw();
	ofDisablePointSprites();
	sprite.unbind();
}

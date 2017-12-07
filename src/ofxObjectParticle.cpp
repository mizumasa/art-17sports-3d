#include "ofxObjectParticle.h"

ofxSPK::System sys2;
ofxSPK::Group group2;
ofImage sprite2;
ofxSPK::Modifier rot2;

//--------------------------------------------------------------
void ofxObjectRingParticle::setup()
{
    ofDisableArbTex();
    sprite2.loadImage("image.jpg");
    ofEnableArbTex();
    
    sys2.setup();
    
    group2.setup(sys2);
    group2.setColor(ofxSPK::RangeC(ofColor(255, 255), ofColor(255, 255)),
                   ofxSPK::RangeC(ofColor(0, 0), ofColor(255, 0)));
    
    group2.setLifeTime(0.5, 2);
    group2.setFriction(0.1);
    group2.setSize(0, ofxSPK::RangeF(5, 20));
    
    group2.setGravity(ofVec3f(0, 0, 0));
    group2.setMass(1.0, 2.0);
    
    group2.reserve(300);
}

//--------------------------------------------------------------
void ofxObjectRingParticle::update()
{
    sys2.update();
}

void ofxObjectRingParticle::addPoint(ofVec3f _pos){
    group2.emitRandom(2, _pos);
}

//--------------------------------------------------------------
void ofxObjectRingParticle::draw()
{
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    sprite2.bind();
    ofEnablePointSprites();
    sys2.draw();
    ofDisablePointSprites();
    sprite2.unbind();
}


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
	
	group.setLifeTime(0.5, 2);
	group.setFriction(0.1);
	group.setSize(0, ofxSPK::RangeF(10, 50));
	
	//group.setGravity(ofVec3f(0, -10, 0));
    group.setGravity(ofVec3f(0, 0, 0));
    group.setMass(0.1, 1);
	
	/*rot.setup(SPK::Vortex::create(SPK::Vector3D(ofGetWidth()/2, ofGetHeight()/2),
								  SPK::Vector3D(0, 1, 0),
								  200,
								  10), group);
	*/
    
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

void ofxObjectParticle::addPoint(ofVec3f _pos){
    group.emitRandom(2, _pos);
}

void ofxObjectParticle::addPoint(int x,int y){
    group.emitRandom(20, ofVec3f(x, y));
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

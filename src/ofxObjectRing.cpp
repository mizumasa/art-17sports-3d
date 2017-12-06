#include "ofxObjectRing.h"
#define RING_NUM 5

float ring_path[RING_NUM][5] = {
    {0, -55.2976, -8.97785, 0.37362, 0.244777},
    {0, -8.59513, 16.1068, 0.37362, 0.157278},
    {0, 38.1074, 30.2541, 0.37362, 0.0697781},
    {0, 84.8098, 33.4639, 0.37362, -0.0177219},
    {0, 131.512, 25.7361, 0.37362, -0.105222}
};

/*
 {0, -79.5829, -26.3444, 0.37362, 0.290277},
 {0, -34.7486, 3.4069, 0.37362, 0.206277},
 {0, 10.0859, 23.0783, 0.37362, 0.122278},
 {0, 54.9203, 32.6696, 0.37362, 0.0382781},
 {0, 99.7546, 32.181, 0.37362, -0.0457219},
 {0, 122.172, 28.1566, 0.37362, -0.0877219}
*/

/*
    {0, -59.3639, -16.5083, 0.7106, 0.415862},//posx , posy ,posz , speedy,speedz
    {0, -16.728, 4.78347, 0.7106, 0.295862},
    {0, 25.908, 18.8752, 0.7106, 0.175862},
    {0, 68.5439, 25.7669, 0.7106, 0.0558618},
    {0, 111.18, 25.4586, 0.7106, -0.0641382}
    //{0, 134.42, 19.1674}
};*/
/*
    {0, -87.835, -40.0654},
    {0, -59.5048, -30.1963},
    {0, -31.1745, -20.3271},
    {0, -2.84435, -10.458},
    {0, 25.4858, -0.58882},
    {0, 53.8161, 9.28031},
    {0, 82.1463, 19.1495},
    {0, 110.476, 29.0186}
};*/

//--------------------------------------------------------------
ofxObjectRings::ofxObjectRings(){
    for(int i=0; i<RING_NUM ;i++){
        add(ofVec3f(ring_path[i][0],ring_path[i][1],ring_path[i][2]));
        vf_Object[vf_Object.size()-1].setRotate(atan2(ring_path[i][4], ring_path[i][3]));
    }
}

//--------------------------------------------------------------
void ofxObjectRings::init(){
    for(int i=0;i<vf_Object.size();i++){
        vf_Object[i].b_Finished = false;
    }
}

//--------------------------------------------------------------
void ofxObjectRings::update(float ballPosY){
    for(int i=0;i<vf_Object.size();i++){
        vf_Object[i].update(ballPosY);
        /*if(vf_Object[i].isEnd()){
            vf_Object.erase(vf_Object.begin() + i);
        }*/
    }
}


//--------------------------------------------------------------
void ofxObjectRings::draw(){
    bool buf;
    buf = ofGetLightingEnabled();
    if(buf)ofDisableLighting();
    ofGetLightingEnabled();
    for(int i=0;i<vf_Object.size();i++){
        vf_Object[i].draw();
    }
    if(buf)ofEnableLighting();
}
//--------------------------------------------------------------
void ofxObjectRings::add(ofVec3f _vf_pos){
    ofxObjectRing buf(_vf_pos);
    vf_Object.push_back(buf);
}




//--------------------------------------------------------------
ofxObjectRing::ofxObjectRing(ofVec3f _vf_Pos){
    vf_Pos = _vf_Pos;
    b_Finished = false;
    i_Count = 0;
}

//--------------------------------------------------------------
void ofxObjectRing::update(float ballPosY){
    i_Count += 1;
    if(vf_Pos[1]<ballPosY){
        b_Finished = true;
    }
    /*if(i_Count > 30){
        b_Finished = true;
    }*/
}

void ofxObjectRing::setSpeed(){
}

bool ofxObjectRing::isEnd(){
    return b_Finished;
}

void ofxObjectRing::setRotate(float _angle){
    f_angle = _angle;
}


//--------------------------------------------------------------
void ofxObjectRing::draw(){
    if(!b_Finished){
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(255, 255, 255, 190);
        ofSetCircleResolution(200);
        ofSetLineWidth(6.0);
        ofTranslate(vf_Pos);
        ofNoFill();
        ofRotateX(90+ 180 * f_angle / PI);
        ofDrawCircle(0,0,0,10);
        /*ofDrawCircle(0,0,0,i_Count);
         if(i_Count>10){
         ofDrawCircle(0,0,0,i_Count-10);
         }*/
        ofPopStyle();
        ofPopMatrix();
    }
}


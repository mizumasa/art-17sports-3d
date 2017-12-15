#include "ofxBGM.h"

#define FO_TIME 60
#define DOWN_TIME 10
#define UP_TIME 10

ofxObjectBGM::ofxObjectBGM(){
    t_Count = 0;
}

void ofxObjectBGM::play(){
    bgm.play();
    bgm.setVolume(1.0);
    i_FoCount = 0;
    i_DownCount = 0;
    i_UpCount = 0;
}
void ofxObjectBGM::update(){
    t_Count += 1;
    if(i_FoCount > 0){
        i_FoCount ++;
        bgm.setVolume( 1.0 * (FO_TIME - i_FoCount) / FO_TIME);
        //cout << bgm.getVolume()<<endl;
        if(i_FoCount >= FO_TIME){
            i_FoCount=0;
            bgm.stop();
        }
    }
    if(i_DownCount > 0){
        i_DownCount ++;
        bgm.setVolume( 0.5 + 0.5 * (DOWN_TIME - i_DownCount) / DOWN_TIME);
        if(i_DownCount >= DOWN_TIME){
            i_DownCount=0;
        }
    }
    if(i_UpCount > 0){
        i_UpCount ++;
        bgm.setVolume( 0.5 + 0.5 * (i_UpCount) / UP_TIME);
        if(i_UpCount >= UP_TIME){
            i_UpCount=0;
        }
    }
}

void ofxObjectBGM::setFo(){
    cout << "setFo"<<bgm.getVolume()<<endl;
    i_FoCount = 1;
}
void ofxObjectBGM::setDown(){
    i_DownCount = 1;
}
void ofxObjectBGM::setUp(){
    i_UpCount = 1;
}


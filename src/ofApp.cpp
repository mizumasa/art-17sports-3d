#include "ofApp.h"

/* simple model space
     ^ tilt+
     |
     z+  y+
     |  /        . ->pan+
     | /     .
     |/  .
 *C  *--------x+
 cameraPos(0,-300,300), lookAt((0,0,0),up=(0,0,1))
   /
  /
 /
 y-
 */
//--------------------------------------------------------------
void ofApp::setup(){
    i_SceneID = 1;
    b_Render = false;
    i_Camera = 0;
    i_test = 0;
    
    b_TestLight = true;
    
	ofEnableLighting();
	ofEnableDepthTest();

    ofSetSmoothLighting(true);

    testLight.setup();
    testLight.disable();
    testLight.setPointLight();
    //testLight.setAreaLight(1000, 1000);
    //testLight.setSpotlight(100,10);
    
    ///testLight.setAmbientColor(ofFloatColor(1.0,0.2,0.2));
    //testLight.setAttenuation(1.0,1.0,1.0);
    //testLight.setDiffuseColor(ofFloatColor(0.5,0.5,0.5));
    testLight.setSpecularColor(ofFloatColor(1.0f, 0.0f, 0.0f));
    testLight.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
    //testLight.lookAt(ofVec3f(0,0,0));
    
    
	areaLight.setup();
	areaLight.enable();
	//areaLight.setSpotlight(15,1000000);
    //areaLight.setSpotlight(5,0);
    areaLight.setSpotlight(180,1);
    
    areaLight.setAmbientColor(ofFloatColor(0,0,0));
	//areaLight.setAttenuation(1.0,1.0,1.0);
	areaLight.setDiffuseColor(ofFloatColor(0.01,0.01,0.01));
    //areaLight.setDiffuseColor(ofFloatColor(0.0,0.0,0.0));
    areaLight.setSpecularColor(ofFloatColor(1,1,1));
	areaLight.setPosition(0,-RADIUS,0);
    areaLight.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
	
    plane.set(400,400,2,2);
	plane.rotate(-90,ofVec3f(1,0,0));
	plane.move(ofVec3f(0,-300,0));
	
    //materialPlane.setAmbientColor(ofFloatColor(0,0,0,1.0));
	//materialPlane.setDiffuseColor(ofFloatColor(0.1,0.1,0.1,1.0));
	//materialPlane.setSpecularColor(ofFloatColor(1.0,1.0,1.0,1.0));
    //materialPlane.setShininess(100000);
    materialPlane.setAmbientColor(ofFloatColor(0,0,0,0.0));
    materialPlane.setDiffuseColor(ofFloatColor(0.0,0.0,0.0,0.0));
    materialPlane.setSpecularColor(ofFloatColor(0.0,0.0,0.0,0.0));
    materialPlane.setShininess(100000);
    
    materialPlaneBlack.setAmbientColor(ofFloatColor(0.4,0.4,0.4,0.0));
    materialPlaneBlack.setDiffuseColor(ofFloatColor(0.0,0.0,0.0,0.0));
    materialPlaneBlack.setSpecularColor(ofFloatColor(0,0,0,0));
    materialPlaneBlack.setShininess(0);
    
    
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(0, 0,0);
        camBuf.setDistance(1.0);
        camBuf.move(-200, -300, 0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(70);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(50);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        //camBuf.enableOrtho();
        camBuf.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(50);
        //camBuf.setNearClip(0);
        camBuf.setFarClip(20000);
        camBuf.setAutoMove();
        v_Camera.push_back(camBuf);
    }

    
    for(int i = -MIR_X_NUM ;i<=MIR_X_NUM ;i++){
        for(int j = 0 ;j<=MIR_Y_NUM ;j++){
            ofxObjectMirror bufMirror;
            bufMirror.setPos(i*MIR_X_ANG, j*MIR_Y_ANG, RADIUS);
            v_ObjectMirror.push_back(bufMirror);
        }
    }
    
    for(int i = -(MIR_X_NUM/2) ;i<=(MIR_X_NUM/2) ;i++){
        for(int j = 1 ;j<=(MIR_Y_NUM/2) ;j++){
            ofxObjectHuman bufHuman;
            bufHuman.setPos(180+i*MIR_X_ANG, -j*MIR_Y_ANG, RADIUS);
            v_ObjectHuman.push_back(bufHuman);
        }
    }

    for(int i = -(MIR_X_NUM/2) ;i<=(MIR_X_NUM/2) ;i++){
        for(int j = 0 ;j<=(MIR_Y_NUM/2) ;j++){
            ofxObjectLight bufLight;
            bufLight.setPos(180+i*MIR_X_ANG, j*MIR_Y_ANG, RADIUS);
            v_ObjectLight.push_back(bufLight);
        }
    }
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].setAngleBetween(v_ObjectLight[4].getPos(), v_Camera[0].getPosition());
    }
    
    ofSetCylinderResolution(24, 1);
    
    
    //model.loadModel("020512_stadium.stl");
    model.loadModel("020512_stadium.3DS");
    imgCourt.load("groundc.jpg");
    
    //FboBlur
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    s.maxFilter = GL_LINEAR; GL_NEAREST;
    s.numSamples = 0;
    s.numColorbuffers = 1;
    s.useDepth = false;
    s.useStencil = false;
    gpuBlur.setup(s, false);

    gui.setup();
    gui.add(pi_AngleSpeed.setup("Angle Speed", 5, 1, 10));
    gui.add(pf_Buf1.setup("pf_Buf1", 10, -100.0, 100.0));
    gui.add(pf_Buf2.setup("pf_Buf2", 10, -100.0, 100.0));
    gui.add(pf_Buf3.setup("pf_Buf3", 1, 1, 100.0));
    gui.add(pf_Buf4.setup("pf_Buf4", 1, 1, 100.0));
    gui.add(pf_Buf5.setup("pf_Buf5", 1, 1, 100.0));
    gui.add(pf_Buf6.setup("pf_Buf6", 1, 0.01, 10.0));
    b_GuiDraw = false;
    
    gpuBlur.blurOffset = 24;
    gpuBlur.blurPasses = 9.5;
    gpuBlur.numBlurOverlays = 1;
    gpuBlur.blurOverlayGain = 255;
    
    if(USE_BLACKMAGIC){
        cam.setup(BLACKMAGIC_W, BLACKMAGIC_H, 30);
    }else{
        camMac.setDeviceID(0);
        camMac.setDesiredFrameRate(60);
        camMac.initGrabber(WEBCAM_W, WEBCAM_H);
    }
    b_CamStart = false;

}

//--------------------------------------------------------------
void ofApp::update(){
	//areaLight.setPosition(0,-200,0);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].update(pi_AngleSpeed);
    }
    for(int i = 0; i<v_ObjectHuman.size(); i++){
        v_ObjectHuman[i].update(pi_AngleSpeed);
    }
    for(int i = 0; i<v_ObjectLight.size(); i++){
        v_ObjectLight[i].update(pi_AngleSpeed);
    }
    for(int i = 0; i<v_Camera.size(); i++){
        v_Camera[i].update();
    }
    if(b_UpdateFbo){
        b_UpdateFbo = false;
        ofFbo::Settings s;
        s.width = ofGetWidth();
        s.height = ofGetHeight();
        s.internalformat = GL_RGBA;
        s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
        s.maxFilter = GL_LINEAR; GL_NEAREST;
        s.numSamples = 0;
        s.numColorbuffers = 1;
        s.useDepth = false;
        s.useStencil = false;
        gpuBlur.setup(s, false);
    }
    
    
    modelBall.update();
    objectEffect.update();

    if(USE_BLACKMAGIC){
        if(cam.update()){
            timer.tick();
            b_CamStart=true;
            camPixels=cam.getColorPixels();
            camImg.setFromPixels(camPixels.getData(), BLACKMAGIC_W, BLACKMAGIC_H, OF_IMAGE_COLOR_ALPHA);
        }
    }else{
        camMac.update();
        b_CamStart=true;
        camPixels = camMac.getPixels();
        camPixels.resize( BLACKMAGIC_W, BLACKMAGIC_H);
        camImg.setFromPixels(camPixels.getData(), BLACKMAGIC_W, BLACKMAGIC_H, OF_IMAGE_COLOR);
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    switch(i_SceneID){
        case 1:
            draw3D();
            break;
        case 2:
            drawInput();
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::drawInput(){
    ofBackground(0,0,0);
    if(b_CamStart){
        ofPushStyle();
        ofPushMatrix();
        int drawHeight;
        drawHeight = int(ofGetWidth()*camImg.getHeight()/camImg.getWidth());
        camImg.draw(0,int((ofGetHeight()-drawHeight)/2),-2, ofGetWidth(), drawHeight);
        ofPushMatrix();
        ofPushStyle();
    }
}

//--------------------------------------------------------------
void ofApp::draw3D(){
    ofPushStyle();
    ofEnableAlphaBlending();
    ofEnableLighting();
    ofEnableDepthTest();

    float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 10, true);

    ofBackground(0,0,0);
    

    v_Camera[i_Camera].begin();
    
    if(b_TestLight){
        testLight.enable();
        areaLight.disable();
    }else{
        testLight.disable();
        areaLight.enable();
    }
    
    if(b_Render){
        materialPlane.begin();
    }else{
        materialPlaneBlack.begin();
    }
    
    ofPushMatrix();
    {
        //ofScale(1.0,1.0,1.0);
        {
            testLight.disable();
            areaLight.disable();
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(4.5, 0,0);
            ofRotateX(-90);
            ofSetColor(128, 128, 128, 128);
            model.drawFaces();
            ofPopMatrix();
            ofPopStyle();

            if(b_TestLight){
                testLight.enable();
                areaLight.disable();
            }else{
                testLight.disable();
                areaLight.enable();
            }

        }
        {
            ofPushMatrix();
            modelGoal.draw();
            ofPopMatrix();
        }
        {
            ofPushMatrix();
            modelBall.draw();
            ofPopMatrix();
        }
        {
            ofPushMatrix();
            ofTranslate(0, 0,GROUND_LEVEL);
            camImg.draw(-COURT_WIDTH_HALF, -COURT_HEIGHT_HALF, COURT_WIDTH_HALF*2, 2*COURT_HEIGHT_HALF);
            ofSetColor(128, 128, 128, 128);
            ofTranslate(0, 0, 1);
            imgCourt.draw(-COURT_WIDTH_HALF, -COURT_HEIGHT_HALF, COURT_WIDTH_HALF*2, 2*COURT_HEIGHT_HALF);
            ofPopMatrix();
        }
    }
    ofPopMatrix();


    
    
    if(b_Render){
        materialPlane.end();
    }else{
        materialPlaneBlack.end();
    }
    
    for(int i = 0; i<v_ObjectLight.size(); i++){
        v_ObjectLight[i].draw();
    }
    
	if(!b_TestLight)areaLight.draw();
    if(b_TestLight)testLight.draw();

 
#if 0
    for(int i=0;i<v_Camera.size();i++){
        ofSetColor(255,0,0);
        ofPushStyle();
        ofPushMatrix();
        ofDisableLighting();
        ofMatrix4x4 inverseCameraMatrix;
        inverseCameraMatrix.makeInvertOf(v_Camera[i].getModelViewProjectionMatrix());
        ofMultMatrix( inverseCameraMatrix );
        ofPoint scale2(0.9,0.9,0.9);
        ofScale(scale2);
        ofNoFill();
        ofDrawBox(0, 0, 0, 2.0f);
        ofEnableLighting();
        ofPopMatrix();
        ofPopStyle();
    }
#endif

    
    v_Camera[i_Camera].end();
    
    ofPopStyle();

    
    ofSetColor(255, 255, 255,255);//this color is applied to gpuBlur.beginDrawScene();

    if(b_GuiDraw){
        ofPushStyle();
        ofDisableLighting();
        ofDisableDepthTest();
        ofSetColor(255, 255, 255,255);
        gui.draw();
        ofPopStyle();
        ofSetColor(255, 255, 255,255);
        string msg;
        msg = ofToString(ofGetFrameRate());
        ofDrawBitmapString(msg, 200, 20);
    }else{
        gpuBlur.beginDrawScene();
        ofClear(0, 0, 0, 0);
        
        v_Camera[i_Camera].begin();
        ofSetColor(255, 255, 255,255);
        for(int i = 0; i<v_ObjectMirror.size(); i++){
            v_ObjectMirror[i].drawLineTo(v_ObjectLight[4].getPos());
            //v_ObjectMirror[i].drawLineTo(v_ObjectLight[7].getPos());
        }
        objectEffect.draw();
        v_Camera[i_Camera].end();
        
        gpuBlur.endDrawScene();
        gpuBlur.performBlur();
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
        gpuBlur.drawBlurFbo();

    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
        case 'e':
            objectEffect.add(ofVec3f(ofRandom(-80,80),ofRandom(-120,100),GROUND_LEVEL));
            break;
        case 't':
            b_TestLight = !b_TestLight;
            break;
        case 'r':
            b_Render = !b_Render;
            break;
        case 'f':
            ofToggleFullscreen();
            b_UpdateFbo = true;
            break;
        case 'g':
            b_GuiDraw = !b_GuiDraw;
            break;
        case 'j':
            //modelBall.setSpeed(ofVec3f(0,0,5));
            modelBall.throwTo(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT),20);
            break;
        case OF_KEY_UP:
            for(int i = 0; i<v_ObjectMirror.size(); i++){
                v_ObjectMirror[i].setRandomAngle();
            }
            break;
        case OF_KEY_DOWN:
            break;
        case OF_KEY_LEFT:
            break;
        case OF_KEY_RIGHT:
            break;
            
        case '1':
            i_SceneID = 1;
            break;
        case '2':
            i_SceneID = 2;
            break;
        case '3':
            i_SceneID = 3;
            break;
        case '4':
            i_SceneID = 4;
            break;

        case '0':
            i_test += 1;
            break;
        case '9':
            i_test -= 1;
            break;
        case 'c':
            //b_Camera = !b_Camera;
            i_Camera = (i_Camera +1)%3;
            for(int i = 0;i<v_Camera.size();i++){
                if(i_Camera == i){
                    v_Camera[i].enableMouseInput();
                }else{
                    v_Camera[i].disableMouseInput();
                }
            }
            break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::exit(){
    if(USE_BLACKMAGIC){
        cam.close();
    }
}

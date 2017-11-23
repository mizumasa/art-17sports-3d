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
    
    b_TestLight = false;
    
	ofEnableLighting();
	ofEnableDepthTest();

    ofSetSmoothLighting(true);

    ballLight.setup();
    ballLight.setAmbientColor(ofFloatColor(0.1,0.1,1.0,1.0));
    ballLight.setDiffuseColor(ofFloatColor(0.4,0.4,1.0));
    ballLight.setSpecularColor(ofFloatColor(0.0f, 0.0f, 1.0f));
    ballLight.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);

    testLight.setup();
    testLight.disable();
    testLight.setPointLight();
    //testLight.setAreaLight(1000, 1000);
    //testLight.setSpotlight(100,10);
    
    ///testLight.setAmbientColor(ofFloatColor(1.0,0.2,0.2));
    //testLight.setAttenuation(1.0,1.0,1.0);
    //testLight.setDiffuseColor(ofFloatColor(0.5,0.5,0.5));
    testLight.setAmbientColor(ofFloatColor(1.0,1.0,1.0,1.0));
    testLight.setDiffuseColor(ofFloatColor(1.0,1.0,1.0));
    testLight.setSpecularColor(ofFloatColor(1.0f, 1.0f, 1.0f));
    testLight.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
    //testLight.lookAt(ofVec3f(0,0,0));
    
    
	areaLight.setup();
	areaLight.enable();
	//areaLight.setSpotlight(15,1000000);
    //areaLight.setSpotlight(5,0);
    areaLight.setSpotlight(180,1);
    
    areaLight.setAmbientColor(ofFloatColor(0.01,0.01,0.01,1.0));
	//areaLight.setAttenuation(1.0,1.0,1.0);
	areaLight.setDiffuseColor(ofFloatColor(0.2,0.2,0.2));
    //areaLight.setDiffuseColor(ofFloatColor(0.0,0.0,0.0));
    areaLight.setSpecularColor(ofFloatColor(0.4,0.4,0.4));
	areaLight.setPosition(RADIUS,-RADIUS,0);
    areaLight.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
	
    plane.set(400,400,2,2);
	plane.rotate(-90,ofVec3f(1,0,0));
	plane.move(ofVec3f(0,-300,0));
	
    materialPlane.setAmbientColor(ofFloatColor(0.2,0.2,0.2,1.0));
	materialPlane.setDiffuseColor(ofFloatColor(0.1,0.1,0.1,1.0));
	materialPlane.setSpecularColor(ofFloatColor(1.0,1.0,1.0,1.0));
    materialPlane.setShininess(100000);
    //materialPlane.setAmbientColor(ofFloatColor(0,0,0,0.0));
    //materialPlane.setDiffuseColor(ofFloatColor(0.0,0.0,0.0,0.0));
    //materialPlane.setSpecularColor(ofFloatColor(0.0,0.0,0.0,0.0));
    //materialPlane.setShininess(100000);
    
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
        camBuf.setPosition(0,0,GOAL_HEIGHT);
        camBuf.setDistance(GOAL_HEIGHT);
        camBuf.lookAt(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT), ofVec3f(0,0,1));
        camBuf.setFov(50);
        //camBuf.setNearClip(0);
        camBuf.setFarClip(20000);
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
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(0, -RADIUS,0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(50);
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
            bufLight.disable();
            bufLight.setPos(180+i*MIR_X_ANG, j*MIR_Y_ANG, RADIUS);
            bufLight.setAngle(i*MIR_X_ANG, -j*MIR_Y_ANG);
            v_ObjectLight.push_back(bufLight);
        }
    }
    for(int i = 0;i<4 ;i++){
        ofxObjectLight bufLight;
        bufLight.disable();
        bufLight.setPos(180, 0, 100);
        bufLight.setAngle(0, 0);
        v_ObjectLight2.push_back(bufLight);
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
    modelGoalBall.noGravity();
    modelGoalBall.setGoalLoop();
    receiver.setup(PORT);
    
    ballParticle.setup();
    
    
    //Gritch
    lenna.loadImage("lenna.png");
    bDrawLenna = false;
    bShowHelp  = true;
    myFbo.allocate(512, 512);
    myGlitch.setup(&myFbo);
    
}

//update--------------------------------------------------------------
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
        if(i==4){
            ofVec3f ballPos;
            ballPos = modelBall.getPos();
            v_Camera[i].setPosition(ballPos+ofVec3f(0, -100,100));
            v_Camera[i].lookAt(ballPos+ofVec3f(0, 0,0), ofVec3f(0,0,1));
        }
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
    if(b_BallColor){
        ballLight.setAmbientColor(ofFloatColor(0.1,sin(ofGetElapsedTimeMillis()/100.0)/2+0.5,cos(ofGetElapsedTimeMillis()/100.0)/2+0.5,1.0));
        ballLight.setDiffuseColor(ofFloatColor(0.1,sin(ofGetElapsedTimeMillis()/100.0)/2+0.5,cos(ofGetElapsedTimeMillis()/100.0)/2+0.5,1.0));
        ballLight.setSpecularColor(ofFloatColor(0.0f,sin(ofGetElapsedTimeMillis()/100.0)/2+0.5,cos(ofGetElapsedTimeMillis()/100.0)/2+0.5));
    }else{
        ballLight.setAmbientColor(ofFloatColor(0.1,0.1,1.0,1.0));
        ballLight.setDiffuseColor(ofFloatColor(0.4,0.4,1.0));
        ballLight.setSpecularColor(ofFloatColor(0.0f, 0.0f, 1.0f));
    }
    modelGoalBall.update();
    objectEffect.update();

    ballParticle.update();

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

    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if(m.getAddress() == "/mouse/position"){
            int recX,recY;
            recX = m.getArgAsInt32(0);
            recY = m.getArgAsInt32(1);
            cout << recX << ":"<< recY << endl;
        }
        if(m.getAddress() == "/start"){
            int recX;
            recX = m.getArgAsInt32(0);
            cout << "OSC start" << recX << endl;
        }
        if(m.getAddress() == "/update"){
            int recX;
            recX = m.getArgAsInt32(0);
            cout << m.getAddress() << recX << endl;
        }
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
    /*if(b_TitleShakeManual){
        myFbo.begin();
    }*/
    ofDisableLighting();
    ofDisableDepthTest();

    ofSetColor(255,255,255);

    ofBackground(0,0,0);
    if(b_CamStart){
        ofPushStyle();
        ofPushMatrix();
        int drawHeight;
        drawHeight = int(ofGetWidth()*camImg.getHeight()/camImg.getWidth());
        camImg.draw(0,int((ofGetHeight()-drawHeight)/2),-2, ofGetWidth(), drawHeight);
        ofPopMatrix();
        ofPopStyle();
    }
    
    myFbo.begin();
    ofClear(0, 0, 0,255);
    if (!bDrawLenna){
        for (int i = 0;i < 100;i++){
            if        (i % 5 == 0)ofSetColor(50 , 255, 100);
            else if (i % 9 == 0)ofSetColor(255, 50, 100);
            else                ofSetColor(255, 255, 255);
            
            ofPushMatrix();
            ofRotate(ofGetFrameNum(), 1.0, 1.0, 1.0);
            ofTranslate((ofNoise(i/2.4)-0.5)*1000,
                        (ofNoise(i/5.6)-0.5)*1000,
                        (ofNoise(i/8.2)-0.5)*1000);
            ofCircle(0, 0, (ofNoise(i/3.4)-0.5)*100+ofRandom(3));
            ofPopMatrix();
        }
    }else{
        ofSetColor(255);
        int drawHeight;
        drawHeight = int(ofGetWidth()*camImg.getHeight()/camImg.getWidth());
        camImg.draw(0,int((ofGetHeight()-drawHeight)/2),-2, ofGetWidth(), drawHeight);
    }
    myFbo.end();

    ofSetColor(255);
    myFbo.draw(0, 0);
    
    /* Apply effects */
    myGlitch.generateFx();
    
    /* draw effected view */
    ofSetColor(255);
    myFbo.draw(512, 0);
    
    
    /* show information*/
    string info = "";
    info += "1 - 0 : Apply glitch effects.\n";
    info += "q - u : Apply color remap effects.\n";
    info += "L key : Switch 3Dview / 2DImage.\n";
    info += "H key : Hide or show this information.";
    
    if (bShowHelp){
        ofSetColor(0, 200);
        ofRect(25, 17, 320, 60);
        ofSetColor(255);
        ofDrawBitmapString(info, 30,30);
    }

    /*if(b_TitleShakeManual){
        myFbo.end();
        myGlitch.generateFx();
        myFbo.draw(0, 0);
    }*/
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
            //testLight.disable();
            //areaLight.disable();

            ofPushStyle();
            ofPushMatrix();
            ofTranslate(4.5, 0,0);
            ofRotateX(-90);
            ofSetColor(0, 0, 0, 128);
            model.drawFaces();
            ofPopMatrix();
            ofPopStyle();

            /*if(b_TestLight){
                testLight.enable();
                areaLight.disable();
            }else{
                testLight.disable();
                areaLight.enable();
            }*/

        }
        {
            ofPushMatrix();
            modelGoal.draw();
            ofPopMatrix();
        }
        {
            ofPushMatrix();
            
            
            testLight.disable();
            areaLight.disable();
            ballLight.enable();
            if(i_Camera==2){
                //ofTranslate(0,pf_Buf6 * (pf_Buf3+pf_Buf4),pf_Buf6*pf_Buf5);
                modelGoalBall.draw();
            }else{
                modelBall.draw();
            }
            ballLight.disable();

            if(b_TestLight)testLight.enable();
            if(!b_TestLight)areaLight.enable();
            
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
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2,100);
    ofDisableDepthTest();
    ballParticle.draw();
    ofPopMatrix();
    ofPopStyle();
    

    
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
        if(0){
            for(int i = 0; i<v_ObjectLight.size(); i++){
                v_ObjectLight[i].drawLineDirMulti(v_ObjectLight[i].getNorm()*800);
            }
        }
        for(int i = 0; i<v_ObjectLight2.size(); i++){
            ofPushMatrix();
            ofTranslate((i%2)*200-100, int(i/2)*300-150);
            ofRotateZ(int(i/2)*180.0);
            if(i==1 or i==2){
                ofRotateZ(20.0);
            }else{
                ofRotateZ(-20.0);
            }
            ofRotateX(-20.0);
            v_ObjectLight2[i].drawLineDirMulti(v_ObjectLight2[i].getNorm()*250);
            ofPopMatrix();
        }

        /*for(int i = 0; i<v_ObjectLight.size(); i++){
            for(int j = 0; j<v_ObjectMirror.size(); j++){
                v_ObjectMirror[j].drawLineTo(v_ObjectLight[i].getPos());
                //v_ObjectLight[i].drawLineDirMulti(v_ObjectLight[i].getNorm()*100);
            }
        }*/
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
        /*case '3':
            i_SceneID = 3;
            break;
        case '4':
            i_SceneID = 4;
            break;
         */
        case '0':
            i_test += 1;
            break;
        case '9':
            i_test -= 1;
            break;
        case 'c':
            //b_Camera = !b_Camera;
            i_Camera = (i_Camera +1)%v_Camera.size();
            for(int i = 0;i<v_Camera.size();i++){
                if(i_Camera == i){
                    v_Camera[i].enableMouseInput();
                }else{
                    v_Camera[i].disableMouseInput();
                }
            }
            break;
        case 'b':
            b_BallColor = !b_BallColor;
            break;
	}
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE    , true);
    if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW            , true);
    if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER            , true);
    if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER        , true);
    if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST            , true);
    if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE        , true);
    if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE            , true);
    if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN        , true);
    if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL            , true);
    if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT            , true);
    
    if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
    if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE    , true);
    if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE    , true);
    if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE    , true);
    if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT    , true);
    if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT    , true);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT    , true);
    
    if (key == 'l') bDrawLenna ^= true;
    if (key == 'h') bShowHelp ^= true;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE    , false);
    if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW            , false);
    if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER            , false);
    if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER        , false);
    if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST            , false);
    if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE        , false);
    if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE            , false);
    if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN        , false);
    if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL            , false);
    if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT            , false);
    
    if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
    if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE    , false);
    if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE    , false);
    if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE    , false);
    if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT    , false);
    if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT    , false);
    if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT    , false);

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

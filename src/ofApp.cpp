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
    ofSetFrameRate(30);
    if(XML.load("settings.xml") ){cout << "setting loaded" <<endl;
    }else{cout << "setting load error" <<endl;}
    if(SCHEDULE.load("schedule.xml") ){cout << "setting loaded" <<endl;
    }else{cout << "setting load error" <<endl;}
    
    if(XML.exists("//WINDOWMODE")) {i_WindowMode = XML.getValue<int>("//WINDOWMODE");
    } else {i_WindowMode = 0;}
    if(XML.exists("//GAMEMODE")) {i_GameMode = XML.getValue<int>("//GAMEMODE");
    } else {i_GameMode = 0;}
    cout << "xml setting : Window Mode=" << i_WindowMode <<" : Game Mode=" << i_GameMode <<endl;
    switch(i_WindowMode){
        case 0:
            setupLeft();
            break;
        case 1:
            setupRight();
            break;
    }
    
    bgm.load("bgm.mp3");
    bgm.setVolume(1.0);
    buzzer.load("buzzer.wav");
    buzzer.setVolume(1.0);
    buzzer.setLoop(false);

    i_NowScheduleId = 0;
    b_ScheduleStart = false;
    b_SchedulePlaying = false;
    
    i_SceneID = 1;
    i_SceneIDPre = 1;
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
    testLight.setAmbientColor(ofFloatColor(0.8,0.8,0.8,1.0));
    testLight.setDiffuseColor(ofFloatColor(0.8,0.8,0.8));
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
        camBuf.setPosition(50, -50,70);
        camBuf.lookAt(ofVec3f(0,0,-200), ofVec3f(0,0,1));
        camBuf.setDistance(300.0);
        camBuf.setFov(70);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(0, -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,300), ofVec3f(0,0,1));
        camBuf.setDistance(150.0);
        camBuf.setFov(50);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(0, -RADIUS*4,RADIUS);
        camBuf.lookAt(ofVec3f(0,-RADIUS*3,GROUND_LEVEL), ofVec3f(0,0,1));
        camBuf.setDistance(250.0);
        camBuf.setFov(80);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        //camBuf.enableOrtho();
        camBuf.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,GROUND_LEVEL), ofVec3f(0,0,1));
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
        camBuf.lookAt(ofVec3f(0,RADIUS,GROUND_LEVEL), ofVec3f(0,0,1));
        camBuf.setChaseBall();
        camBuf.setFov(50);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        //camBuf.enableOrtho();
        camBuf.setPosition(0,COURT_HEIGHT_HALF*7.8/8,GOAL_HEIGHT);
        camBuf.setDistance(150);
        camBuf.lookAt(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT), ofVec3f(0,0,1));
        camBuf.setFov(30);
        //camBuf.setNearClip(0);
        camBuf.setFarClip(20000);
        v_Camera.push_back(camBuf);
    }

    
    for(int i = -MIR_X_NUM ;i<=MIR_X_NUM ;i++){
        for(int j = 0 ;j<=MIR_Y_NUM ;j++){
            ofxObjectMirror bufMirror;
            bufMirror.setPos(i*MIR_X_ANG, j*MIR_Y_ANG, RADIUS);
            v_ObjectMirror.push_back(bufMirror);
        }
    }
    



    for(int i = 0;i<4 ;i++){
        ofxObjectLight bufLight;
        bufLight.disable();
        bufLight.setPos(180, 0, 100);
        bufLight.setAngle(0, 0);
        v_ObjectLight2.push_back(bufLight);
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
    gui.setPosition(0,ofGetHeight()/2);
    b_GuiDraw = false;
    
    gpuBlur.blurOffset = 24;
    gpuBlur.blurPasses = 9.5;
    gpuBlur.numBlurOverlays = 1;
    gpuBlur.blurOverlayGain = 255;
    
    if(USE_BLACKMAGIC){
        cam.setup(BLACKMAGIC_W, BLACKMAGIC_H, BLACKMAGIC_FPS);
    }else{
        camMac.setDeviceID(0);
        camMac.setDesiredFrameRate(30);
        camMac.initGrabber(WEBCAM_W, WEBCAM_H);
    }
    b_CamStart = false;
    modelGoalBall.noGravity();
    modelGoalBall.setGoalLoop();
    receiver.setup(PORT);
    
    ballParticle.setup();

    
    //Gritch
    lenna.loadImage("lenna.png");
    bDrawLenna = true;
    bShowHelp  = false;
    myFbo.allocate(512, 512);
    myGlitch.setup(&myFbo);
    
    modelBall.setPos(ofVec3f(100,-100,0),ofVec3f(0,0,0));
    i_BigSightMaskMode = 0;
}

//update--------------------------------------------------------------
void ofApp::update(){
	//areaLight.setPosition(0,-200,0);
    switch(i_WindowMode){
        case 0:
            updateLeft();
            break;
        case 1:
            updateRight();
            break;
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

    if(b_ScheduleStart){
        b_ScheduleStart = false;
        b_SchedulePlaying = false;
        if(i_NowScheduleId==0){
            bgm.play();
        }
        if(i_NowScheduleId==(v_ScheduleSeg.size()-2)){
            buzzer.play();
        }
        switch(v_ScheduleSeg[i_NowScheduleId].actMode){
            case ACT_MODE_CG:
                i_SceneID = 1;
                changeToField();
                modelGoalBall.clearPose();
                modelBall.clearPose();
                break;
            case ACT_MODE_CAPTURE:
                i_SceneID = 2;
                break;
            case ACT_MODE_MOVIE:
                v_ScheduleSeg[i_NowScheduleId].video.play();
                b_SchedulePlaying = true;
                i_SceneID = 3;
                break;
            default:
                break;
        }
        if(v_ScheduleSeg[i_NowScheduleId].s_Name=="CG2fail"){
            cout << "CG 2 fail"<<endl;
            changeToGoal();
        }
        if(v_ScheduleSeg[i_NowScheduleId].s_Name=="CG 2 success"){
            cout << "CG 2 success"<<endl;
            changeToGoal();
        }
    }
    if(b_SchedulePlaying){
        v_ScheduleSeg[i_NowScheduleId].video.update();
    }
    
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if((i_SceneID == 1) and m.getAddress() == "/mouse/position"){
            int recX,recY,recScore;
            recX = int((unsigned char)(m.getArgAsChar(0)));
            recY = int((unsigned char)(m.getArgAsChar(1)));
            recScore = int((unsigned char)(m.getArgAsChar(2)));
            cout << recX << ":"<< recY << "=" << recScore << endl;
            if(recScore>50){
                int addPosX,addPosY;
                addPosX = 2 * COURT_WIDTH_HALF * (0.5 - recX / 255.0);
                addPosY = 2 * COURT_HEIGHT_HALF * (recY / 255.0 - 0.5);
                objectEffect.add(ofVec3f(addPosX,addPosY,GROUND_LEVEL+4));
            }
        }
        if((i_SceneID == 1) and m.getAddress() == "/debug/position"){
            int recX,recY;
            recX = int((unsigned char)(m.getArgAsChar(0)));
            recY = int((unsigned char)(m.getArgAsChar(1)));
            cout << "Debug Pos "<< recX << ":"<< recY << endl;
            int addPosX,addPosY;
            addPosX = 2 * COURT_WIDTH_HALF * (0.5 - recX / 255.0);
            addPosY = 2 * COURT_HEIGHT_HALF * (recY / 255.0 - 0.5);
            objectEffect.add(ofVec3f(addPosX,addPosY,GROUND_LEVEL+4));
        }
        if(m.getAddress() == "/pose/start"){
            int recX;
            recX = m.getArgAsInt32(0);
            cout << "OSC start" << recX << endl;
        }
        if(m.getAddress() == "/pose/update"){
            int recX;
            recX = m.getArgAsInt32(0);
            cout << m.getAddress() << recX << endl;
        }
        if((i_SceneID == 2) and m.getAddress() == "/pose/subset"){
            cout << "OSC got subset" << endl;
        }
        if((i_SceneID == 2) and m.getAddress() == "/pose/candidate"){
            cout << "OSC got candidate" << m.getArgAsInt32(0) <<":"<<m.getArgAsInt32(1) <<":"<<m.getArgAsInt32(2) <<":"<<m.getArgAsInt32(3) << endl;
            int detPosX,detPosY;
            detPosX = int(ofGetWidth() * (m.getArgAsInt32(0) / OPENPOSE_RESIZE_RATE) / OPENPOSE_CAP_WIDTH);
            detPosY = int(ofGetHeight() * (m.getArgAsInt32(1) / OPENPOSE_RESIZE_RATE) / OPENPOSE_CAP_HEIGHT);
            ballParticle.addPoint(detPosX,detPosY);
        }
    }
    switch(i_SceneID){
        case 1:
            update3D();
            break;
        case 2:
            //drawInput();
            ballParticle.update();
            break;
        case 3:
            //v_ScheduleSeg[i_NowScheduleId].video.draw(0, 0, ofGetWidth(), ofGetHeight());
            break;
        case 4:
            break;
        default:
            break;
    }
    if(i_SceneIDPre != i_SceneID){
        ballParticle.setup();
    }
    i_SceneIDPre = i_SceneID;
}

//update--------------------------------------------------------------
void ofApp::update3D(){
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].update(pi_AngleSpeed);
    }
    for(int i = 0; i<v_Camera.size(); i++){
        v_Camera[i].update();
        if(v_Camera[i].getChaseBall()){
            ofVec3f ballPos;
            ballPos = modelBall.getPos();
            v_Camera[i].setPosition(ballPos+ofVec3f(0, -100,100));
            v_Camera[i].lookAt(ballPos+ofVec3f(0, 0,0), ofVec3f(0,0,1));
        }
    }
    
    modelBall.update();
    if(b_BallColor and !modelBall.isReversePlaying() and !modelGoalBall.isReversePlaying()){
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
    //ballParticle.addMouse();
    if(b_BallColor and !modelBall.isReversePlaying() and !modelGoalBall.isReversePlaying()){
        ballParticle.addPoint(modelBall.getPos());
    }
    ballParticle.update();
}



//draw--------------------------------------------------------------
void ofApp::draw(){
    switch(i_WindowMode){
        case 0:
            drawLeft();
            break;
        case 1:
            drawRight();
            break;
    }
    switch(i_SceneID){
        case 1:
            draw3D();
            break;
        case 2:
            drawInput();
            ballParticle.draw();
            break;
        case 3:
            v_ScheduleSeg[i_NowScheduleId].video.draw(0, 0, ofGetWidth(), ofGetHeight());
            break;
        case 4:
            break;
        default:
            break;
    }
    ofEnableAlphaBlending();
    if(i_BigSightMaskMode==0)i_BigSightMask.draw(0,0,ofGetWidth(),ofGetHeight());
    if(i_BigSightMaskMode==1)i_BigSightMask2.draw(0,0,ofGetWidth(),ofGetHeight());
    if(b_GuiDraw){
        ofPushStyle();
        ofDisableLighting();
        ofDisableDepthTest();
        ofSetColor(255, 255, 255,255);
        gui.draw();
        ofPopStyle();
        ofSetColor(255, 255, 255,255);

        string info = "";
        info += "Framerate:"+ofToString(ofGetFrameRate())+"\n";
        info += "window size :"+ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())+"\n";
        info += ofToString(v_ScheduleSeg[i_NowScheduleId].s_Name)+"\n";
        info += " ";
        ofSetColor(255,255,255);
        ofDrawBitmapString(info, 20,gui.getPosition().y + gui.getHeight()+50);
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
        camImg.draw(-100,-100+int((ofGetHeight()-drawHeight)/2),-2, ofGetWidth(), drawHeight);
    }
    myFbo.end();

    ofSetColor(255);
    //myFbo.draw(0, 0);
    
    /* Apply effects */
    myGlitch.generateFx();
    
    /* draw effected view */
    ofSetColor(255);
    myFbo.draw(100, 100);
    
    
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
    
    ofRectangle viewport3D;
    viewport3D.x = 0;
    viewport3D.y = - ofGetHeight()/3;
    viewport3D.width = ofGetWidth();
    viewport3D.height = ofGetHeight()*4/3;
    v_Camera[i_Camera].begin(viewport3D);
    
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
            //model.drawFaces();
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
            //ofTranslate(0,0,pf_Buf5*pf_Buf6*pf_Buf2);
            modelGoal.draw();
            ofRotateZ(180);
            modelGoal.draw();
            ofPopMatrix();
        }
        {
            ofPushMatrix();
            
            
            testLight.disable();
            areaLight.disable();
            ballLight.enable();
            if(i_Camera==(v_Camera.size()-1)){
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
        objectEffect.draw();
        {
            ofPushMatrix();
            ofTranslate(0, 0,GROUND_LEVEL);
            ofRotateZ(180);
            imgCourt.draw(-COURT_WIDTH_HALF, -COURT_HEIGHT_HALF, COURT_WIDTH_HALF*2, 2*COURT_HEIGHT_HALF);
            ofSetColor(255, 255, 255, 200);
            ofTranslate(0, 0, 1);
            camImg.draw(-COURT_WIDTH_HALF, -COURT_HEIGHT_HALF, COURT_WIDTH_HALF*2, 2*COURT_HEIGHT_HALF);
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
    ofDisableDepthTest();
    ballParticle.draw();
    ofPopMatrix();
    ofPopStyle();
    

    

    
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

    testLight.enable();
    gpuBlur.beginDrawScene();
    ofClear(0, 0, 0, 0);
    
    ofRectangle viewport3D2;
    viewport3D2.x = 0;
    viewport3D2.y = 0;
    viewport3D2.width = ofGetWidth();
    viewport3D2.height = ofGetHeight()*4/3;
    v_Camera[i_Camera].begin(viewport3D2);
    ofSetColor(255, 240, 230);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].drawLineTo(ofVec3f(0,-RADIUS,0));
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
        if( int(i/2) == 0){
            ofSetColor(255, 240, 230);
        }else{
            ofSetColor(255, 200, 190);
        }
        v_ObjectLight2[i].drawLineDirMulti(v_ObjectLight2[i].getNorm()*250);
        ofPopMatrix();
    }
    
    v_Camera[i_Camera].end();
    
    gpuBlur.endDrawScene();
    gpuBlur.performBlur();
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
    gpuBlur.drawBlurFbo();
    
    testLight.disable();
    

}

void ofApp::changeToField(){
    i_Camera = 0;
    modelBall.clearHistory();
}
void ofApp::changeToGoal(){
    i_Camera = v_Camera.size()-1;
    modelGoalBall.t_Count = 0;
    modelGoalBall.noGravity();
    modelGoalBall.setGoalLoop();
    modelGoalBall.clearHistory();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
        case ' ':
            b_ScheduleStart = true;
            cout << i_NowScheduleId << " start"<<endl;
            break;
        case 'e':
            objectEffect.add(ofVec3f(ofRandom(-80,80),ofRandom(-120,100),GROUND_LEVEL));
            break;
        case 'p':
            if(i_Camera == (v_Camera.size()-1)){
                modelGoalBall.togglePose();
            }else{
                modelBall.togglePose();
            }
            break;
        case ';':
            if(i_Camera == (v_Camera.size()-1)){
                modelGoalBall.startReplay();
            }else{
                modelBall.startReplay();
            }
            break;
        case '/':
            if(i_Camera == (v_Camera.size()-1)){
                modelGoalBall.startReverse();
            }else{
                modelBall.startReverse();
            }
            break;
        case 's':
            bgm.stop();
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
            modelBall.throwTo(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT+40),13);
            break;
        case '[':
            modelBall.clearHistory();
            modelBall.setPos(ofVec3f(0,-COURT_HEIGHT_HALF,GROUND_LEVEL),ofVec3f(0,0,0));
            modelBall.throwTo(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT+200),12);
            break;
        case ']':
            modelBall.clearHistory();
            modelBall.setPos(ofVec3f(0,-COURT_HEIGHT_HALF,GROUND_LEVEL),ofVec3f(0,0,0));
            modelBall.throwTo(ofVec3f(-GOAL_LOOP_RADIUS,COURT_HEIGHT_HALF,GOAL_HEIGHT+300),13);
            break;
        case OF_KEY_UP:
            i_NowScheduleId = MAX(0,i_NowScheduleId-1);
            scheduleChange();
            break;
        case OF_KEY_DOWN:
            i_NowScheduleId = MIN(v_ScheduleSeg.size()-1,i_NowScheduleId+1);
            scheduleChange();
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
        case 'x':
            if(i_Camera == (v_Camera.size()-1)){
                changeToField();
            }else{
                changeToGoal();
            }
            modelGoalBall.clearPose();
            modelBall.clearPose();
            for(int i = 0;i<v_Camera.size();i++){
                if(i_Camera == i){
                    v_Camera[i].enableMouseInput();
                }else{
                    v_Camera[i].disableMouseInput();
                }
            }
            break;
        case 'm':
            i_BigSightMaskMode = (i_BigSightMaskMode+1)%3;
            break;
        case 'c':
            //b_Camera = !b_Camera;
            i_Camera = (i_Camera +1)%(v_Camera.size()-1);
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
        case '@':
            modelGoalBall.releaseOut();
            break;
        case ':':
            modelGoalBall.releaseGoal();
            break;
        case '_':
            modelGoalBall.startGoalLoopSlow();
            break;
	}
    if (key == '-') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE    , true);
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
    if (key == '-') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE    , false);
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
    if(i_SceneID == 2){
        ballParticle.addPoint(x,y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(i_SceneID == 2){
        ballParticle.addPoint(x,y);
    }
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

void ofApp::scheduleChange(){
    for(int i =0;i<v_ScheduleSeg.size();i++){
        if(v_ScheduleSeg[i].actMode == ACT_MODE_MOVIE){
            if(v_ScheduleSeg[i].video.isPlaying())v_ScheduleSeg[i].video.stop();
        }
    }
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::exit(){
    if(USE_BLACKMAGIC){
        cam.close();
    }
}

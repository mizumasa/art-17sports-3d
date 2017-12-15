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
#define RIGHT_POS_NUM 80

int right_pos[RIGHT_POS_NUM][3][2]={{{128, 62}, {240, 62}, {188, 159}},
    {{240, 62}, {354, 62}, {301, 159}},
    {{354, 62}, {467, 62}, {413, 159}},
    {{467, 62}, {581, 62}, {525, 159}},
    {{581, 62}, {694, 62}, {638, 159}},
    {{694, 62}, {809, 62}, {750, 159}},
    {{809, 62}, {922, 62}, {863, 159}},
    {{922, 62}, {1036, 62}, {976, 159}},
    {{1036, 62}, {1150, 62}, {1087, 159}},
    {{240, 62}, {188, 159}, {301, 159}},
    {{354, 62}, {301, 159}, {413, 159}},
    {{467, 62}, {413, 159}, {525, 159}},
    {{581, 62}, {525, 159}, {638, 159}},
    {{694, 62}, {638, 159}, {750, 159}},
    {{809, 62}, {750, 159}, {863, 159}},
    {{922, 62}, {863, 159}, {976, 159}},
    {{1036, 62}, {976, 159}, {1087, 159}},
    {{188, 159}, {301, 159}, {249, 254}},
    {{301, 159}, {413, 159}, {360, 254}},
    {{413, 159}, {525, 159}, {471, 254}},
    {{525, 159}, {638, 159}, {582, 254}},
    {{638, 159}, {750, 159}, {693, 254}},
    {{750, 159}, {863, 159}, {804, 254}},
    {{863, 159}, {976, 159}, {916, 254}},
    {{976, 159}, {1087, 159}, {1027, 254}},
    {{301, 159}, {249, 254}, {360, 254}},
    {{413, 159}, {360, 254}, {471, 254}},
    {{525, 159}, {471, 254}, {582, 254}},
    {{638, 159}, {582, 254}, {693, 254}},
    {{750, 159}, {693, 254}, {804, 254}},
    {{863, 159}, {804, 254}, {916, 254}},
    {{976, 159}, {916, 254}, {1027, 254}},
    {{249, 254}, {360, 254}, {308, 347}},
    {{360, 254}, {471, 254}, {418, 347}},
    {{471, 254}, {582, 254}, {528, 347}},
    {{582, 254}, {693, 254}, {637, 347}},
    {{693, 254}, {804, 254}, {747, 347}},
    {{804, 254}, {916, 254}, {857, 347}},
    {{916, 254}, {1027, 254}, {968, 347}},
    {{360, 254}, {308, 347}, {418, 347}},
    {{471, 254}, {418, 347}, {528, 347}},
    {{582, 254}, {528, 347}, {637, 347}},
    {{693, 254}, {637, 347}, {747, 347}},
    {{804, 254}, {747, 347}, {857, 347}},
    {{916, 254}, {857, 347}, {968, 347}},
    {{308, 347}, {418, 347}, {366, 438}},
    {{418, 347}, {528, 347}, {474, 438}},
    {{528, 347}, {637, 347}, {583, 438}},
    {{637, 347}, {747, 347}, {692, 438}},
    {{747, 347}, {857, 347}, {800, 438}},
    {{857, 347}, {968, 347}, {910, 438}},
    {{418, 347}, {366, 438}, {474, 438}},
    {{528, 347}, {474, 438}, {583, 438}},
    {{637, 347}, {583, 438}, {692, 438}},
    {{747, 347}, {692, 438}, {800, 438}},
    {{857, 347}, {800, 438}, {910, 438}},
    {{366, 438}, {474, 438}, {423, 527}},
    {{474, 438}, {583, 438}, {529, 527}},
    {{583, 438}, {692, 438}, {637, 527}},
    {{692, 438}, {800, 438}, {745, 527}},
    {{800, 438}, {910, 438}, {853, 527}},
    {{474, 438}, {423, 527}, {529, 527}},
    {{583, 438}, {529, 527}, {637, 527}},
    {{692, 438}, {637, 527}, {745, 527}},
    {{800, 438}, {745, 527}, {853, 527}},
    {{423, 527}, {529, 527}, {479, 615}},
    {{529, 527}, {637, 527}, {583, 615}},
    {{637, 527}, {745, 527}, {691, 615}},
    {{745, 527}, {853, 527}, {797, 615}},
    {{529, 527}, {479, 615}, {583, 615}},
    {{637, 527}, {583, 615}, {691, 615}},
    {{745, 527}, {691, 615}, {797, 615}},
    {{479, 615}, {583, 615}, {532, 699}},
    {{583, 615}, {691, 615}, {637, 699}},
    {{691, 615}, {797, 615}, {743, 699}},
    {{583, 615}, {532, 699}, {637, 699}},
    {{691, 615}, {637, 699}, {743, 699}},
    {{532, 699}, {637, 699}, {585, 780}},
    {{637, 699}, {743, 699}, {690, 780}},
    {{637, 699}, {585, 780}, {690, 780}}};

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
    
    //bgm.load("bgm.mp3");
    //bgm.setVolume(1.0);
    bgm1.bgm.load("bgm/intro_BGM.wav");
    bgm1.bgm.setVolume(1.0);
    bgm2.bgm.load("bgm/interaction_bgm.wav");
    bgm2.bgm.setVolume(1.0);
    bgm3.bgm.load("bgm/end_bgm.wav");
    bgm3.bgm.setVolume(1.0);
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
        camBuf.setDistance(150.0);
        camBuf.setPosition(-2, -28,-32);
        camBuf.lookAt(ofVec3f(-57,60,-16), ofVec3f(0,0,1));
        camBuf.setFov(100);
        v_Camera.push_back(camBuf);
        
    }
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setDistance(150.0);
        camBuf.setPosition(78, 172,88);
        camBuf.lookAt(ofVec3f(-26,98,-6), ofVec3f(0,0,1));
        camBuf.setFov(53);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setDistance(150.0);
        camBuf.setPosition(0,0,0);
        camBuf.lookAt(ofVec3f(0,10,GROUND_LEVEL), ofVec3f(0,0,1));
        camBuf.setChaseBall(3);
        camBuf.setFov(60);
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
        camBuf.setChaseBall(1);
        camBuf.setFov(50);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(0, -RADIUS,0);
        camBuf.lookAt(ofVec3f(0,RADIUS,GROUND_LEVEL), ofVec3f(0,0,1));
        camBuf.setChaseBall(2);
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
    b_CameraFix = true;

    
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
    imgCourt.load("groundc1.png");
    
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
    gui.add(pf_Buf3.setup("pf_Buf3", 1, -100.0, 100.0));
    gui.add(pf_Buf4.setup("pf_Buf4", 1, -100.0, 100.0));
    gui.add(pf_Buf5.setup("pf_Buf5", 1, -100.0, 100.0));
    gui.add(pf_Buf6.setup("pf_Buf6", 1, -100.0, 100.0));
    gui.add(pf_Buf7.setup("pf_Buf7", 1, -100.0, 100.0));
    gui.add(pf_Buf8.setup("pf_Buf8", 1, -100.0, 100.0));
    gui.add(pf_Buf9.setup("pf_Buf9", 1, -100.0, 100.0));
    gui.setPosition(0,ofGetHeight()/2);
    b_GuiDraw = false;
    
    gpuBlur.blurOffset = 10;
    gpuBlur.blurPasses = 2;
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
    modelGameBall.noGravity();
    modelGameBall.setNoResistance();
    modelGameBall.b_Slow = true;

    i_BigSightMaskMode = 0;
    
    i_PanelScore = 0;
    
    objectFrame.setPoints();
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
            //bgm.play();
        }
        if(i_NowScheduleId==(v_ScheduleSeg.size()-2)){
            //buzzer.play();
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
                if(i_NowScheduleId==2){
                    bgm1.setFo();
                    bgm2.play();
                }
                if(i_NowScheduleId==8){
                    bgm2.setFo();
                    bgm3.play();
                }
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
        if(m.getAddress() == "/mouse/position"){
            int recX,recY,recScore;
            recX = int((unsigned char)(m.getArgAsChar(0)));
            recY = int((unsigned char)(m.getArgAsChar(1)));
            recScore = int((unsigned char)(m.getArgAsChar(2)));
            cout << recX << ":"<< recY << "=" << recScore << endl;
            if(recScore>50){
                /*
                 int addPosX,addPosY;
                addPosX = 2 * COURT_WIDTH_HALF * (0.5 - recX / 255.0);
                addPosY = 2 * COURT_HEIGHT_HALF * (recY / 255.0 - 0.5);
                objectEffect.add(ofVec3f(addPosX,addPosY,GROUND_LEVEL+4));*/
                mousePressed(ofGetWidth()*recX / 255.0, ofGetHeight()*recY / 255.0,0);
            }
        }
        if(m.getAddress() == "/debug/position"){
            int recX,recY;
            recX = int((unsigned char)(m.getArgAsChar(0)));
            recY = int((unsigned char)(m.getArgAsChar(1)));
            cout << "Debug Pos "<< recX << ":"<< recY << endl;
            
            /*int addPosX,addPosY;
            addPosX = 2 * COURT_WIDTH_HALF * (0.5 - recX / 255.0);
            addPosY = 2 * COURT_HEIGHT_HALF * (recY / 255.0 - 0.5);
            objectEffect.add(ofVec3f(addPosX,addPosY,GROUND_LEVEL+4));
             */
            mousePressed(ofGetWidth()*recX / 255.0, ofGetHeight()*recY / 255.0,0);
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
    for(int i = 0; i<v_ObjectPanel.size(); i++){
        v_ObjectPanel[i].update();
    }
    objectPanel2.update();
    objectFrame.i_ColorMode = i_NowScheduleId % 2;
    objectFrame.update();
    objectCountdown.update();
    
    if(i_SceneIDPre != i_SceneID){
        ballParticle.setup();
    }
    i_SceneIDPre = i_SceneID;

    if(b_GuiDraw and (modelGameBall.t_Count%125==0)){
        cout <<"{"<< modelGameBall.getPos() <<","<< modelGameBall.vf_Speed <<"},"<< endl;
    }
    bgm1.update();
    bgm2.update();
    bgm3.update();

}

//update--------------------------------------------------------------
void ofApp::update3D(){
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].update(pi_AngleSpeed);
    }
    for(int i = 0; i<v_Camera.size(); i++){
        v_Camera[i].update();
        if(0){
            v_Camera[i].setPosition(pf_Buf1*2, pf_Buf2*2,pf_Buf3*2);
            v_Camera[i].lookAt(ofVec3f(pf_Buf4,pf_Buf5,pf_Buf6), ofVec3f(0,0,1));
            v_Camera[i].setFov(pf_Buf7);
        }

        //v_Camera[i].setFov(pf_Buf1);
        if(v_Camera[i].getChaseBall() > 0){
            ofVec3f ballPos;
            switch(v_Camera[i].getChaseBall()){
                case 1:
                    ballPos = modelBall.getPos();
                    v_Camera[i].setPosition(ballPos+ofVec3f(0, -100,100));
                    v_Camera[i].lookAt(ballPos+ofVec3f(0, 0,0), ofVec3f(0,0,1));
                    break;
                case 2:
                    ballPos = modelGameBall.getPos();
                    v_Camera[i].setPosition(ballPos+ofVec3f(0, -50,-10));
                    v_Camera[i].lookAt(ballPos + ofVec3f(0,0,0), ofVec3f(0,0,1));
                    break;
                default://3
                    ballPos = modelBall.getPos();
                    v_Camera[i].setPosition(ofVec3f(50, -22,-44));
                    v_Camera[i].lookAt(ballPos+ofVec3f(0,0,0), ofVec3f(0,0,1));
                    break;
            }
        }
        if(v_Camera[i].getAutoMove()){
            ofVec3f ballPos;
            ballPos = modelBall.getPos();
            v_Camera[i].lookAt(ballPos+ofVec3f(0, 0,0), ofVec3f(0,0,1));
        }
    }
    
    modelBall.update();
    modelGameBall.update();
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
    objectRing.update(modelGameBall.getPos()[1]);
    //ballParticle.addMouse();
    if(b_BallColor and !modelBall.isReversePlaying() and !modelGoalBall.isReversePlaying()){
        ballParticle.addPoint(modelBall.getPos());
    }
    ballParticle.update();
}



//draw--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushStyle();
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
    ofPopStyle();
    ofPushMatrix();
    ofDisableLighting();
    ofScale(ofGetWidth()/MACBOOKPRO_W, ofGetHeight()/MACBOOKPRO_H);
    for(int i = 0; i<v_ObjectPanel.size(); i++){
        v_ObjectPanel[i].draw();
    }
    ofPushStyle();
    if(i_WindowMode==0){
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, 120);
    }
    objectFrame.draw();
    ofPopStyle();
    objectCountdown.draw();
    ofPopMatrix();
    objectPanel2.draw();
    ofPopStyle();
    ofPopMatrix();
    
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
    
#ifdef USE_FBO
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
#endif
    
    
    
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
                modelGameBall.draw();
            }
            ballLight.disable();

            if(b_TestLight)testLight.enable();
            if(!b_TestLight)areaLight.enable();
            
            ofPopMatrix();
        }
        objectEffect.draw();
        objectRing.draw();
        {
            ofPushMatrix();
            ofTranslate(0, 0,GROUND_LEVEL);
            ofRotateZ(180);
            imgCourt.draw(-COURT_WIDTH_HALF, -COURT_HEIGHT_HALF, COURT_WIDTH_HALF*2, 2*COURT_HEIGHT_HALF);
            //ofSetColor(255, 255, 255, 200);
            //ofTranslate(0, 0, 1);
            //camImg.draw(-COURT_WIDTH_HALF, -COURT_HEIGHT_HALF, COURT_WIDTH_HALF*2, 2*COURT_HEIGHT_HALF);
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
    

    testLight.enable();
    areaLight.disable();
    


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
        case 'q':
            bgm1.play();
            break;
        case 'a':
            bgm2.play();
            break;
        case 'z':
            bgm3.play();
            break;
        case 's':
            bgm1.bgm.stop();
            bgm2.bgm.stop();
            bgm3.bgm.stop();
            break;
        case 'd':
            if(bgm1.bgm.isPlaying())bgm1.setDown();
            if(bgm2.bgm.isPlaying())bgm2.setDown();
            if(bgm3.bgm.isPlaying())bgm3.setDown();
            break;
        case 'u':
            if(bgm1.bgm.isPlaying())bgm1.setUp();
            if(bgm2.bgm.isPlaying())bgm2.setUp();
            if(bgm3.bgm.isPlaying())bgm3.setUp();
            break;
        case 'o':
            if(bgm1.bgm.isPlaying()){
                bgm1.setFo();
            }
            if(bgm2.bgm.isPlaying())bgm2.setFo();
            if(bgm3.bgm.isPlaying())bgm3.setFo();
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
        case 'y':
            //modelBall.setSpeed(ofVec3f(0,0,5));
            //modelGameBall.setGravity(2/1000.0);
            modelGameBall.setGravity(7/10000.0);
            modelGameBall.setPos(ofVec3f(0,-COURT_HEIGHT_HALF+40,GROUND_LEVEL+10),ofVec3f(2,2,0));
            //modelGameBall.throwTo(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT+99),89/100.0);
            modelGameBall.throwTo(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT+66*2),50/100.0);
            objectRing.init();
            break;
        case '[':
            modelBall.clearHistory();
            modelBall.setPos(ofVec3f(-COURT_WIDTH_HALF/2,0,GROUND_LEVEL),ofVec3f(0,0,0));
            modelBall.throwTo(ofVec3f(4.96,COURT_HEIGHT_HALF,GOAL_HEIGHT+128.8),8.3665);
            break;
        case ']':
            modelBall.clearHistory();
            modelBall.setPos(ofVec3f(0,-COURT_HEIGHT_HALF+40,GROUND_LEVEL+10),ofVec3f(2,2,0));
            modelBall.throwTo(ofVec3f(0,COURT_HEIGHT_HALF,GOAL_HEIGHT+99),10.4);
            break;
        case OF_KEY_UP:
            i_NowScheduleId = max(0,i_NowScheduleId-1);
            scheduleChange();
            modelGameBall.vf_SlowShift[2] += 0.1;
            break;
        case OF_KEY_DOWN:
            //i_NowScheduleId = MIN(v_ScheduleSeg.size()-1,i_NowScheduleId+1);
            i_NowScheduleId = i_NowScheduleId+1;
            if(i_NowScheduleId > v_ScheduleSeg.size()-1){
                i_NowScheduleId = v_ScheduleSeg.size()-1;
            }
            scheduleChange();
            for(int i = 0; i<v_ObjectPanel.size(); i++){
                v_ObjectPanel[i].start();
            }
            modelGameBall.vf_SlowShift[2] -= 0.1;
            break;
        case OF_KEY_LEFT:
            modelGameBall.vf_SlowShift[0] -= 0.4;
            break;
        case OF_KEY_RIGHT:
            modelGameBall.vf_SlowShift[0] += 0.4;
            break;
            
        case '1':
            i_SceneID = 1;
            break;
        case '2':
            i_SceneID = 2;
            break;
        case '3':
            objectCountdown.start(0);
            objectFrame.setBlinkTimer(30);
            break;
        case '4':
            objectCountdown.start(1);
            break;
        case '5':
            objectCountdown.start(2);
            break;
        case '6':
            objectCountdown.start(3);
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
            /*
            if(i_Camera == (v_Camera.size()-1)){
                changeToField();
            }else{
                changeToGoal();
            }*/
            i_Camera = v_Camera.size()-2;
            modelGoalBall.clearPose();
            modelBall.clearPose();
            for(int i = 0;i<v_Camera.size();i++){
                if(i_Camera == i and !b_CameraFix){
                    v_Camera[i].enableMouseInput();
                }else{
                    v_Camera[i].disableMouseInput();
                }
            }
            break;
        case 'm':
            i_BigSightMaskMode = (i_BigSightMaskMode+1)%3;
            break;
        case 'C':
            b_CameraFix = !b_CameraFix;
            break;
        case 'c':
            //b_Camera = !b_Camera;
            i_Camera = (i_Camera +1)%(v_Camera.size()-2);
            for(int i = 0;i<v_Camera.size();i++){
                if(i_Camera == i and !b_CameraFix){
                //if(false){
                    v_Camera[i].enableMouseInput();
                }else{
                    v_Camera[i].disableMouseInput();
                }
            }
            break;
        case 'b':
            b_BallColor = !b_BallColor;
            break;
        case 'B':
            objectFrame.setBlink(true);
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

    
    
#ifdef USE_DETECTION
    //below cam
    if(key == 'i') detect.toggleImage();
    if(key == 'g') detect.bHideGui = !detect.bHideGui;
    //if(key == 's') detect.saveParam();
    //if(key == 'l') detect.loadParam();
    //if(key == 'c') perspective.toggleImage();
    if(key == 'd') b_DrawImage = !b_DrawImage;
#else
#endif
    
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

    if (key == 'B') objectFrame.setBlink(false);

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(i_SceneID == 2){
        ballParticle.addPoint(x,y);
    }
    
#ifdef USE_DETECTION
    if(b_DrawImage)perspective.mouseDragged(mouseX, mouseY, button);
#endif
    
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(i_SceneID == 2){
        ballParticle.addPoint(x,y);
    }
    cout << "pos:" << x << ":" << y << endl;
    
    switch(v_Camera[i_Camera].getChaseBall()){
        case 2:
        {
            objectPanel2.add(ofVec2f(x,y),modelGameBall.vf_SlowShift, (i_WindowMode==0));
        }
            break;
        default:
        {
            if(i_PanelScore >= RIGHT_POS_NUM){
                i_PanelScore = 0;
                v_ObjectPanel.clear();
            }
            ofxObjectPanel bufPanel;
            int i_Offset1,i_Offset2;
            i_Offset1 =  - ofGetWidth()*i_WindowMode;
            i_Offset2 =  ofGetWidth()* (1 - i_WindowMode);
            bufPanel.i_ColorMode = i_NowScheduleId % 2;
            bufPanel.setStartPos(ofVec2f(i_Offset1 + x,y),
                                 ofVec2f(i_Offset2 + right_pos[RIGHT_POS_NUM-1-i_PanelScore][0][0],right_pos[RIGHT_POS_NUM-1-i_PanelScore][0][1]),
                                 ofVec2f(i_Offset2 + right_pos[RIGHT_POS_NUM-1-i_PanelScore][1][0],right_pos[RIGHT_POS_NUM-1-i_PanelScore][1][1]),
                                 ofVec2f(i_Offset2 + right_pos[RIGHT_POS_NUM-1-i_PanelScore][2][0],right_pos[RIGHT_POS_NUM-1-i_PanelScore][2][1]));
            
            i_PanelScore += 1;
            v_ObjectPanel.push_back(bufPanel);
        }
            break;
    }
    
    

#ifdef USE_DETECTION
    if(b_DrawImage)perspective.mousePressed(mouseX, mouseY, button);
#endif
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

#ifdef USE_DETECTION
    if(b_DrawImage)perspective.mouseReleased(mouseX, mouseY, button);
#endif
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

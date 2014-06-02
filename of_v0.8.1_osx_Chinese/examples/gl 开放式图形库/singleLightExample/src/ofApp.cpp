#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofEnableDepthTest() 使用openGL的z-buffer功能 - 就是存储每个象素的z-value并且每帧都会清除再更新z坐标
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(10, 10, 10);
	ofEnableDepthTest();
    
    // turn on smooth lighting //
	// 使用平滑灯光
    ofSetSmoothLighting(true);
    
    // lets make a sphere with more resolution than the default //
    // default is 20 //
	// 设置圆圈份比率，数字越大越高清
    ofSetSphereResolution(32);
	
	radius = 300.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
	// 灯光向各个方向个方向发光
    // 设置漫反射颜色，颜色从光源反射
    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
    
    // specular color, the highlight/shininess color //
	// specular light 代表光点的材料颜色
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(center.x, center.y, 0);
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
	// 闪亮度范围在0-128，128最亮
	material.setShininess( 64 );
    
    
	// 设置半径，把个球，是否使用线框模式
    sphereRadius    = 140;
    numSpheres      = 8;
    rotation        = 0.f;
    bDrawWireframe  = false;
    
	// 设置灯光的一些数据
    colorHue = ofRandom(0, 250);
    
    lightColor.setBrightness( 180.f );
    lightColor.setSaturation( 150.f );
    
    materialColor.setBrightness(250.f);
    materialColor.setSaturation(200);
}

//--------------------------------------------------------------
void ofApp::update() {
	// 更新颜色
	colorHue += .1f;
    if(colorHue >= 255) colorHue = 0.f;
    lightColor.setHue(colorHue);
    
    rotation += 1;
    if(rotation >=360) rotation = 0;
    
	// 更新半径
    radius = cos(ofGetElapsedTimef()) * 200.f + 200.f;
    
    pointLight.setDiffuseColor(lightColor);
    
    
    materialColor.setHue(colorHue);
    // the light highlight of the material //
	material.setSpecularColor(materialColor);
}

//--------------------------------------------------------------
void ofApp::draw() {
    
	// 画球
    ofSetColor(pointLight.getDiffuseColor());
    ofDrawSphere(pointLight.getPosition(), 20.f);
    
    // enable lighting //
	// 使用灯光
    ofEnableLighting();
    // the position of the light must be updated every frame,
    // call enable() so that it can update itself //
    pointLight.enable();
    material.begin();
    
    if(bDrawWireframe) ofNoFill();
    else ofFill();
    
    
	// 每个球在不停的旋转
    ofPushMatrix();
    ofTranslate(center.x, center.y, 0);
    ofRotate(rotation, 0, 0, 1);
	for(int i = 0; i < numSpheres; i++) {
        float angle = TWO_PI / (float)numSpheres * i;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        ofDrawSphere(x, y, -200, sphereRadius);
    }
    ofPopMatrix();
	material.end();
	// turn off lighting //
	// 关灯
    ofDisableLighting();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Draw Wireframe (w) : "+ofToString(bDrawWireframe, 0), 20, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// 控制是否画线框
    switch (key) {
        case 'w':
            bDrawWireframe = !bDrawWireframe;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    pointLight.setPosition(x, y, 0);
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
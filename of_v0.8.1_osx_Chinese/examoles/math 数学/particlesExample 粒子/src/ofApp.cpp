#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	// ofSetVerticalSync()-同步更新屏幕重绘和屏幕的垂直刷新
	ofSetVerticalSync(true);
	
	
	int num = 1500;							// 1500 粒子
	p.assign(num, demoParticle());
	currentMode = PARTICLE_MODE_ATTRACT;	//跟踪鼠标
    
	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
    
	resetParticles();						//重置
}

//--------------------------------------------------------------
void ofApp::resetParticles(){
    
	//these are the attraction points used in the forth demo
    //让我们先清空所有的吸引点，以防止这些吸引点在之前使用过
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	//设置一些性质
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
    
	//更新粒子的性质
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update();
	}
	
	//lets add a bit of movement to the attract points
    //让吸引点动起来，这只不过是一种算法，可以自己调整
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//设置背景色彩
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
    
	//画出所有粒子
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}
	
	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofCircle(attractPointsWithMovement[i], 4);
		}
	}
    
	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	//一些说明文字
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}
    
	if( key == ' ' ){
		resetParticles();
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

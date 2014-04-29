#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	// we add this listener before setting up so the initial circle resolution is correct
    // 我们需要在gui建立之前加入监听，这样才能得到正确的圆形分辨率
	circleResolution.addListener(this, &ofApp::circleResolutionChanged);
	ringButton.addListener(this,&ofApp::ringButtonPressed);

	gui.setup(); // most of the time you don't need a name
    //大多数情况，我们不需要命名它
	gui.add(filled.setup("fill", true));
	gui.add(radius.setup( "radius", 140, 10, 300 ));
	gui.add(center.setup("center",ofVec2f(ofGetWidth()*.5,ofGetHeight()*.5),ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight())));
	gui.add(color.setup("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	gui.add(circleResolution.setup("circle res", 5, 3, 90));
	gui.add(twoCircles.setup("two circles"));
	gui.add(ringButton.setup("ring"));
	gui.add(screenSize.setup("screen size", ""));

	bHide = true;

	ring.loadSound("ring.wav");
}

//--------------------------------------------------------------
void ofApp::exit(){
	ringButton.removeListener(this,&ofApp::ringButtonPressed);
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int & circleResolution){
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
	ring.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
	if( filled ){
		ofFill();
	}else{
		ofNoFill();
	}

	ofSetColor(color);
	if(twoCircles){
		ofCircle(center->x-radius*.5, center->y, radius );
		ofCircle(center->x+radius*.5, center->y, radius );
	}else{
		ofCircle((ofVec2f)center, radius );
	}
	
	// auto draw?
	// should the gui control hiding?
    // 要自动画？
    // 还是应该用gui控制是显示和隐藏？
	if( bHide ){
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == 'h' ){
		bHide = !bHide;
	}
	if(key == 's') {
		gui.saveToFile("settings.xml");
	}
	if(key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	if(key == ' '){
		color = ofColor(255);
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
    screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}

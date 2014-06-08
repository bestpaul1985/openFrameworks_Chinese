//04-25-2014
/**
 *
 * OFDevCon Example Code Sprint
 * Trigonometry example that depicts the relationship between a circle and the sine and cosine.
 *
 * Created by Roy Macdonald on 2/24/2012
 */

//三角函数例子
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    //设置证绿和背景颜色
	ofSetFrameRate(60);
	ofBackground(50);
    
    
    //一些有关的初始数字（包括角度，半径，旋转速度，中心)，都在 ofApp.h 里宣布的
	angle=0;
	cosine=0;
	sine=0;
	tangent=0;
	rotationSpeed=0.01f;
	radius = 180;
	center.set(ofGetWidth()*0.3f, ofGetHeight()*0.6f, 0);
	
	
    //设置圆圈分辨率
    ofSetCircleResolution(40);
	
	
    //弧的一些性质, setFill() 控制是否填充颜色
	angleArc.setArcResolution(360);
	angleArc.setFilled(true);
	angleArc.setColor(ofColor(240, 130, 10));
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
    //用鼠标控来制运动， 都挺明显的
	if (!ofGetMousePressed()) {
		angle+=rotationSpeed;
	}
	if (angle>=TWO_PI) {
		angle=0;
	}
    
    
    //计算余弦, 正弦, 切线
	cosine=cos(angle);
	sine=sin(angle);
	tangent=tan(angle);
	
	
	point.set(cosine * radius, sine * radius, 0);
    
    //一个代表角度的弧
	angleArc.clear();
	angleArc.arc( 0,  0, radius * 0.5f, radius * 0.5f, 0, ofRadToDeg(angle));
	angleArc.close();
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw()永远是从左上角开始的，我们先移动到中间，这样作为启发点会方便一些
	ofTranslate(center);
	
    //画一个黄色的圆圈。 位置 -（0，0）半径 - 180 像素
	ofSetColor(240, 230, 10);
	ofCircle(0,0, radius);
	
    //再画一个青色的圆圈， 差不多的概念
	ofSetColor(0, 140, 255);
	ofCircle(point, 10);
	
    //画桔黄色的弧
	angleArc.draw();
    
    //画x轴和y轴
	ofSetColor(20);
	ofSetLineWidth(1);
	ofLine(-radius * 1.3f, 0, radius * 2, 0);
	ofLine(0, -radius * 2, 0, radius * 1.3f);
	
	ofSetColor(180);
	ofLine(0, -radius , radius * 2, -radius);
	ofLine(0,  radius , radius * 2,  radius);
	ofLine(-radius, 0 ,-radius,  -radius * 2);
	ofLine( radius, 0 , radius,  -radius * 2);
	
    //画粉红色的杆
	ofSetColor(255, 0, 127);
	ofRect(0, -radius * 2, cosine * radius, 20);
	ofRect(radius * 2, 0, -20, sine * radius);
	
	
	ofSetLineWidth(3);
	
	
    //从青色到粉红色杆的直线
	ofSetColor(255, 0, 50);
	ofLine(point.x, point.y, cosine * radius, -radius * 2);
	ofLine(point.x, point.y, radius * 2, sine * radius);
	
    
    //画旋转的半径
	ofSetColor(0, 127, 255);
	ofLine(0, 0, point.x, point.y);
	
    
    //画移动的黑线
	ofSetColor(40);
	ofLine(0, sine * radius, cosine * radius, sine * radius);
	ofLine(cosine * radius, 0, cosine * radius, sine * radius);
	
    
    //画不断更新的文字包括角度，半径，余弦, 正弦, 切线
	ofSetColor(10);
	ofDrawBitmapString("Angle (RAD): " + ofToString(angle), 3,-3);
	ofSetColor(30);
	ofDrawBitmapString("Angle (DEG): " + ofToString(ofRadToDeg(angle)), 3,20);
	
	ofDrawBitmapString("Radius: " + ofToString(radius), -radius +20, -3);
	
	ofSetColor(220);
	ofDrawBitmapString("Angle Sine: " + ofToString(sine), radius *2 +3, 0);
	ofDrawBitmapString("sine x radius: " + ofToString(sine * radius), radius *2 +3, 15	);
	
	ofDrawBitmapString("Angle cosine: " + ofToString(cosine), 0, -radius *2 -20);
	ofDrawBitmapString("cosine x radius: " + ofToString(cosine * radius), 0, -radius *2 -5 );
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //点鼠标将导致重新设置动画
	ofVec2f mousePos(x-center.x, y-center.y);
	if (mousePos.length()<radius ) {
		angle = -mousePos.angleRad(ofVec2f(radius,0));
		if (angle<0) {
			angle+=TWO_PI;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //点鼠标将导致重新设置动画
	ofVec2f mousePos(x-center.x, y-center.y);
	if (mousePos.length()<radius ) {
		angle = -mousePos.angleRad(ofVec2f(radius,0));
		if (angle<0) {
			angle+=TWO_PI;
		}
	}
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
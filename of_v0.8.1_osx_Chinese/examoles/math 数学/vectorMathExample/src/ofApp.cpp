//04-25-2014
#include "ofApp.h"

//如何通过操纵一个不断旋转的坐标轴来绘制一个三维图形
//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync() 好像同步更新屏幕重绘和屏幕的垂直刷新
	ofSetVerticalSync(true);
    
	//设置旋转量和速度
	nPts = 0;
	rotateAmount.set(0,0,1);
	speedOfRotation = 0.5f;
    
	ofBackground(255,255,255);
	//定义中心
	ofVec3f center(ofGetWidth()/2, ofGetHeight()/2, 0);
    
	//设置一些坐标，xAxisMin, xAxisMax, yAxisMin, yAxisMax, zAxisMin, zAxisMax 都是ofVec3f
	//ofVec3f有三个变量， 很善于存储三维属性，比如说位置，速度，和加速度，
	xAxisMin.set(-100,0,0);
	xAxisMax.set(100,0,0);
	yAxisMin.set(0,-100,0);
	yAxisMax.set(0,100,0);
	zAxisMin.set(0,0,-100);
	zAxisMax.set(0,0,100);
    
	xAxisMin += center;
	xAxisMax += center;
	yAxisMin += center;
	yAxisMax += center;
	zAxisMin += center;
	zAxisMax += center;
    
	bDrawnAnything = false;     // added this cause theo saw this example
    // and was like "how do I tell zach that a rotating
    // cross is not that interesting ??"  before realizing
    // that one should draw :)
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // rotation occurs around 0,0,0 position.
    // since 0,0,0 is the top left corner, we need to:
    // (A) move over,
    // (B) rotate
    // (C) move back
    // this could all be one for loop, but broken out here for
    // clarity on the steps:
    
    //别忘了启发点永远在OF屏幕的左上角（0，0）而我们旋转的中心在屏幕的中心，所以需要移动到屏幕中心，旋转，然后回去。
    //其实可以用ofPushMatrix()/ofPushMatrix()得到一样的效果，但这个一步一步比较明确
    ofVec3f center(ofGetWidth()/2, ofGetHeight()/2,0);
    
    //move the points so that their center (ofGetW/2, ofGetH/2) is at 0,0,0
    for (int i = 0; i < nPts; i++){
        pts[i]-= center;
    }
    
    //rotate the points
    //旋转所有的顶点
    for (int i = 0; i < nPts; i++){
        pts[i] = pts[i].rotated(speedOfRotation, rotateAmount);
    }
    
    //move them back
    for (int i = 0; i < nPts; i++){
        pts[i]+= center;
    }
    
    //移动的方式都挺明显的
    xAxisMin -= center;
    xAxisMax -= center;
    yAxisMin -= center;
    yAxisMax -= center;
    zAxisMin -= center;
    zAxisMax -= center;
    
    xAxisMin.rotate(speedOfRotation, rotateAmount);
    xAxisMax.rotate(speedOfRotation, rotateAmount);
    yAxisMin.rotate(speedOfRotation, rotateAmount);
    yAxisMax.rotate(speedOfRotation, rotateAmount);
    zAxisMin.rotate(speedOfRotation, rotateAmount);
    zAxisMax.rotate(speedOfRotation, rotateAmount);
    
    xAxisMin += center;
    xAxisMax += center;
    yAxisMin += center;
    yAxisMax += center;
    zAxisMin += center;
    zAxisMax += center;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //设置背景颜色，但表填充，制造顶点
    ofSetHexColor(0x000000);
    ofNoFill();
    ofBeginShape();
    for (int i = 0; i < nPts; i++){
        ofVertex(pts[i].x, pts[i].y);
    }
    ofEndShape();
    
    //显示三个方向的旋转度
    string info = "speed of rotation (a/z): " + ofToString(speedOfRotation,3) + "\n" +
    "rotateAmount in x (s/x): " + ofToString(rotateAmount.x,3) + "\n" +
    "rotateAmount in y (d/c): " + ofToString(rotateAmount.y,3) + "\n" +
    "rotateAmount in z (f/v): " + ofToString(rotateAmount.z,3);
    
    
    //左上角的桔黄色方块
    ofFill();
    ofSetHexColor(0xE5A93F);
    ofRect(10,10,300,70);
    ofSetHexColor(0x000000);
    ofDrawBitmapString(info,30,30);
    
    
    //画线，这是openGL的构造方式
    ofSetColor(50,50,255);
    ofNoFill();
    ofBeginShape();
    ofVertex(xAxisMin.x, xAxisMin.y, xAxisMin.z);
    ofVertex(xAxisMax.x, xAxisMax.y, xAxisMax.z);
    ofEndShape();
    ofBeginShape();
    ofVertex(yAxisMin.x, yAxisMin.y, yAxisMin.z);
    ofVertex(yAxisMax.x, yAxisMax.y, yAxisMax.z);
    ofEndShape();
    ofBeginShape();
    ofVertex(zAxisMin.x, zAxisMin.y, zAxisMin.z);
    ofVertex(zAxisMax.x, zAxisMax.y, zAxisMax.z);
    ofEndShape();
    
	//刚开始的提示
    if (bDrawnAnything == false){
        ofSetColor(0,0,0);
        ofDrawBitmapString("draw something!", ofGetWidth()/2 + 100,ofGetHeight()/2 + 20);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
	//慢慢移动三个方向的坐标轴,也可以加速
    switch (key){
        case 'a':
            speedOfRotation += 0.05f;
            break;
        case 'z':
            speedOfRotation -= 0.05f;
            break;
        case 's':
            rotateAmount.x += 0.05f;
            break;
        case 'x':
            rotateAmount.x -= 0.05f;
            break;
        case 'd':
            rotateAmount.y += 0.05f;
            break;
        case 'c':
            rotateAmount.y -= 0.05f;
            break;
        case 'f':
            rotateAmount.z += 0.05f;
            break;
        case 'v':
            rotateAmount.z -= 0.05f;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    bDrawnAnything = true;
    //托运鼠标到达的每一点都被添加为新的顶点，
    if (nPts < MAX_N_PTS){       //MAX_N_PTS 被定义为1500在ofApp.h里
        pts[nPts].x = x;
        pts[nPts].y = y;
        nPts++;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //删除然后重新开始
    nPts = 0;
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

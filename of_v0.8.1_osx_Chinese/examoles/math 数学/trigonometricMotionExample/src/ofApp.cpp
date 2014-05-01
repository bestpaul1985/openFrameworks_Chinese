//首先熟悉ofPushMatrix()/ofPopMatrix()的用法

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//设置圆圈分辨率
	ofSetCircleResolution(40);
	
	//our history arrays are initialized with a value of zero for all of it's elements.
	//首先设置为0
	for (int i=1; i<TAIL_LENGTH; i++) {
		waveHistory[i] = ofVec3f(0, 0, 0);
	}
	for (int i=1; i<WAVEFORM_HISTORY; i++) {
		horWaveHistory[i] = 0;
		vertWaveHistory[i] = 0;
	}
	
	//our center point is defined here.
	//中心点的定义
	center= ofPoint((ofGetWidth()-LEFT_MARGIN)*0.5f +LEFT_MARGIN,
                    (ofGetHeight()-TOP_MARGIN)*0.5f + TOP_MARGIN);
	
	
	bScaleMouse=false;
	
	//比例系数
	scale=1;
	
	//this are the multipliers for scaling the horizontal and vertical waveforms so this fit into the screen.
	//横行和垂直波型的缩放倍数，根据屏幕大小
	hWaveMult=(ofGetWidth()-LEFT_MARGIN)/float(WAVEFORM_HISTORY);
	vWaveMult=(ofGetHeight()-TOP_MARGIN)/float(WAVEFORM_HISTORY);
	
	//这些定义都在ofApp.h里面
	selectedOscilator=-1;
	bSelectedOscHor = false;
	bSelectedOscVert = false;
	
	//使用平滑，混色，ofSetVerticalSync() 好像同步更新屏幕重绘和屏幕的垂直刷新
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	//更新所有的水平振荡器
	for (unsigned int i=0; i<horizontalOscilators.size(); i++) {
		horizontalOscilators[i].update();
	}
	//更新所有的垂直振荡器
	for (unsigned int i=0; i<verticalOscilators.size(); i++) {
		verticalOscilators[i].update();
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//设置背景颜色
	ofBackgroundGradient(ofColor(245), ofColor(200));
	//ofSetLineWidth(1);
	
	//The following is just to print the instructions to the screen.
    
	//显示一些说明
	ofSetColor(80);
    //在左上角显示指挥，“点击此处添加水平振荡器"
	ofDrawBitmapString("Click here to add horizontal oscillators.", LEFT_MARGIN +100, TOP_MARGIN-5 );
	
	ofDrawBitmapString("Click and drag\nover an\noscillator to\nmodify it's\nspeed and\namplitude", 15,25);
	ofDrawBitmapString("Click in this area and drag upwards/downwards to scale up/down.\nPress spacebar to delete all the oscillators.", LEFT_MARGIN + 200, ofGetHeight()-40);
	
	//All this bunch is to print the vertical text
	//在左下角显示指挥，“点击此处添加垂直振荡器"
	ofPushMatrix();
	ofTranslate(LEFT_MARGIN -5,  ofGetHeight() - 100, 0);
	ofRotate(-90, 0, 0, 1);
	ofDrawBitmapString("Click here to add vertical oscillators.",  0, 0 );
	ofPopMatrix();
	
	
	
	
	ofEnableSmoothing();
	
	//This are just the reference lines draw in the screen.
	//一些分离空间的线
	ofSetColor(0, 0, 0, 150);
	ofLine(LEFT_MARGIN, 0, LEFT_MARGIN, ofGetHeight());
	ofLine(0, TOP_MARGIN, ofGetWidth(), TOP_MARGIN);
	
	ofSetColor(0, 0, 0, 80);
	ofLine(LEFT_MARGIN, center.y, ofGetWidth(), center.y);
	ofLine(center.x, TOP_MARGIN, center.x, ofGetHeight());
	
	//ofSetLineWidth(2);
	
	
	//看下面解释
	float horWave = 0;
	float vertWave = 0;
	
	//here we go through all the horizontal oscillators
	//所有的水平振荡器
	for (unsigned int i=0; i<horizontalOscilators.size(); i++) {
		ofSetColor(255, 127+i, 0,150);
		//画振荡器,也就是桔黄色的圆圈是由oscillator class自己画得
		horizontalOscilators[i].draw();
		//集合所有的正弦，没什么理论的根据好像
		horWave += horizontalOscilators[i].waveSin;
		//THIS IS IMPORTANT. Here we are adding together all the current sine values of each oscillator.
		// This is what is creates all the crazy motion that we get.
        
	}
	//the same as above but for vertical oscillators
	//所有的垂直振荡器，算法和上面的一模一样
	for (unsigned int i=0; i<verticalOscilators.size(); i++) {
		ofSetColor(0, 127+i, 255, 150);
		//画振荡器，也就是说蓝色的圆圈是由oscillator class自己画得
		verticalOscilators[i].draw();
		//集合所有的正弦
		vertWave += verticalOscilators[i].waveSin;
	}
	//here we move all the elements of the array one position forward so to make space for a new value.
	//把所有波音往前移动一步
	for (int i=1; i<TAIL_LENGTH; i++) {
		waveHistory[i-1] = waveHistory[i];
	}
	for (int i=1; i<WAVEFORM_HISTORY; i++) {
		horWaveHistory[i-1] = horWaveHistory[i];
		vertWaveHistory[i-1]= vertWaveHistory[i];
	}
	//here we save into our history
	//添加新的波音
	horWaveHistory[WAVEFORM_HISTORY-1] = horWave;
	vertWaveHistory[WAVEFORM_HISTORY-1] = vertWave;
	waveHistory[TAIL_LENGTH-1] = ofVec3f(horWave, vertWave,0);
	
	
	//wave代表振荡器运动时产生的一条路线
	ofMesh wave; // declaring a new ofMesh object with which we're drawing the motion path created by summing the vertical and horizontal oscillators
	wave.setMode(OF_PRIMITIVE_LINE_STRIP);
	for (int i=0; i<TAIL_LENGTH; i++) {
		wave.addColor(ofFloatColor(0.1f,0.1f,0.1f, 0.5f + 0.5f * i/float(TAIL_LENGTH) ));
		wave.addVertex(waveHistory[i]);
	}
	
	//all the following is to create and populate the horizontal and vertical waveforms.
	//存储所有水平和垂直振荡器达到过的地点
	ofMesh hWave;
	hWave.setMode(OF_PRIMITIVE_LINE_STRIP);
	ofMesh vWave;
	vWave.setMode(OF_PRIMITIVE_LINE_STRIP);
	for (int i=0; i<WAVEFORM_HISTORY; i++) {
		hWave.addColor(ofFloatColor(255, 240,10, 255));
		hWave.addVertex(ofVec3f(i*hWaveMult, horWaveHistory[i]*0.1f*scale, 0));
		vWave.addColor(ofFloatColor(255, 240,10, 255));
		vWave.addVertex(ofVec3f(vertWaveHistory[i]*0.1f*scale, i*vWaveMult, 0));
	}
	
	//draw the vertical and horizontal wave.
	//绘制垂直和水平波
	ofPushMatrix();
	ofTranslate(LEFT_MARGIN, TOP_MARGIN, 0);
	hWave.draw();           //画白色的横行波音
	vWave.draw();           //画白色的直行波音
	ofPopMatrix();
	
	//draw the composite wave.
	//绘制复合波。
	ofPushMatrix();
	ofTranslate(center.x, center.y, 0);
	ofScale(scale, scale, 0);
	wave.draw();
	ofSetColor(0,10, 255),
    //蓝色的球带领波音
	ofCircle(horWave, vertWave, 10);
	ofPopMatrix();
	
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
	//按下空格键将清除所有的振荡器
	if (key == ' ') {//when the spacebar is pressed the vectors that contain all the oscillators are cleared.
		horizontalOscilators.clear();
		verticalOscilators.clear();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//点击或拖动振荡器将改变它的频率和振幅
	if (selectedOscilator>-1) {//when an oscillator is clicked and dragged it's speed (freq) and amplitude are changed.
		//the following lines do so.
		if(bSelectedOscHor==true){
			horizontalOscilators[selectedOscilator].freq += 0.1f * (ofGetPreviousMouseX() - ofGetMouseX())/ float(ofGetWidth());
			horizontalOscilators[selectedOscilator].amplitude += ofGetMouseY() - ofGetPreviousMouseY();
		}else if (bSelectedOscVert==true) {
			verticalOscilators[selectedOscilator].freq += 0.1f * (ofGetPreviousMouseY() - ofGetMouseY())/ float(ofGetHeight());
			verticalOscilators[selectedOscilator].amplitude += ofGetMouseX() - ofGetPreviousMouseX();
		}
	}else if (bScaleMouse) {
		scale += float(ofGetMouseY()-ofGetPreviousMouseY())/ofGetHeight();
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	if (y< TOP_MARGIN && x>LEFT_MARGIN) {
		//水平振荡器一个一个检查是否被电击
		for (unsigned int i = 0; i < horizontalOscilators.size(); i++) {//this goes through the horizontal oscillators checking if anyone has been clicked over.
			if(horizontalOscilators[i].checkOver(x, y)){
				setPressedOscilator(i, true);
				break;
			}
		}
		//如果没有点击存在的水平振荡器，就在鼠标的位置添加一个新的
		if (!bSelectedOscHor) {//in case that no oscillator was clicked then create a new one at the position of the mouse.
			horizontalOscilators.push_back(oscillator());
			horizontalOscilators.back().setup(x, y);
		}
	}else if(y>TOP_MARGIN && x<LEFT_MARGIN){
		//垂直振荡器一个一个检查是否被电击
		for (unsigned int i = 0; i < verticalOscilators.size(); i++) {
			if(verticalOscilators[i].checkOver(x, y)){
				setPressedOscilator(i, false);
				break;
			}
		}
		//如果没有点击存在的垂直振荡器，就在鼠标的位置添加一个新的
		if (!bSelectedOscVert) {
			verticalOscilators.push_back(oscillator());
			verticalOscilators.back().setup(x, y);
		}
	}else {
		bScaleMouse=true;
	}
}
//--------------------------------------------------------------
void ofApp::setPressedOscilator(int index, bool isHorizontal){
	selectedOscilator=index;
	bSelectedOscHor =isHorizontal;
	bSelectedOscVert =!isHorizontal;
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	bScaleMouse=false;
	selectedOscilator=-1;
	bSelectedOscHor=false;
	bSelectedOscVert=false;
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

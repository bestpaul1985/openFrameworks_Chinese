//04-25-2014
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//trail是一个vector<ofPolyline>, ofPolyline 是一个通过一组点联合起来到的一条线，并可以和其他的ofPolyLine集合起来。比ofPath简单一点，而且容易操纵，可以移动或者增加顶点来改变形状
	//
	trail.resize(8);
	y.resize(8);
    
	//一些图形的数据，位置，半径
	x = 0;
	prevX = 0;
	y[0] = 60*2;
	radius = 3;
	rightMargin = 190;
	
	//是否显示位置
	showPos = false;
	
	//yFactor是一个滑块（ofxSimpleSlider), 控制噪音的振幅，setup() 需要最高值，最低值，和一些尺寸
	yFactor.setup(130, 20, 100, 20,0,30,20,false, false);
	yFactor.setLabelString("y amnt");
	
    //speed是一个滑块（ofxSimpleSlider), 控制噪音的横行速度，setup() 需要最高值，最低值，和一些尺寸
	speed.setup(130, 45, 100, 20,1,200,30,false, false);
	speed.setLabelString("x speed (px/s)");
	
    //freq是一个滑块（ofxSimpleSlider)，控制瓶绿，setup() 需要最高值，最低值，和一些尺寸
	freq.setup(130, 70, 100, 20,0,10,1,false, false);
	freq.setLabelString("frequency (hz)");
	
	//ofSetVerticalSync()-同步更新屏幕重绘和屏幕的垂直刷新
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	ofSetColor(20);
	
    //保存初始速度
	preSpeed = speed.getValue();
}

//--------------------------------------------------------------
void ofApp::update(){
    
	//if the speed has changed we need to clear the lines.
    // we can't test for float equality or non-equality
    // (speed.getValue() != preSpeed)
    // so we look at the change and if the change is greater then a certain
    // amount we clear.
    
	//没法测试float数字的平等，所以只能去衡量他们的差别
	if( fabs(speed.getValue() - preSpeed) > 0.00001f ){
		speedChanged();
	}
    
    //更新速度
	preSpeed = speed.getValue();
    
	//更新时间，只有在一开始和每次删除后纪录initTime
	t = ofGetElapsedTimef();
	if(trail[0].size()==0){
		initTime = t;
	}
	t = t - initTime;
    
	//计算x坐标, 一旦信号达到右边界 (rightMargin)，它会从左边重新环绕，所以必须取它处于长度的余数
	x = int(t*speed.getValue())%(ofGetWidth()-rightMargin);
    
    //各种不同形状的噪音, 有些利用perlin杂
    //而且随机数不能由时间或者频率有关
	y[1] = 60*3+ofNoise(t*freq.getValue())*yFactor.getValue();
	y[2] = 60*4+ofSignedNoise(t*freq.getValue())*yFactor.getValue();
	y[3] = 60*5+ofRandom(-1,1)*yFactor.getValue(); // random can't be dependent on time or frequency
	y[4] = 60*6+sin(t*freq.getValue()*TWO_PI)*yFactor.getValue();
	y[5] = 60*7+(sin(t*freq.getValue()*TWO_PI)+1)*.5*yFactor.getValue();
	y[6] = 60*8+fmod(t*freq.getValue(),1)*yFactor.getValue();
	y[7] = 60*9+(fmod(t*freq.getValue(),1)*2-1)*yFactor.getValue();
    
    //和上面的逻辑差不多，刚才用更新的x坐标来计算y坐标，现在涉及到ofPolyline的构造，到了边界以后必须删除所有的顶点然后从心开始
	for(int i=0;i<(int)trail.size();i++){
		if(x<prevX){
			trail[i].clear();
		}else{
			trail[i].addVertex(ofPoint(x,y[i]));
		}
	}
    
	prevX = x;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //设置背景颜色
	ofBackgroundGradient(ofColor(240),ofColor(210),OF_GRADIENT_BAR);
    
	//画噪音和有关数据
	ofSetColor(170);
	for(int i=0;i<(ofGetWidth()-rightMargin)/speed.getValue();i++){
		ofLine(i*speed.getValue(),120,i*speed.getValue(),ofGetHeight());
		//是否显示位置
		if(showPos)
			ofDrawBitmapString(ofToString(i)+"s",i*speed.getValue(),ofGetHeight()-20);
		else
			ofDrawBitmapString(ofToString(i*speed.getValue(),0)+"p",i*speed.getValue(),ofGetHeight()-20);
	}
    
	ofSetColor(20);
    
    //画右边的直边界线
	ofLine(ofGetWidth()-rightMargin,0,ofGetWidth()-rightMargin,ofGetHeight());
    
    //所有的噪音
	for(int i=0;i<(int)trail.size();i++){
		ofEnableSmoothing();
        //画线头的圆圈, 再画代表噪音的线
		ofCircle(x,y[i],radius);
		trail[i].draw();
        
		//禁止平滑
		ofDisableSmoothing();
		ofLine(0,60*(i+2),ofGetWidth(),60*(i+2));
        
        //画上下摆动的方块
		float rectY = 60*(i+2);
		ofRect(ofGetWidth()-rightMargin+10,rectY,10,y[i]-rectY);
	}
    
	//显示一些标题
	ofDrawBitmapString("constant",ofGetWidth()-160,60*2-4);
	ofDrawBitmapString("ofNoise(t)",ofGetWidth()-160,60*3-4);
	ofDrawBitmapString("ofSignedNoise(t)",ofGetWidth()-160,60*4-4);
	ofDrawBitmapString("ofRandom(-1,1)",ofGetWidth()-160,60*5-4);
	ofDrawBitmapString("sin(TWO_PI*t)",ofGetWidth()-160,60*6-4);
	ofDrawBitmapString("(sin(TWO_PI*t)+1)/2",ofGetWidth()-160,60*7-4);
	ofDrawBitmapString("modulo(t,1)",ofGetWidth()-160,60*8-4);
	ofDrawBitmapString("modulo(t,1)*2-1",ofGetWidth()-160,60*9-4);
    
    //显示帧率，时间，位置
	ofDrawBitmapString("fps:" + ofToString(ofGetFrameRate(),0),ofGetWidth()-80,20);
	ofDrawBitmapString("t:" + ofToString(t,2),ofGetWidth()-80,35);
	ofDrawBitmapString("x:" + ofToString(x,2),ofGetWidth()-80,50);
    
}

//--------------------------------------------------------------
//改变速度后必须删除数据，重新计算交叉点
void ofApp::speedChanged(){
	for(unsigned int i=0;i<trail.size();i++){
		trail[i].clear();
	}
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

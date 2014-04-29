#pragma once

#include "ofMain.h"

//The following defines are called preprocessor directives.
//This are just to make the programmers life easier.
//This are actually not compiled, instead whenever you use a defined directive it gets replaced by it's associated value in the source code BEFORE it compiles.
//So this don't use memory space and if you are using this directives a lot it's easier and faster to change it's value.

//假定你会C++,知道directives的功能
#define TOP_MARGIN 150
#define LEFT_MARGIN 150

#define WAVEFORM_HISTORY 800
#define TAIL_LENGTH 400

//this is our oscillator class.
//This defines how to save, update and draw each oscillators properties and values.
//这是我们的振荡器，它定义如何保存，如何更新和绘制每个振荡器的属性和值
class  oscillator {
public:
	
	//振荡器的有关数据
	float freq;			//频率
	float waveSin;		//正弦
	float waveCos;		//余弦
	float amplitude;	//振幅
	float phase;		//波相
	double counter;		//计数
	
	ofVec2f pos;
	
	oscillator(){}
	~oscillator(){}
    
	//每次制造新的振荡器都需要这个函数
	void setup(int x, int y){//this function initializes all the properties of the oscillator. It must be called just after creating a new oscillator.
		
		//（x,y) 代表位置
		pos.set(x, y);//sets the position of the oscillator using the values passed to the function. In this case is the position where the mouse was clicked.
		
		// 随机频率
		freq = ofRandom(0.0001f, 0.1f);// the frequency get's initialized with a random value.
		
		counter = 0;
		// 根据位置决定是水平的还是垂直的振荡器
		if (y<TOP_MARGIN) {//this if is to determine if the oscillator is either an horizontal or vertical oscillator.
			//phase和amplitude都有位置来决定
			phase = ofMap(x-LEFT_MARGIN, LEFT_MARGIN, ofGetWidth(), -PI, PI, false);//the phase is defined by to position of the locator.Here it's value gets remaped to the correct range.
			amplitude = ofMap(y, 0, TOP_MARGIN, 0.1f, 300, false);//Amplitude is defined by the position, and it's value gets remaped to the correct range.
			
		}else {
			phase = ofMap(y-TOP_MARGIN, TOP_MARGIN, ofGetHeight(), -PI, PI, false);
			amplitude = ofMap(x, 0, LEFT_MARGIN, 0.1f, 300, false);
		}
	}
	
	void update(){
		counter += freq;//the counter is incremented by the value of freq each time the oscillators update methods is called.
		//必须乘以振幅因为sin()在0至1范围
		waveSin = sin(counter + phase) * amplitude;//Here is where we calulate the sine value for the oscillator.
		//Then is multiplied by amplitude, because the sin() function returns a value between -1 and 1
		//同样必须乘以政府
		waveCos = cos(counter + phase) * amplitude;
	}
	
	//画振荡器
	void draw(){//here we draw the oscillator
		//填充形状
		ofFill();
		//画圆圈
		ofCircle(pos.x, pos.y, amplitude/4);
		ofSetColor(40);
		ofNoFill();
		//画中心
		ofCircle(pos.x, pos.y, amplitude/4);
		//画指针
		ofLine(pos.x, pos.y, pos.x +  waveCos/4, pos.y + waveSin/4);
	}
    
	//检查鼠标是否停在振荡器
	bool checkOver(int x, int y){//this is to check if the mouse is over the oscillator.
		if (pos.distance(ofVec2f(x,y)) <amplitude*0.25) {
			return true;
		}else{
			return false;
		}
	}
};



class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setPressedOscilator(int index, bool isHorizontal);
    
    //所有的水平振荡器
    vector<oscillator>horizontalOscilators; //In this vector object we're going to save our horizontal oscillators.
    //所有的垂直振荡器
    vector<oscillator>verticalOscilators;   //In this vector object we're going to save our vertical oscillators.
    //所有经过的位置，用来构造波音的路线
    ofVec3f waveHistory [TAIL_LENGTH]; // This array object is to save the previous positions of the composite wave we're creating, so we can draw it's path later.
    
    //水平波音的历史
    float horWaveHistory [WAVEFORM_HISTORY];//This and the following array are for saving the wave form history.
    //垂直波音的历史
    float vertWaveHistory [WAVEFORM_HISTORY];
    
    //波音的中心
    ofPoint center; //This is to store the center location for the composite wave .
    //波音的比例系数
    float scale; // the amount by which the waveforms get scaled.
    //是否用鼠标更改比例系数
    bool bScaleMouse;//just to know that you're using the mouse to change the scale.
    
    float hWaveMult;//this are to scale or multiply the vertical and horizontal waveforms.
    float vWaveMult;
    
    //振荡器排列位置
    int selectedOscilator; //this stores the clicked oscillator position within the vector when it's being pressed.
    //被点击的振荡器是否是横行的
    bool bSelectedOscHor; //when you click over an oscillator this boolean indicates whether it was one of the horizontal oscillators or not.
    //被点击的振荡器是否是垂直的
    bool bSelectedOscVert;//when you click over an oscillator this boolean indicates whether it was one of the vertical oscillators or not.
};

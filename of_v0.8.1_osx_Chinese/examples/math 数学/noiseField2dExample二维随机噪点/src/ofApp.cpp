/*
 This example demonstrates how to use a two dimensional slice of a three
 dimensional noise field to guide particles that are flying around. It was
 originally based on the idea of simulating "pollen" being blown around by
 the wind, and implemented in the Processing:
 http://www.openprocessing.org/visuals/?visualID=2785
 
 通过这个例子，能够学习到如何通过噪点来模拟花粉被风吹散的效果。
 
 Processing版本：
 http://www.openprocessing.org/visuals/?visualID=2785
 
 */

#include "ofApp.h"

/*
 All these settings control the behavior of the app. In general it's a better
 idea to keep variables in the .h file, but this makes it easy to set them at
 the same time you declare them.
 
 一般来说变量最好是写在.h文件里，但是为了更方便的调整这个应用，我们把一些变量写在这里：
 */

int nPoints = 4028;		// points to draw
                        // 点点的数量

float complexity = 6;	// wind complexity
                        // 风的复杂度

float pollenMass = .8;	// pollen mass
                        // 花粉的重量

float timeSpeed = .02;	// wind variation speed
                        // 风的变化速度

float phase = TWO_PI;	// separate u-noise from v-noise
                        // 层次，用于分开噪点的u和v

float windSpeed = 40;	// wind vector magnitude for debug
                        // 风的速度

int step = 10;			// spatial sampling rate for debug
                        // 空间采样率
bool debugMode = false;

/*
 This is the magic method that samples a 2d slice of the 3d noise field. When
 you call this method with a position, it returns a direction (a 2d vector). The
 trick behind this method is that the u,v values for the field are taken from
 out-of-phase slices in the first dimension: t + phase for the u, and t - phase
 for the v.
 
 这是非常的神奇方法让你可以通过一个由噪点控制的，不断变化的力场，计算出所在位置的移动方向。
 当你使用这个方式的时候，你只需要输入位置的坐标，这个力场就会给到你一个方向。
 这个方法背后的秘密是：用位置和时间建立起来的三维力场来取得一个u和v值，同时用层次参数区分开u和v
 */

//--------------------------------------------------------------
//用perlinz杂来制造一个矢量场
ofVec2f ofApp::getField(ofVec2f position) {
    
	// ofNormalize()只不过把一个数字在最小和最大的范围内重新规范为0至1
	float normx = ofNormalize(position.x, 0, ofGetWidth());
	float normy = ofNormalize(position.y, 0, ofGetHeight());
    
	// 这些计算没什么理论的根据不要看得太细，致使试验后表现出最有趣的图案
	float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
	float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
	return ofVec2f(u, v);
    
}

//--------------------------------------------------------------
void ofApp::setup() {
    
	// ofSetVerticalSync()-同步更新屏幕重绘和屏幕的垂直刷新
	ofSetVerticalSync(true); // don't go too fast
    // 嘿！机器不好就别跑太快
    
	// 使用混色
	ofEnableAlphaBlending();
	
	// randomly allocate the points across the screen
    // 随机设置点点在屏幕上的位置
    points.resize(nPoints);
    for(int i = 0; i < nPoints; i++) {
        points[i] = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
    }
	
	// we'll be drawing the points into an ofMesh that is drawn as bunch of points
    // 把点点都放到一个ofMesh里，然后画出ofMesh
	cloud.clear();
    
	// OF_PRIMITIVE_POINTS意思是通过点点来构造mesh, primitive 也可以用线代表
	cloud.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update() {
	width = ofGetWidth(), height = ofGetHeight();
    t = ofGetFrameNum() * timeSpeed;
    for(int i = 0; i < nPoints; i++) {
		float x = points[i].x, y = points[i].y;
		ofVec2f field = getField(points[i]); // get the field at this position
        // 输入在力场中所处的坐标
        
		// use the strength of the field to determine a speed to move
        // 使用力场的强度来确定移动速度
		// the speed is changing over time and velocity-space as well
        // 速度和速度变化范围都会不断变化
        float speed = (1 + ofNoise(t, field.x, field.y)) / pollenMass;
        
		// add the velocity of the particle to its position
        // 把点点的速度加到它的位置中
        
		// float ofLerp(float start, float stop, float amt) 是一个很有用的函数，它在启动点(start)和停止点(stop)之间每步增加amt
		x += ofLerp(-speed, speed, field.x);
		y += ofLerp(-speed, speed, field.y);
        
		// if we've moved outside of the screen, reinitialize randomly
        // 如果点点移动到窗口之外了，就随机初始化
		if(x < 0 || x > width || y < 0 || y > height) {
			x = ofRandom(0, width);
			y = ofRandom(0, height);
		}
        
		// save the changes we made to the position
        // 更新点点位置
		points[i].x = x;
		points[i].y = y;
        
		// add the current point to our collection of drawn points
        // 把点点加入向量
		cloud.addVertex(ofVec2f(x, y));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(255);
    if(debugMode) {
        ofSetColor(0);
        
		// draw a vector field for the debug screen
        // 显示力场，用于调试
        for(int i = 0; i < width; i += step) {
            for(int j = 0; j < height; j += step) {
                ofVec2f field = getField(ofVec2f(i, j));
				
				//理解为什么需要ofPushMatrix()/ofPopMatrix()
                ofPushMatrix();
                ofTranslate(i, j);
				ofSetColor(0);
                ofLine(0, 0, ofLerp(-windSpeed, windSpeed, field.x), ofLerp(-windSpeed, windSpeed, field.y));
                ofPopMatrix();
            }
        }
        
		// draw the points as circles
        // 画出点点
		ofSetColor(ofColor::red);
		for(int i = 0; i < nPoints; i++) {
            ofCircle(points[i], 2);
		}
    } else {
        
		// when not in debug mode, draw all the points to the screen
        // 让我们画出花粉被风吹散的效果吧！当然，如果是不在调试模式下的话。
        ofSetColor(0, 10);
		cloud.draw();
	}
	
	ofDrawBitmapStringHighlight("click to reset\nhit any key for debug", 10, 10, ofColor::white, ofColor::black);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
	// when you hit a key, draw the debug screen
    // 点击任意按键切换到调试模式
    debugMode = !debugMode;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
	// when you click the mouse, reset all the points
    // 如果点击鼠标，重置所有的点点
    setup();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

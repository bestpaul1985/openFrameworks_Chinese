/*
 This example demonstrates how to use a two dimensional slice of a three
 dimensional noise field to guide particles that are flying around. It was
 originally based on the idea of simulating "pollen" being blown around by
 the wind, and implemented in the Processing:
 http://www.openprocessing.org/visuals/?visualID=2785
 
 这个例子说明了如何用三维领域中的二维切片去指导一群飞舞的粒子。这个例子是原创性地基于模拟被风吹散的“花粉”，
 你还可以看到一个Processing的例子： http://www.openprocessing.org/visuals/?visualID=2785。
 */

#include "testApp.h"

/*
 All these settings control the behavior of the app. In general it's a better
 idea to keep variables in the .h file, but this makes it easy to set them at
 the same time you declare them.
 这些设置控制整个应用的表现方式。总的来说，如果在.h文件里面保存这些变量会比较好，但是把变量写在这里会更容易去设置他们。
 */
int nPoints = 4096; // points to draw 要画的点
float complexity = 6; // wind complexity 风的复杂度
float pollenMass = .8; // pollen mass 花粉的质量
float timeSpeed = .02; // wind variation speed 风的变化速度
float phase = TWO_PI; // separate u-noise from v-noise 从 v-随机噪点中分离 u-随机噪点
float windSpeed = 40; // wind vector magnitude for debug 调试用风的向量大小
int step = 10; // spatial sampling rate for debug 调试用空间率
bool debugMode = false;

/*
 This is the magic method that samples a 2d slice of the 3d noise field. When
 you call this method with a position, it returns a direction (a 2d vector). The
 trick behind this method is that the u,v values for the field are taken from
 out-of-phase slices in the first dimension: t + phase for the u, and t - phase
 for the v.
 
 这是一个魔术般的的方法，它从3d的噪点场中采集2d的切片。当你用一个位置坐标去激活这个方法时，它会返回一个方向（一个2d的矢量）。
 这个方式背后的窍门是这个场中的u,v数值取自一纬空间里的外层切片；t+层用于u， 和 t-层用于v。
 */
//--------------------------------------------------------------
ofVec2f testApp::getField(ofVec2f position) {
	float normx = ofNormalize(position.x, 0, ofGetWidth());
	float normy = ofNormalize(position.y, 0, ofGetHeight());
	float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
	float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
	return ofVec2f(u, v);
}

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true); // don't go too fast 不会跑的太快
	ofEnableAlphaBlending();
	
	// randomly allocate the points across the screen 在屏幕上随机放置点点
  points.resize(nPoints);
  for(int i = 0; i < nPoints; i++) {
    points[i] = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
  }
	
	// we'll be drawing the points into an ofMesh that is drawn as bunch of points 我们会画一些点点到ofMesh里面，然后这个ofMesh会画一堆点点
	cloud.clear();
	cloud.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void testApp::update() {
	width = ofGetWidth(), height = ofGetHeight();
  t = ofGetFrameNum() * timeSpeed;
  for(int i = 0; i < nPoints; i++) {
		float x = points[i].x, y = points[i].y;
		ofVec2f field = getField(points[i]); // get the field at this position 得到所在位置的场
		// use the strength of the field to determine a speed to move 使用场的强度来确定移动速度
		// the speed is changing over time and velocity-space as well  速度和加速空间都会不断变化
    float speed = (1 + ofNoise(t, field.x, field.y)) / pollenMass;
		// add the velocity of the particle to its position 把粒子的坐标和加速度相加
    x += ofLerp(-speed, speed, field.x);
    y += ofLerp(-speed, speed, field.y);
		// if we've moved outside of the screen, reinitialize randomly  如果点点已经移动到屏幕之外了，就随机初始化
    if(x < 0 || x > width || y < 0 || y > height) {
      x = ofRandom(0, width);
      y = ofRandom(0, height);
    }
		// save the changes we made to the position 保存我们对点点位置的改变
    points[i].x = x;
    points[i].y = y;
		// add the current point to our collection of drawn points 把新的点点加到我们需要画的点点矢量里
		cloud.addVertex(ofVec2f(x, y));
	}
} 

//--------------------------------------------------------------
void testApp::draw() {
	ofBackground(255);
  if(debugMode) {
    ofSetColor(0);
		// draw a vector field for the debug screen 绘制出矢量场用于调试屏幕
    for(int i = 0; i < width; i += step) {
      for(int j = 0; j < height; j += step) {
				ofVec2f field = getField(ofVec2f(i, j));
        ofPushMatrix();
        ofTranslate(i, j);
				ofSetColor(0);
        ofLine(0, 0, ofLerp(-windSpeed, windSpeed, field.x), ofLerp(-windSpeed, windSpeed, field.y));
        ofPopMatrix();
      }
    }
		// draw the points as circles 用圆形作为绘制的点
		ofSetColor(ofColor::red);
		for(int i = 0; i < nPoints; i++) {
      ofCircle(points[i], 2);
		}
  } else {
		// when not in debug mode, draw all the points to the screen 如果不是在调试模式，绘制所有的点点到屏幕上
    ofSetColor(0, 10);
		cloud.draw();
	}
	
	ofDrawBitmapStringHighlight("click to reset\nhit any key for debug", 10, 10, ofColor::white, ofColor::black);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	// when you hit a key, draw the debug screen 如果你点击一个按键，切换到调试模式
  debugMode = !debugMode;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	// when you click the mouse, reset all the points 如果点击鼠标，重置所有的点点
  setup();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

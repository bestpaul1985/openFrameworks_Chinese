//4-25-2014
//disclaimer: some of the functionalities I'm not even certain how to describe in English.  Make sure you understand how ofPushMatrix()/ofPupMatrix() works

//首先熟悉ofPushMatrix() 和 ofPopMatrix() 的功能

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    //设置标题，背景颜色，圆圈分辨率， ofSetVerticalSync() 同步更新屏幕重绘和屏幕的垂直刷新
	ofSetWindowTitle("Noise 1D Example");
	ofBackground(215,215,215);
	ofSetVerticalSync(true);
	ofSetCircleResolution(256);
	
	setupSignedNoiseDemo();
}

//--------------------------------------------------------------
//设置一些数据
void ofApp::setupSignedNoiseDemo(){
    
	// Setup and allocate resources used in the signed noise demo.
	// 设置并分配在随机噪点例子中需要的资源
    
    // 存储400个数字的历史纪录
	nSignedNoiseData = 400;
	signedNoiseData = new float[nSignedNoiseData];
	for (int i=0; i<nSignedNoiseData; i++){
		signedNoiseData[i] = 0;
	}
	
	// Some coordinates...
    // 看下面解释
	radialNoiseDemoY = 200;
	radialNoiseDemoR = 100;
	radialNoiseDemoX = ofGetWidth()/2 - radialNoiseDemoR;
	
	// These 2 sliders control the noise waveform at the top.
    // radialNoiseStepSlider 和 radialNouseAmoundSlider  两个滑块控制噪声的波形， step 主要控制波音的速度， amount 主要控制波音的振幅, 都由鼠标控制
	radialNoiseStepSlider.setup(radialNoiseDemoX,   radialNoiseDemoY+150, 200,16, 0.010, 0.150, 0.05, false,true);
	radialNoiseAmountSlider.setup(radialNoiseDemoX, radialNoiseDemoY+170, 200,16, 0.000, 1.000, 0.40, false,true);
	
    // 图形的标签
	radialNoiseStepSlider.setLabelString(  "Noise Step");
	radialNoiseAmountSlider.setLabelString("Noise Amount");
	radialNoiseStepSlider.setNumberDisplayPrecision(3);
	radialNoiseCursor = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    // 一切从这里开始
	updateSignedNoiseDemo();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // 画背景，画信号和数据，画机械手臂
    // OF_GRADIENT_CIRCULAR - 使用圆形渐变性的色彩
    
	ofBackgroundGradient( ofColor(255), ofColor(180), OF_GRADIENT_CIRCULAR);
	renderSignedNoiseDemo();
	renderNoisyRobotArmDemo();
}



//--------------------------------------------------------------
void ofApp::updateSignedNoiseDemo (){
	
	// Shift all of the old data forward through the array
    // 把数据往矩阵头移动一步
	for (int i=(nSignedNoiseData-1); i>0; i--){
		signedNoiseData[i] = signedNoiseData[i-1];
	}
	
	// Compute the latest data, and insert it at the head of the array.
	// Here is where ofSignedNoise is requested.
    // 计算噪音量, 然后插入道矩阵的头部
	float noiseStep    = radialNoiseStepSlider.getValue();
	float noiseAmount  = radialNoiseAmountSlider.getValue();
	
    // 计算perlin杂， 范围在－1 到 1 之间
	signedNoiseData[0] = noiseAmount * ofSignedNoise( radialNoiseCursor );
	radialNoiseCursor += noiseStep;
}


//--------------------------------------------------------------
void ofApp::renderNoisyRobotArmDemo(){
    
	// 计算机械手臂各部分（肩膀，弯头，腕）的角度, ofNoise() 和ofSignedNoise() 的区别在于ofNoise() 范伟在 0 到 1 之间
	float t = ofGetElapsedTimef();
	float shoulderNoiseAngleDegrees = 90 + 70.0 * ofSignedNoise(t * 1.00);
	float elbowNoiseAngleDegrees    = 60 + 80.0 * ofSignedNoise(t * 0.87);
	float wristNoiseAngleDegrees	= (2.5 * 72) + 45.0 * ofSignedNoise(t * 1.13);
	
    // perlin杂用不同的倍数，否则只会显示出灰色的各种色调
	float noisyR = ofNoise(t * 0.66); // different multiplicative step-factors
	float noisyG = ofNoise(t * 0.73); // guarantee that our color channels are
	float noisyB = ofNoise(t * 0.81); // not all (apparently) synchronized.
	
    
    // 启用平滑，使颜色混合，调整分辨率，调整线的粗细
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetCircleResolution(12);
	ofSetLineWidth(1.0);
	
    // ofPushMatrix()／ofPopMatrix() 是OF最通常的一个技巧，ofPushMatrix()将保存当前位置 接下来的一切移动，旋转，放大，缩小都相对于当地坐标系直到ofPopMatrix() 才退出现场，说不太清楚，必须自己试试，所有的手臂部位都在一对ofPushMatrix()/ofPopMatrix() 里面,这样移动整个手臂比较方便
	ofPushMatrix();
	
	// Translate over to the shoulder location; draw it
    // 转化到肩部位置;
	
    ofTranslate(ofGetWidth()/2, 540, 0);
	ofRotate(shoulderNoiseAngleDegrees, 0, 0, 1);
	drawNoisyArmRect(100,24);
	
	// Translate over to the forearm location; draw it
    // 转化到前臂位置；
	ofTranslate(76, 0, 0);
	ofRotate(elbowNoiseAngleDegrees, 0, 0, 1);
	drawNoisyArmRect(90,16);
	
	// Translate over to the hand location; draw it. Note that the color of the 'hand' is controlled by noise.
    // 转化到手部位置，手的颜色由上面的perlin杂决定
	ofTranslate(74, 0, 0);
	ofRotate(wristNoiseAngleDegrees, 0, 0, 1);
    
    // 五角星
	ofSetCircleResolution(5);
	ofFill();
	ofSetColor (ofFloatColor(noisyR, noisyG, noisyB, 0.75));
    
    // 画三个椭圆代表螺母
	ofEllipse(-10,0, 60,60);
	ofNoFill();
	ofSetColor(0);
	ofEllipse(-10,0, 60,60);
	ofSetCircleResolution(12);
	ofSetColor(0);
	ofFill();
	//ofEllipse(0,0, 7,7);
	
	ofPopMatrix();
}


//--------------------------------------------------------------
// 画机械手的三个部分
void ofApp::drawNoisyArmRect (float w, float h){
	// A little helper function to simplify the code above.
	
    // 画三个长方形, 填充颜色
	ofFill();
	ofSetColor(255,255,255, 128);
	ofRect(-h/2,-h/2, w,h);
	
	ofNoFill();
	ofSetColor(0);
	ofRect(-h/2,-h/2, w,h);
	
	ofSetColor(0);
	ofFill();
	ofEllipse(0,0, 7,7);
}



//--------------------------------------------------------------
// 画噪音
void ofApp::renderSignedNoiseDemo(){
	
	// Draw the explanatory text.
    // 一些简单的解释
	string signedNoiseText = "ofSignedNoise() generates values between -1 and 1.\n";
	signedNoiseText       += "It can be used to generate a terrain - whether as\n";
	signedNoiseText       += "displacements to a line, or to some other shape.\n\n";
	signedNoiseText       += "1D Noise can also be used to control other visual\n";
	signedNoiseText       += "properties, such as rotation angles or color values.\n";
	signedNoiseText       += "Noise is mapped to rotation -- there's no physics here!\n";
	
	ofSetColor(0,0,0);
    
    // 显示perlin杂的有关数据
	float signedNoiseTextX = radialNoiseDemoX - radialNoiseDemoR;
	float signedNoiseTextY = radialNoiseDemoY + radialNoiseDemoR * 2.0 + 16;
	ofDrawBitmapString(signedNoiseText, signedNoiseTextX, signedNoiseTextY);
	ofDrawBitmapString("ofSignedNoise()", signedNoiseTextX+1, signedNoiseTextY); // 'bold' it
	
	// Now draw the linear and circle-wrapped waveforms.
    // 画直行和和沿着旋转圆圈的波纹
	renderRadialSignedNoiseDemo();
	renderLinearSignedNoiseDemo();
}



//--------------------------------------------------------------
void ofApp::renderRadialSignedNoiseDemo (){
	
	float centerX = radialNoiseDemoX;
	float centerY = radialNoiseDemoY;
	
	// Render the Signed Noise demo, using
	// the noise as radial displacements to a circle.
    // 移到中心加半径
	ofPushMatrix();
	ofTranslate(centerX + radialNoiseDemoR,centerY,0);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofNoFill();
	
	// Draw a faint plain circle, so that we can better understand
	// the radial displacements caused by the signed noise later on.
    // 画出一个淡色的圆形，这样我们可以更好的理解径向位移是如果被噪点影响的
	ofSetColor(0,0,0, 64);
	ofSetCircleResolution(256);
	ofEllipse(0,0, radialNoiseDemoR*2,radialNoiseDemoR*2);
	
	// Let's use the signed noise as a radial displacement to a circle. We render out the points stored in the X and Y arrays.
    // 用噪点作为一个圆形的径向位移，把渲染好的点存储在X和Y的阵列中，ofMesh是一组在三维空间中的顶点和他们的法向量，颜色，质地，等等，和openGL格式差不多
	ofMesh wigglyMeshLine; // yes, technically, it's a "mesh"
	wigglyMeshLine.setMode(OF_PRIMITIVE_LINE_STRIP);
	float px = 0, py = 0;
	for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // 角度和色度用ofMap() float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax)
        // 计算inputMax 和 inputMin 之间的直线距离，并重新映射到 outputMax 和 outputMin的百分比例
		float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,-TWO_PI) - HALF_PI;
		float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0     );
		wigglyMeshLine.addColor(ofFloatColor(0,0,255, alph));
		
		// Cpmpute the displaced radius
        // 计算被移动后的半径
		float wigglyRadius = radialNoiseDemoR;
		wigglyRadius +=  radialNoiseDemoR * signedNoiseData[i];
		
		// Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        // 计算新的交点，然后加入 wigglyMeshLine
		px = wigglyRadius * cos( angle );
		py = wigglyRadius * sin( angle );
		wigglyMeshLine.addVertex(ofVec2f(px,py));
	}
	
	// draw the "mesh" (line)
    // 画”网格“(线)
	ofEnableSmoothing();
	wigglyMeshLine.draw();
	
	// draw a little ball at the end
    // 画线尾巴的灰色球
	ofFill();
	ofSetColor(0,0,0, 160);
	ofEllipse(px,py, 7,7);
	
	ofPopMatrix();
}

//--------------------------------------------------------------
// 画直行的噪音（红色的线）
void ofApp::renderLinearSignedNoiseDemo(){
    
	ofPushMatrix();
	
	float drawWiggleWidth = radialNoiseDemoR*TWO_PI;
	ofTranslate (radialNoiseDemoX + radialNoiseDemoR - drawWiggleWidth, radialNoiseDemoY-radialNoiseDemoR,0);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofNoFill();
	
	// draw a "baseline"
    // 灰色的“基线”
    
	ofSetColor(0,0,0, 64);
	ofLine(0,0, drawWiggleWidth,0);
	
	// draw a wiggly line
    // 红色蠕动的线代表燥音
    
	ofSetColor(255,0,0, 192);
	ofPolyline wigglyPolyLine;
	for (int i=0; i<nSignedNoiseData; i++){
		
		// From the 'i' iterator, use ofMap to compute both an angle (around a circle) and an alpha value.
        // 计算角度和色度
		float px = ofMap(i, 0,nSignedNoiseData-1, drawWiggleWidth,0);
		float py = 0 - radialNoiseDemoR * signedNoiseData[i];
		wigglyPolyLine.addVertex(ofVec2f(px,py));
	}
	
	// draw the line
    // 最后，画线
    
	wigglyPolyLine.draw();
	ofPopMatrix();
}

// In case you're wondering, the simpleSliders get their mouse info through event handlers.
// simpleSliders 直接通过鼠标事件处理程序来获取鼠标信息。
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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

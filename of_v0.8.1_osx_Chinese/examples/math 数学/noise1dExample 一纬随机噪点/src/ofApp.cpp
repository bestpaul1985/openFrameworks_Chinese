#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetWindowTitle("Noise 1D Example");
	ofBackground(215,215,215);
	ofSetVerticalSync(true);
	ofSetCircleResolution(256);
	
	setupSignedNoiseDemo();
}

//--------------------------------------------------------------
void ofApp::setupSignedNoiseDemo(){
	// Setup and allocate resources used in the signed noise demo.
    // 设置并分配在随机噪点例子中需要的资源
	nSignedNoiseData = 400; // we'll store a history of 400 numbers
                            // 让我们生产能够存储400个数字的历史记录
	signedNoiseData = new float[nSignedNoiseData];
	for (int i=0; i<nSignedNoiseData; i++){
		signedNoiseData[i] = 0; 
	}
	
	// Some coordinates...
    // 一些坐标
	radialNoiseDemoY = 200;
	radialNoiseDemoR = 100;
	radialNoiseDemoX = ofGetWidth()/2 - radialNoiseDemoR; 
	
	// These 2 sliders control the noise waveform at the top.
    //这两个滑块控制顶部的噪点波纹
	radialNoiseStepSlider.setup(radialNoiseDemoX,   radialNoiseDemoY+150, 200,16, 0.010, 0.150, 0.05, false,true);
	radialNoiseAmountSlider.setup(radialNoiseDemoX, radialNoiseDemoY+170, 200,16, 0.000, 1.000, 0.40, false,true);
	
	radialNoiseStepSlider.setLabelString(  "Noise Step"); 
	radialNoiseAmountSlider.setLabelString("Noise Amount"); 
	radialNoiseStepSlider.setNumberDisplayPrecision(3); 
	radialNoiseCursor = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
	updateSignedNoiseDemo();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient( ofColor(255), ofColor(180), OF_GRADIENT_CIRCULAR);
	renderSignedNoiseDemo();
	renderNoisyRobotArmDemo();
}



//--------------------------------------------------------------
void ofApp::updateSignedNoiseDemo (){
	
	// Shift all of the old data forward through the array
    // 用一个矩阵（array）转移旧的数据
	for (int i=(nSignedNoiseData-1); i>0; i--){
		signedNoiseData[i] = signedNoiseData[i-1];
	}
	
	// Compute the latest data, and insert it at the head of the array.
	// Here is where ofSignedNoise is requested.
    // 计算最后的数据，并且插入到矩阵（array）的头部

	float noiseStep    = radialNoiseStepSlider.getValue();
	float noiseAmount  = radialNoiseAmountSlider.getValue();
	
	signedNoiseData[0] = noiseAmount * ofSignedNoise( radialNoiseCursor ); 
	radialNoiseCursor += noiseStep;
}


//--------------------------------------------------------------
void ofApp::renderNoisyRobotArmDemo(){
	
	float t = ofGetElapsedTimef(); 
	float shoulderNoiseAngleDegrees = 90 + 70.0 * ofSignedNoise(t * 1.00); 
	float elbowNoiseAngleDegrees    = 60 + 80.0 * ofSignedNoise(t * 0.87); 
	float wristNoiseAngleDegrees	= (2.5 * 72) + 45.0 * ofSignedNoise(t * 1.13); 
	
	float noisyR = ofNoise(t * 0.66); // different multiplicative step-factors
                                      // 不同的乘法系数
	float noisyG = ofNoise(t * 0.73); // guarantee that our color channels are
                                      // 保证我们的颜色通道
	float noisyB = ofNoise(t * 0.81); // not all (apparently) synchronized.
                                      //  明显的不同步
	
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetCircleResolution(12);
	ofSetLineWidth(1.0);
	
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
	
	// Translate over to the hand location; draw it. 
	// Note that the color of the 'hand' is controlled by noise.
    // 转化到手部位置
    // 需要注意,手部的颜色是由噪点决定的
	ofTranslate(74, 0, 0);
	ofRotate(wristNoiseAngleDegrees, 0, 0, 1);
	ofSetCircleResolution(5); // a kludgy "pentagon" 一个五角形
	ofFill();
	ofSetColor (ofFloatColor(noisyR, noisyG, noisyB, 0.75)); 
	ofEllipse(-10,0, 60,60); 
	ofNoFill();
	ofSetColor(0);
	ofEllipse(-10,0, 60,60); 
	ofSetCircleResolution(12);
	ofSetColor(0); 
	ofFill();
	ofEllipse(0,0, 7,7);
	
	ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::drawNoisyArmRect (float w, float h){
	// A little helper function to simplify the code above. 
    // 简单的辅助功能用来简化上面的代码
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
void ofApp::renderSignedNoiseDemo(){
	
	// Draw the explanatory text.
    // 画出说明文字
	string signedNoiseText = "ofSignedNoise() generates values between -1 and 1.\n";
	signedNoiseText       += "It can be used to generate a terrain - whether as\n";
	signedNoiseText       += "displacements to a line, or to some other shape.\n\n";
	signedNoiseText       += "1D Noise can also be used to control other visual\n";
	signedNoiseText       += "properties, such as rotation angles or color values.\n";
	signedNoiseText       += "Noise is mapped to rotation -- there's no physics here!\n";
	
	ofSetColor(0,0,0); 
	float signedNoiseTextX = radialNoiseDemoX - radialNoiseDemoR;
	float signedNoiseTextY = radialNoiseDemoY + radialNoiseDemoR * 2.0 + 16;
	ofDrawBitmapString(signedNoiseText, signedNoiseTextX, signedNoiseTextY);
	ofDrawBitmapString("ofSignedNoise()", signedNoiseTextX+1, signedNoiseTextY); // 'bold' it
                                                                                 // 用粗体字
	
	// Now draw the linear and circle-wrapped waveforms.
    // 现在，我们画出线性和圆形的波纹
	renderRadialSignedNoiseDemo();
	renderLinearSignedNoiseDemo();
}



//--------------------------------------------------------------
void ofApp::renderRadialSignedNoiseDemo (){
	
	float centerX = radialNoiseDemoX; 
	float centerY = radialNoiseDemoY; 
	
	// Render the Signed Noise demo, using 
	// the noise as radial displacements to a circle.
    // 对一个圆形使用径向位移，来渲染一个噪点实例

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
	
	// Let's use the signed noise as a radial displacement to a circle. 
	// We render out the points stored in the X and Y arrays.
    //让我们使用噪点作为一个圆形的径向位移
    //我们把渲染好的点存储在X和Y的阵列中
	ofMesh wigglyMeshLine; // yes, technically, it's a "mesh"
                           // 技术成面来说这就是个网格
	wigglyMeshLine.setMode(OF_PRIMITIVE_LINE_STRIP);
	float px = 0, py = 0;
	for (int i=(nSignedNoiseData-1); i>=0; i--){
		
		// From the 'i' iterator, use ofMap to compute both 
		// an angle (around a circle) and an alpha value. 
		float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,-TWO_PI) - HALF_PI;
		float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0     );
		wigglyMeshLine.addColor(ofFloatColor(0,0,255, alph)); 
		
		// Cpmpute the displaced radius
		float wigglyRadius = radialNoiseDemoR;
		wigglyRadius +=  radialNoiseDemoR * signedNoiseData[i];
		
		// Good old-fashioned trigonometry: y = cos(t), x = sin(t)
		px = wigglyRadius * cos( angle );
		py = wigglyRadius * sin( angle );
		wigglyMeshLine.addVertex(ofVec2f(px,py));
	}
	
	// draw the "mesh" (line)
    // 画出”网格“(线)

	ofEnableSmoothing();
	wigglyMeshLine.draw();
	
	// draw a little ball at the end
    // 在最后，我们再画一个小球

	ofFill();
	ofSetColor(0,0,0, 160);
	ofEllipse(px,py, 7,7); 
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::renderLinearSignedNoiseDemo(){
	
	// Draw the stored noise history as a straightforward timeline.
    // 画一个存储了噪点历史数据的直线

	ofPushMatrix();
	
	float drawWiggleWidth = radialNoiseDemoR*TWO_PI;
	ofTranslate (radialNoiseDemoX + radialNoiseDemoR - drawWiggleWidth, radialNoiseDemoY-radialNoiseDemoR,0);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofNoFill();
	
	// draw a "baseline"
    // 画一条“基线”

	ofSetColor(0,0,0, 64);
	ofLine(0,0, drawWiggleWidth,0); 
	
	// draw a wiggly line
    // 画一条蠕动的线

	ofSetColor(255,0,0, 192);
	ofPolyline wigglyPolyLine; 
	for (int i=0; i<nSignedNoiseData; i++){
		
		// From the 'i' iterator, use ofMap to compute both 
		// an angle (around a circle) and an alpha value.
        // 在“i”迭代中，使用 ofMap 去计算角度（环绕在圆形）和一个透明度值。

		float px = ofMap(i, 0,nSignedNoiseData-1, drawWiggleWidth,0);
		float py = 0 - radialNoiseDemoR * signedNoiseData[i];
		wigglyPolyLine.addVertex(ofVec2f(px,py));
	}
	
	// draw the line
    // 画线

	wigglyPolyLine.draw();
	ofPopMatrix();
}

// In case you're wondering, the simpleSliders get their mouse info through event handlers.
// 如果你想知道的话，simpleSliders这个插件通过直接通过鼠标事件处理程序来获取鼠标信息。

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

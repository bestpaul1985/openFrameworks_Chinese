#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(0,0,0);
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);

    font.loadFont("Courier New Bold.ttf", 9);
    
    // this set of characters comes from processing: 
    //http://processing.org/learning/library/asciivideo.html
    //这组字符来自于processing
    
	// changed order slightly to work better for mapping
    // 我们只要简单的改变下顺序，这些字符就能映射更好
    asciiCharacters =  string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");
	
    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    
    // change background video alpha value based on the mouse position
    // 用鼠标改变背景的透明度
    float videoAlphaValue = ofMap(mouseX, 0,ofGetWidth(),0,255);
    
    // set a white fill color with the alpha generated above
    // 设置一个白色的背景，它的透明度就是上面的参数
    ofSetColor(255,255,255,videoAlphaValue);

    // draw the raw video frame with the alpha value generated above
    // 现在，我们开始创建原始的视屏桢，它的透明度取决于上面的操作
    vidGrabber.draw(0,0);

    ofPixelsRef pixelsRef = vidGrabber.getPixelsRef();
    
    ofSetHexColor(0xffffff);

    for (int i = 0; i < camWidth; i+= 7){
        for (int j = 0; j < camHeight; j+= 9){
            // get the pixel and its lightness (lightness is the average of its RGB values)
            //取得像素和像素的亮度（亮度就是这个像素RGB值的平均数）
            float lightness = pixelsRef.getColor(i,j).getLightness();
            // calculate the index of the character from our asciiCharacters array
            // 通过计算，从字母排列中得到一个相对应的字母
            int character = powf( ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();
            // draw the character at the correct location
            // 把计算出的字母放到正确的位置
            font.drawString(ofToString(asciiCharacters[character]), i, j);
        }
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
    //在全屏模式下，至少在PC上，第一次弹出视频设置的时候，他们会在全屏窗口下面。这时候你需要用alt-tab组合键去切换。
    //这是一个buy,OF小组正在修复它。
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

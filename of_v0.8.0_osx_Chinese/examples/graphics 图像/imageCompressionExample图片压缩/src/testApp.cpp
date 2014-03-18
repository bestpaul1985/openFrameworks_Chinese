#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	quality = OF_IMAGE_QUALITY_WORST;
	maxSize = 2048;
	glitchStart = .6;
	reset();
}

//--------------------------------------------------------------
void testApp::reset() {
	generation = 0;
	img.loadImage("buses.jpg");
	// pick random for bleeding 随机选择出血值
	addX = ofRandom(0, 16);
	addY = ofRandom(0, 16);
	subX = ofRandom(0, addX);
	subY = ofRandom(0, addY);
}

//--------------------------------------------------------------
void testApp::update() {
	string curFilename = "compressed.jpg";

	int size = img.getWidth();

	// keeps the image from getting too big
    //保持图片大小使得图片不会过大
	if(size < maxSize) {
		img.saveImage(curFilename, quality);

		if(ofGetKeyPressed('g')) {
			// this portion glitches the jpeg file
			// first loading the file (as binary)
            // 这个部分我们会转化jpeg文件，让它开个小差
            // 首先我们会载入整个图片文件（转为二进制）
			ofBuffer file = ofBufferFromFile(curFilename, true);
			int fileSize = file.size();
			char * buffer = file.getBinaryBuffer();

			// pick a byte offset that is somewhere near the end of the file
            // 选择一个靠近文件结尾处的字节
			int whichByte = (int) ofRandom(fileSize * glitchStart, fileSize);
			// and pick a bit in that byte to turn on
            // 然后选择一个比特在那个字节里面
			int whichBit = ofRandom(8);
			char bitMask = 1 << whichBit;
			// using the OR operator |, if the bit isn't already on this will turn it on
            //使用|（选择运算符），下面的代码很有意思，它的意思就是说，如果whichByte和bitMask不同，就把buffer中的whichByte改写成bitMask
			buffer[whichByte] |= bitMask;

			// write the file out like nothing happened
            // 导出文件，就像什么都没发生过一样
			ofBufferToFile(curFilename, file, true);
			img.loadImage(curFilename);
		} else {
			img.loadImage(curFilename);

			// this if switches every other frame
            // 这个if语句会打开或关闭其它帧
			// resizing up and down breaks the 8x8 JPEG blocks
			if(ofGetFrameNum() % 2 == 0) {
				// resize a little bigger
                //改变一点大小，让它大一点
				img.resize(size + addX, size + addY);
			} else {
				// then resize a little smaller
                //然后再把大小变小一点
				img.resize(size - subX, size - subY);
			}
		}
		generation++;
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	ofSetColor(255);
	img.draw(0, 0, ofGetWidth(), ofGetHeight());

	ofSetColor(0);
	ofRect(5, 5, 290, 45);
	ofSetColor(255);
	ofDrawBitmapString("Currently on generation " + ofToString(generation), 10, 20);
	ofDrawBitmapString("Click to reset, hold 'g' to glitch.", 10, 40);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	reset();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

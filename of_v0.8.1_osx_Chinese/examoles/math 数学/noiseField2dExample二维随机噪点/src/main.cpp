#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(512,512, OF_WINDOW);			// <-------- setup the GL context 设置GL

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    // 上面的代码控制应用的大小和运行模式
    // 你可以输入 OF_WINDOW（窗口模式）或者 OF_FULLSCREEN（全屏模式）调节显示模式
    // 也可以输入长度和宽度来改变窗口大小：
	ofRunApp( new ofApp());
    
}

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1024,60*10, OF_WINDOW);			// <-------- setup the GL context设置GL

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    // 上面的代码控制整个程序的窗口尺寸和显示模式
    // 你可以输入 OF_WINDOW（窗口模式）或者 OF_FULLSCREEN（全屏模式）调节显示模式
    // 也可以输入长度和宽度来改变窗口大小：
	ofRunApp( new ofApp());
    
}

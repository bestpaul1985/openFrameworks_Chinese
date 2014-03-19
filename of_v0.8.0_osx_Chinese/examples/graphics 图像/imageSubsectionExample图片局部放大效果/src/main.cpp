#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(527,640, OF_WINDOW);			// <-------- setup the GL context 设置GL背景

    // this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    // 这行代码揭开了整个程序的运行
    // 可以输入 OF_WINDOW（窗口模式）或者 OF_FULLSCREEN（全屏模式）调节显示模式
    // 也可以输入长度和宽度：
	ofRunApp( new testApp());
    
}

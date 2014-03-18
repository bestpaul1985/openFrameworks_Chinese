#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

        // member variables to store the current mouse X and Y position 
        // as a percentage of the width/height of the screen
    
        //建立一组变量用于存储鼠标坐标X和Y相对于窗口长和宽的百分比
    
        float mouseXPercent, mouseYPercent;
};
	

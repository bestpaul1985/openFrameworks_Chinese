#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
  
    ofScaleMode scaleMode;
    
    ofAspectRatioMode aspectRatioMode;
    
    ofAlignHorz target_hAlign;
    ofAlignVert target_vAlign;
    
    ofAlignHorz subject_hAlign;
    ofAlignVert subject_vAlign;

    ofRectangle targetRect;
    ofRectangle subjectRect;
    ofRectangle workingSubjectRect;
    
    ofColor targetColor;
    ofColor subjectColor;

    bool bUseImage;
    
    bool isRectScaling;
    bool isScaling;
    bool isAligning;
    
    ofImage img;
    
    /////////////////////////
    // Helper functions below
    // 下面的是辅助功能

    // generate a random subject rect
    // 生成一个随机的’主体‘四边形

    void makeNewSubject();

    // generate a random target rect
    // 生成一个随机的’目标‘四边形

    void makeNewTarget();
    
    // draw a rectangle with alignment marks, etc
    // 画一个有对齐标记的四边形，等。。
    void drawAlignRect(const ofRectangle& rect,
                       const ofColor& color,
                       ofAlignHorz hAlign,
                       ofAlignVert vAlign,
                       bool useImage);
    
    // draw visual horizontal anchor marks
    // 画水平方向上的锚点
    void drawHorzAlignMark(const ofRectangle& rect, const ofColor& color, ofAlignHorz hAlign);
    void drawVertAlignMark(const ofRectangle& rect, const ofColor& color, ofAlignVert vAlign);
    
    
    // helper functions for text output
    // 文字输出辅助功能
    ofScaleMode getNextScaleMode(ofScaleMode mode);
    ofAspectRatioMode getNextAspectRatioMode(ofAspectRatioMode mode);
    ofAlignHorz getNextHorzAlign(ofAlignHorz hAlign);
    ofAlignVert getNextVertAlign(ofAlignVert vAlign);
    
    string getHorzAlignString(ofAlignHorz hAlign);
    string getVertAlignString(ofAlignVert vAlign);
    
    string getAspectRatioModeString(ofAspectRatioMode mode);
    string getScaleModeString(ofScaleMode mode);
    
};

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // This example is designed to show all of the different aligning
    // and scaling functions available in ofRectangle.
    //
    // Please run the example and use the keyboard to see the visual
    // results of each of the alignment and scaling operations.
    //
    // The basic premise is to define a subject and target rectangle.
    // The "subject" (on the left) rectangle will be aligned-to
    // and scaled-to the "target" (on the right) rectangle based
    // on the user's input.
    //
    // The resulting rectangle (workingSubjectRect in this case),
    // displayed in the center, is the result of the operations.
    //
    // An image is used to further emphasize the effect of various
    // aspect-ratio preservation modes.
    
    //这个例子是用于展示所有针对ofRectangle的对齐和缩放功能
    //请运行这个例子并使用键盘去探索各种对齐和缩放的效果
    //基本前提是先界定”主体“和”目标“的形状。
    //基于用户的选择， ”主体“（左边的那个）四边形会对齐于或者缩放到”目标“
    //显示对齐或者缩放结果的方形（在这个例子里叫：workingSubjectRect）会展现在中间
    //为了更好的显示对齐时四边形的旋转方向，我们用了一张图片去强调这个效果。
    
    
    
    ofSetFrameRate(30);
    ofEnableAlphaBlending();

    isScaling = false;
    isAligning = true;
    isRectScaling = false;
    
    scaleMode       = OF_SCALEMODE_FIT;
    aspectRatioMode = OF_ASPECT_RATIO_KEEP;
    
    target_hAlign   = OF_ALIGN_HORZ_CENTER;
    target_vAlign   = OF_ALIGN_VERT_CENTER;
    
    subject_hAlign  = OF_ALIGN_HORZ_CENTER;
    subject_vAlign  = OF_ALIGN_VERT_CENTER;
    
    bUseImage = true;
    
    img.loadImage("resolution_test_1080_mini.png");

    targetColor  = ofColor(255,0,0);
    subjectColor = ofColor(255,255,0);

    makeNewTarget();
    makeNewSubject();

}

//--------------------------------------------------------------
void testApp::update(){
    
    workingSubjectRect = subjectRect;

    // read the results of our keyboard input to determine
    // the correct scaling and / or alignment operation.
    
    //读取键盘输入的信息
    //通过信息判断正确的缩放/对齐方式
    
    if(!isRectScaling) {
        if(isScaling) {
            if(isAligning) {
                workingSubjectRect.scaleTo(targetRect,
                                           aspectRatioMode,
                                           target_hAlign,
                                           target_vAlign,
                                           subject_hAlign,
                                           subject_vAlign);
            } else {
                workingSubjectRect.scaleTo(targetRect,
                                           aspectRatioMode);
            }
        } else {
            if(isAligning) {
                workingSubjectRect.alignTo(targetRect,
                                           target_hAlign,
                                           target_vAlign,
                                           subject_hAlign,
                                           subject_vAlign);
            } else {
                workingSubjectRect.alignTo(targetRect);
            }
        }
    } else {
        workingSubjectRect.scaleTo(targetRect,
                                   scaleMode);
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);

    // draw original subject in lower left-hand corner
    // 在左下角画出”主体“四边形
    if(!bUseImage) {
        ofFill(); ofSetColor(subjectColor, 80);
        ofRect(10, ofGetHeight() - subjectRect.height - 10, subjectRect.width, subjectRect.height);
    } else {
        ofFill(); ofSetColor(255);
        img.draw(10, ofGetHeight() - subjectRect.height - 10, subjectRect.width, subjectRect.height);
    }
    // draw original subject frame in lower left-hand corner
    // 在左下角画出”主体“的外框
    ofNoFill(); ofSetColor(subjectColor, 120);
    ofRect(10, ofGetHeight() - subjectRect.height - 10, subjectRect.width, subjectRect.height);
    // draw original subject label
    ofSetColor(255);
    ofDrawBitmapStringHighlight("SUBJECT", 16, ofGetHeight() - 20);
    
    // draw original target in lower right-hand corner
    // 在右下角画出”目标“四边形
    ofFill(); ofSetColor(targetColor, 80);
    ofRect(ofGetWidth() - targetRect.width - 10, ofGetHeight() - targetRect.height - 10, targetRect.width, targetRect.height);
    // draw original target frame in lower right-hand corner
    // 在右下角画出”目标“的外框
    ofNoFill(); ofSetColor(targetColor, 120);
    ofRect(ofGetWidth() - targetRect.width - 10, ofGetHeight() - targetRect.height - 10, targetRect.width, targetRect.height);
    ofSetColor(255);
    ofDrawBitmapStringHighlight("TARGET", ofGetWidth() - 65, ofGetHeight() - 20);    
    
    // draw target rectangle in center
    //在中间画出”目标“四边形
    drawAlignRect(targetRect,  targetColor,  target_hAlign,  target_vAlign, false);
    
    // draw aligned / scaled subject with respect to the target
    // 画出与“目标”对齐后/缩放后的”主体“
    drawAlignRect(workingSubjectRect, subjectColor, subject_hAlign, subject_vAlign, bUseImage);

    // make the menu
    // 下面我们开始做一个菜单
    stringstream ss;
    
    ss << "Keys:" << endl;
    ss << "----------------------------------------------------------" << endl;
    ss << " New Subject / Target (space) " << endl;
    ss << " Use An Image Subject (i) = " << (bUseImage ? "YES" : "NO") << endl;
    ss << "----------------------------------------------------------" << endl;
    ss << "  Enable Custom Align (A) = " << (isAligning && !isRectScaling ? "YES" : "NO") << endl;
    ss << "  Subject ofAlignHorz (h) = " << (isAligning && !isRectScaling ? getHorzAlignString(subject_hAlign) : "-") << endl;
    ss << "    Model ofAlignHorz (H) = " << (isAligning && !isRectScaling ? getHorzAlignString(target_hAlign)  : "-") << endl;
    ss << "  Subject ofAlignVert (v) = " << (isAligning && !isRectScaling ? getVertAlignString(subject_vAlign) : "-") << endl;
    ss << "    Model ofAlignVert (V) = " << (isAligning && !isRectScaling ? getVertAlignString(target_vAlign)  : "-") << endl;
    ss << "----------------------------------------------------------" << endl;
    ss << "Enable Custom Scaling (S) = " << (isScaling && !isRectScaling ? "YES" : "NO") << endl;
    ss << "    ofAspectRatioMode (a) = " << (isScaling && !isRectScaling ? getAspectRatioModeString(aspectRatioMode) : "-") << endl;
    ss << "----------------------------------------------------------" << endl;
    ss << " Override Scale/Align (r) = " << (isRectScaling ? "YES" : "NO") << endl;
    ss << "          ofScaleMode (s) = " << (isRectScaling ? getScaleModeString(scaleMode) : "-") << endl;

    // draw the menu
    //画出这个菜单
    ofSetColor(255);
    ofDrawBitmapString(ss.str(), 10, 14);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    // define keyboard interactions
    // 定义键盘信息
    if(key == ' ') {
        makeNewTarget();
        makeNewSubject();
    } else if(key == 'h' && !isRectScaling && isAligning) {
        subject_hAlign = getNextHorzAlign(subject_hAlign);
    } else if(key == 'H' && !isRectScaling && isAligning) {
        target_hAlign = getNextHorzAlign(target_hAlign);
    } else if(key == 'v' && !isRectScaling && isAligning) {
        subject_vAlign = getNextVertAlign(subject_vAlign);
    } else if(key == 'V' && !isRectScaling && isAligning) {
        target_vAlign = getNextVertAlign(target_vAlign);
    } else if(key == 'a' && !isRectScaling && isScaling) {
        aspectRatioMode = getNextAspectRatioMode(aspectRatioMode);
    } else if(key == 's' && isRectScaling) {
        scaleMode = getNextScaleMode(scaleMode);
    } else if(key == 'S') {
        if(isRectScaling) {
            isScaling = true;
            isRectScaling = false;
        } else {
            isScaling = !isScaling;
        }
    } else if(key == 'r') {
        isRectScaling = !isRectScaling;
        if(isRectScaling) {
            isScaling = false;
            isAligning = false;
        }
    } else if(key == 'A') {
        if(isRectScaling) {
            isRectScaling = false;
            isAligning = true;
        } else {
            isAligning = !isAligning;
        }
    } else if(key == 'i') {
        bUseImage = !bUseImage;
        if(bUseImage) {
            makeNewSubject();
        }
    }
}

//--------------------------------------------------------------
void testApp::makeNewSubject() {
    // if we are not using an image, make a random subject rectangle
    //如果我们不使用图片，我们会制作一个随机的四边形
    if(!bUseImage) {
        subjectRect.setFromCenter(ofGetWidth()  / 2.0f,
                                  ofGetHeight() / 2.0f,
                                  ofRandom(30.0f,300.0f),
                                  ofRandom(30.0f,300.0f));
    } else {
        // if we are using the image, then match the image size
        // 如果我们使用图片，我们会用图片大小
        subjectRect.setFromCenter(ofGetWidth()  / 2.0f,
                                  ofGetHeight() / 2.0f,
                                  img.getWidth(),
                                  img.getHeight());
    }
    
    // copy the subject to the working subject so it can be modified.
    //复制“主体”的信息到“working subject”，也就是说我们可以调整working subject
    workingSubjectRect = subjectRect;
    
}

//--------------------------------------------------------------
void testApp::makeNewTarget() {
    
    // create a random target rectangle aligned to the center of the screen
    // 创建一个随机的“目标”四边形对齐到屏幕中间
    targetRect.setFromCenter(ofGetWidth()  / 2.0f,
                             ofGetHeight() / 2.0f,
                             ofRandom(30.0f,300.0f),
                             ofRandom(30.0f,300.0f));
}

//--------------------------------------------------------------
void testApp::drawAlignRect(const ofRectangle& rect,
                            const ofColor& color,
                            ofAlignHorz hAlign,
                            ofAlignVert vAlign,
                            bool drawImage) {
    
    // draw the rect -- draw the image if using an image
    //画一个四边形--如果需要图片，我们就用图片
    ofFill();
    if(drawImage) {
        ofSetColor(255,127);
        img.draw(rect);
    } else {
        ofSetColor(color, 80);
        ofRect(rect);
    }
    
    ofNoFill();
    ofSetColor(color, 120);
    ofRect(rect);
    
    // draw the alignment marks if applicable
    //画出对齐标记，如果这个选项可以被执行的话
    if(isAligning && !isRectScaling) {
        drawHorzAlignMark(rect, color, hAlign);
        drawVertAlignMark(rect, color, vAlign);
    }
}

//--------------------------------------------------------------
void testApp::drawHorzAlignMark(const ofRectangle& rect, const ofColor& color, ofAlignHorz hAlign) {
    if(hAlign != OF_ALIGN_HORZ_IGNORE) {
        float hAnchor = rect.getHorzAnchor(hAlign);
        ofSetColor(color,120);
        ofLine(hAnchor, rect.getTop()    - 13, hAnchor, rect.getTop()    - 3);
        ofLine(hAnchor, rect.getBottom() + 13, hAnchor, rect.getBottom() + 3);
    }
}

//--------------------------------------------------------------
void testApp::drawVertAlignMark(const ofRectangle& rect, const ofColor& color, ofAlignVert vAlign) {
    if(vAlign != OF_ALIGN_VERT_IGNORE) {
        float vAnchor = rect.getVertAnchor(vAlign);
        ofSetColor(color,120);
        ofLine(rect.getLeft()  - 13, vAnchor, rect.getLeft()  - 3, vAnchor);
        ofLine(rect.getRight() + 13, vAnchor, rect.getRight() + 3, vAnchor);
    }
}

//--------------------------------------------------------------
ofScaleMode testApp::getNextScaleMode(ofScaleMode mode) {
    if(mode == OF_SCALEMODE_FIT) {
        mode = OF_SCALEMODE_FILL;
    } else if(mode == OF_SCALEMODE_FILL) {
        mode = OF_SCALEMODE_CENTER;
    } else if(mode == OF_SCALEMODE_CENTER) {
        mode = OF_SCALEMODE_STRETCH_TO_FILL;
    } else if(mode == OF_SCALEMODE_STRETCH_TO_FILL) {
        mode = OF_SCALEMODE_FIT;
    }
    return mode;
}

//--------------------------------------------------------------
ofAspectRatioMode testApp::getNextAspectRatioMode(ofAspectRatioMode mode) {
    if(mode == OF_ASPECT_RATIO_IGNORE) {
        mode = OF_ASPECT_RATIO_KEEP;
    } else if(mode == OF_ASPECT_RATIO_KEEP) {
        mode = OF_ASPECT_RATIO_KEEP_BY_EXPANDING;
    } else if(mode == OF_ASPECT_RATIO_KEEP_BY_EXPANDING) {
        mode = OF_ASPECT_RATIO_IGNORE;
    }
    return mode;
}


//--------------------------------------------------------------
ofAlignHorz testApp::getNextHorzAlign(ofAlignHorz hAlign) {
    if(hAlign == OF_ALIGN_HORZ_LEFT) {
        hAlign = OF_ALIGN_HORZ_CENTER;
    } else if(hAlign == OF_ALIGN_HORZ_CENTER) {
        hAlign = OF_ALIGN_HORZ_RIGHT;
    } else if(hAlign == OF_ALIGN_HORZ_RIGHT) {
        hAlign = OF_ALIGN_HORZ_LEFT;
    }
    return hAlign;
}

//--------------------------------------------------------------
ofAlignVert testApp::getNextVertAlign(ofAlignVert vAlign) {
    if(vAlign == OF_ALIGN_VERT_TOP) {
        vAlign = OF_ALIGN_VERT_CENTER;
    } else if(vAlign == OF_ALIGN_VERT_CENTER) {
        vAlign = OF_ALIGN_VERT_BOTTOM;
    } else if(vAlign == OF_ALIGN_VERT_BOTTOM) {
        vAlign = OF_ALIGN_VERT_TOP;
    }
    return vAlign;
}

//--------------------------------------------------------------
string testApp::getHorzAlignString(ofAlignHorz hAlign) {
    switch (hAlign) {
        case OF_ALIGN_HORZ_LEFT:
            return "OF_ALIGN_HORZ_LEFT";
        case OF_ALIGN_HORZ_CENTER:
            return "OF_ALIGN_HORZ_CENTER";
        case OF_ALIGN_HORZ_RIGHT:
            return "OF_ALIGN_HORZ_RIGHT";
        case OF_ALIGN_HORZ_IGNORE:
            return "OF_ALIGN_HORZ_IGNORE";
        default:
        	ofLogError() << "Unknown ofAlignHorz: " << hAlign;
        	return "";
    }
}

//--------------------------------------------------------------
string testApp::getVertAlignString(ofAlignVert vAlign) {
    switch (vAlign) {
        case OF_ALIGN_VERT_TOP:
            return "OF_ALIGN_VERT_TOP";
        case OF_ALIGN_VERT_CENTER:
            return "OF_ALIGN_VERT_CENTER";
        case OF_ALIGN_VERT_BOTTOM:
            return "OF_ALIGN_VERT_BOTTOM";
        case OF_ALIGN_VERT_IGNORE:
            return "OF_ALIGN_VERT_IGNORE";
        default:
        	ofLogError() << "Unknown ofAlignVert: " << vAlign;
        	return "";
    }
}

//--------------------------------------------------------------
string testApp::getAspectRatioModeString(ofAspectRatioMode mode) {
    switch (mode) {
        case OF_ASPECT_RATIO_IGNORE:
            return "OF_ASPECT_RATIO_IGNORE";
        case OF_ASPECT_RATIO_KEEP:
            return "OF_ASPECT_RATIO_KEEP";
        case OF_ASPECT_RATIO_KEEP_BY_EXPANDING:
            return "OF_ASPECT_RATIO_KEEP_BY_EXPANDING";
        default:
        	ofLogError() << "Unknown ofAspectRatioMode: " << mode;
        	return "";
    }
}

//--------------------------------------------------------------
string testApp::getScaleModeString(ofScaleMode mode) {
    switch (mode) {
        case OF_SCALEMODE_FIT:
            return "OF_SCALEMODE_FIT";
        case OF_SCALEMODE_FILL:
            return "OF_SCALEMODE_FILL";
        case OF_SCALEMODE_CENTER:
            return "OF_SCALEMODE_CENTER";
        case OF_SCALEMODE_STRETCH_TO_FILL:
            return "OF_SCALEMODE_STRETCH_TO_FILL";
        default:
        	ofLogError() << "Unknown ofScaleMode: " << mode;
        	return "";
    }
}


#include "ofApp.h"


/*
 
 Image Sequence Example:
 In this example we are going to load a sequence of images from a folder.
 We know that the images are in order and the we saved them out at 24fps. 
 the goal is to play them back at 24fps independent of the fps of the app.
 You can toggle the sequence to be independent of the app fps.
 
 说明：
 
 在这个例子中我们将会从一个文件夹中加载一系列的图片。
 些图片都是按照顺序命名的，并且我们知道这些图片组成的动画的帧率是24fps。
 以24fps的帧率播放这些图片取决于这个应用的帧速率。
 我们可以把这个序列在播放单张图片和播放动画之间切换。
 
 Topics:
 - ofDirectory
 - ofImage
 - timing
 
 gif from: http://probertson.livejournal.com/32350.html
 

 
 */


//--------------------------------------------------------------
void ofApp::setup() {
    
    ofBackground(0);
    ofSetWindowTitle("The Moon is made of plops");
                     
    // read the directory for the images
    // we know that they are named in seq
    // 读取路径中的图片
    // 我们知道这些图片都是按照顺序命名的
    ofDirectory dir;
    
    int nFiles = dir.listDir("plops");
    if(nFiles) {
        
        for(int i=0; i<dir.numFiles(); i++) { 
            
            // add the image to the vector
            // 把图片加入向量
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
            
        }
        
    } 
    else printf("Could not find folder\n");
    
    // this toggle will tell the sequence
    // be be indepent of the app fps
    // 这个切换会告诉序列每一桢都单独播放

    bFrameIndependent = true;
    
    // this will set the speed to play 
    // the animation back we set the
    // default to 24fps
    //这里将会设置播放动画的的速度
    //默认值是24fps
    
    sequenceFPS = 24;

    // set the app fps
    //设置应用的fps

    appFPS = 60;
    ofSetFrameRate(appFPS);
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    // we need some images if not return
    // 如果没有加载任何图片，我们会被告知

    if((int)images.size() <= 0) {
        ofSetColor(255);
        ofDrawBitmapString("No Images...", 150, ofGetHeight()/2);
        return;
    }
    
    // this is the total time of the animation based on fps
    // 下面是计算播放动画所需时间的公式

    //float totalTime = images.size() / sequenceFPS;
    
    
    int frameIndex = 0;
    
    if(bFrameIndependent) {
        // calculate the frame index based on the app time
        // and the desired sequence fps. then mod to wrap
        //计算时间和帧速率，得出这一帧需要播放的内容
        frameIndex = (int)(ofGetElapsedTimef() * sequenceFPS) % images.size();
    }
    else {
        // set the frame index based on the app frame
        // count. then mod to wrap.
        //计算应用的总帧数，得出这一帧需要播放的内容
        frameIndex = ofGetFrameNum() % images.size();
    }
    
    // draw the image sequence at the new frame count
    // 画出图片序列
    ofSetColor(255);
    images[frameIndex].draw(256, 36);
    
    
    // draw where we are in the sequence
    // 画出图片序列的缩略图
    float x = 0;
    for(int offset = 0; offset < 5; offset++) {
			int i = (frameIndex + offset) % images.size();
        ofSetColor(255);
        images[i].draw(200+x, ofGetHeight()-40, 40, 40);
        x += 40;
    }
    
    
    // how fast is the app running and some other info
    // 应用的一些信息，如应用的运行速度等
    ofSetColor(50);
    ofRect(0, 0, 200, 200);
    ofSetColor(200);
    string info;
    info += ofToString(frameIndex)+" sequence index\n";
    info += ofToString(appFPS)+"/"+ofToString(ofGetFrameRate(), 0)+" fps\n";
    info += ofToString(sequenceFPS)+" Sequence fps\n\n";
    info += "Keys:\nup & down arrows to\nchange app fps\n\n";
    info += "left & right arrows to\nchange sequence fps";
    info += "\n\n't' to toggle\nframe independent("+ofToString(bFrameIndependent)+")";
    
    ofDrawBitmapString(info, 15, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if(key == OF_KEY_UP)      appFPS ++;
    if(key == OF_KEY_DOWN)    appFPS --;
    if(key == OF_KEY_LEFT)    sequenceFPS --;
    if(key == OF_KEY_RIGHT)   sequenceFPS ++;    
    if(key == 't')            bFrameIndependent = !bFrameIndependent;
    
    // check for less than zero...
    // 检查是否小于0
    sequenceFPS = MAX(sequenceFPS, 1);
    appFPS      = MAX(appFPS, 1);
    
    ofSetFrameRate(appFPS);
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

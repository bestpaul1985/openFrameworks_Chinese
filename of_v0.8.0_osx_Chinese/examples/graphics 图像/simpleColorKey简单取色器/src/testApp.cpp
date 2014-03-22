#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //load the image object
    //载入图片
    original.loadImage("myImage.jpg");
    
    //get the pixels from the image
    //取得图片的各个像素
    ofPixelsRef pixels = original.getPixelsRef();
	
	//let's manipulate the pixels by iterating through them
    //or a rough bluescreen
    //让我们控制这些像素通过逐一通过它们
    //或者就来个蓝屏
    for(int y = 0; y < original.getHeight(); y++){
		for(int x = 0; x < original.getWidth(); x++){
			
			//if the blue is greater than the combination of  red and green together, delete that pixel
            //如果这个蓝色的值比红色和绿色相加还大，那就删除这个像素
			ofColor color = original.getColor(x, y);
			if(color.b > color.g + color.r){
				pixels.setColor(x, y, ofColor::black);
			}
		}
	}

    //after we're done we need to put the pixels into the keyed image
    //完成上面的步骤后，我们把得到的像素放到一张键控图片里
    keyed.setFromPixels(pixels);
}

//--------------------------------------------------------------
void testApp::update(){
    //no need to use this
    //这里什么都不用做
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //draw the image every frame, the changes you made in setup() will be there
    //画出每桢的图片，你在setup()里做的改变都会显示在这里
    original.draw(0,0);
	keyed.draw(original.getWidth(),0);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 's'){
		//we can save out the modified version here
        //我们可以把得到的图片保存起来
		keyed.saveImage("keyed_image.png");
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

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
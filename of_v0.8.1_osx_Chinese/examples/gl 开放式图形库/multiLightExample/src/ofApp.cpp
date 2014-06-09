//看各种灯光的设置 http://www.openframeworks.cc/documentation/gl/ofLight.html
#include "testApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	ofSetVerticalSync(true);    //ofSetVerticalSync()-同步更新屏幕重绘和屏幕的垂直刷新,
	ofSetFrameRate(60);         //设置分辨率
	ofBackground(10, 10, 10);   //设置背景颜色
	ofEnableDepthTest();        //ofEnableDepthTest()-使用openGL的z-buffer功能 - 就是存储每个象素的z-value并且每帧都会清除再更新z坐标
    
    // turn on smooth lighting //
	// 使用平滑 (柔和？）的灯光
    bSmoothLighting     = true;
    ofSetSmoothLighting(true);
    
    // lets make a high-res sphere //
    // default is 20 //
	// 设置圆圈份比率，数字越大越高清
    ofSetSphereResolution(128);
	
    // radius of the sphere //
	// 设置球的半径和中心
	radius		= 180.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
	// 灯光向个方向发光
    // 设置漫反射颜色，颜色从光源反射
    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
    
    // specular color, the highlight/shininess color //
	// specular light 代表光点的材料颜色
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
	pointLight.setPointLight();
    
    
	// diffuse light 代表材料被灯光照亮的颜色
    spotLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));
	spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    
    // turn the light into spotLight, emit a cone of light //
	// 把光变成像聚光灯一样，发射光锥
    spotLight.setSpotlight();
    
    // size of the cone of emitted light, angle between light axis and side of cone //
    // angle range between 0 - 90 in degrees //
	// 这是光锥散发的角度
    spotLight.setSpotlightCutOff( 50 );
    
    // rate of falloff, illumination decreases as the angle from the cone axis increases //
    // range 0 - 128, zero is even illumination, 128 is max falloff //
	// concentration 代表衰减率，光线随着光拽离轴的角度的增加慢慢降落，范围在0-128，零是均匀的照明，128是最大衰减
    spotLight.setSpotConcentration( 45 );
    
	
    // Directional Lights emit light based on their orientation, regardless of their position //
	// 射向光线是根据它的方向，不是根据它的位置
	directionalLight.setDiffuseColor(ofColor(0.f, 0.f, 255.f));
	directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	directionalLight.setDirectional();
    
    // set the direction of the light
    // set it pointing from left to right -> //
	// 设置光线的射向，一般从左到右
	directionalLight.setOrientation( ofVec3f(0, 90, 0) );
    
	
	// 闪亮！
	bShiny = true;
    // shininess is a value between 0 - 128, 128 being the most shiny //
	// 闪亮度范围在0-128，128最亮
	material.setShininess( 120 );
    
    // the light highlight of the material //
    // 看上面的解释
	material.setSpecularColor(ofColor(255, 255, 255, 255));
	
	bPointLight = bSpotLight = bDirLight = true;
    
    // tex coords for 3D objects in OF are from 0 -> 1, not 0 -> image.width
    // so we must disable the arb rectangle call to allow 0 -> 1
	// 三维物体的坐标是从0 - > 1 ，而不是0 - > image.width
    // 所以我们必须禁用套利矩形调用允许0 - > 1
    ofDisableArbTex();
    
    // load an image to use as the texture //
	// 加载图像作为纹理使用
    ofLogoImage.loadImage("of.png");
    bUseTexture = true;
}

//--------------------------------------------------------------
void ofApp::update() {
	// pointlight灯光在空间里不停的旋转，spotlight灯光的位置为鼠标来定
    pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
						   sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
						   -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
	
    spotLight.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );
	spotLight.setPosition( mouseX, mouseY, 200);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // enable lighting //
	// 使能照明
    ofEnableLighting();
    // enable the material, so that it applies to all 3D objects before material.end() call //
	// 又是一个和ofPushMatrix()/ofPopMatrix()格式类似的构造，接下来的性质影响到所有在这对material.begin/material.end里面的
	material.begin();
    // activate the lights //
	// 开灯
	if (bPointLight) pointLight.enable();
	if (bSpotLight) spotLight.enable();
	if (bDirLight) directionalLight.enable();
    
    // grab the texture reference and bind it //
    // this will apply the texture to all drawing (vertex) calls before unbind() //
	// bind()会把这张图片绑在以下的box上面，直到unbind（），又是一个类似于ofPushMatrix()/ofPopMatrix();
    if(bUseTexture) ofLogoImage.getTextureReference().bind();
    
	// 画旋转的球，这里用ofPushMatrix()/ofPopMatrix()是为了让他从她的中心旋转，注意第二步 ofTranslate()
	ofSetColor(255, 255, 255, 255);
    ofPushMatrix();
    ofTranslate(center.x, center.y, center.z-300);
    ofRotate(ofGetElapsedTimef() * .8 * RAD_TO_DEG, 0, 1, 0);
	ofDrawSphere( 0,0,0, radius);
    ofPopMatrix();
	
	// 画旋转的小立方体
	ofPushMatrix();
	ofTranslate(300, 300, cos(ofGetElapsedTimef()*1.4) * 300.f);
	ofRotate(ofGetElapsedTimef()*.6 * RAD_TO_DEG, 1, 0, 0);
	ofRotate(ofGetElapsedTimef()*.8 * RAD_TO_DEG, 0, 1, 0);
	ofDrawBox(0, 0, 0, 60);
	ofPopMatrix();
	
	// 画另外一个大立方体
	ofPushMatrix();
	ofTranslate(center.x, center.y, -900);
	ofRotate(ofGetElapsedTimef() * .2 * RAD_TO_DEG, 0, 1, 0);
	ofDrawBox( 0, 0, 0, 850);
	ofPopMatrix();
    
    if(bUseTexture) ofLogoImage.getTextureReference().unbind();
	
	// 关灯光
	if (!bPointLight) pointLight.disable();
	if (!bSpotLight) spotLight.disable();
	if (!bDirLight) directionalLight.disable();
	
    material.end();
	// turn off lighting //
    ofDisableLighting();
    
	ofSetColor( pointLight.getDiffuseColor() );
	if(bPointLight) pointLight.draw();
    
    ofSetColor(255, 255, 255);
	ofSetColor( spotLight.getDiffuseColor() );
	if(bSpotLight) spotLight.draw();
	
    
	// 显示一些有关数据
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Point Light On (1) : "+ofToString(bPointLight) +"\n"+
					   "Spot Light On (2) : "+ofToString(bSpotLight) +"\n"+
					   "Directional Light On (3) : "+ofToString(bDirLight)+"\n"+
					   "Shiny Objects On (s) : "+ofToString(bShiny)+"\n"+
                       "Spot Light Cutoff (up/down) : "+ofToString(spotLight.getSpotlightCutOff(),0)+"\n"+
                       "Spot Light Concentration (right/left) : " + ofToString(spotLight.getSpotConcentration(),0)+"\n"+
                       "Smooth Lighting enabled (x) : "+ofToString(bSmoothLighting,0)+"\n"+
                       "Textured (t) : "+ofToString(bUseTexture,0),
					   20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	//各种光线的设置，自己试试看
    switch (key) {
		case '1':
			bPointLight = !bPointLight;
			break;
		case '2':
			bSpotLight = !bSpotLight;
			break;
		case '3':
			bDirLight = !bDirLight;
			break;
		case 's':
			bShiny	= !bShiny;
			if (bShiny) material.setShininess( 120 );
			else material.setShininess( 30 );
			break;
        case 'x':
            bSmoothLighting = !bSmoothLighting;
            ofSetSmoothLighting(bSmoothLighting);
            break;
        case 't':
            bUseTexture = !bUseTexture;
            break;
        case OF_KEY_UP:
            // setSpotlightCutOff is clamped between 0 - 90 degrees //
			// setSpotlightCutOff范围在0至90度
            spotLight.setSpotlightCutOff(spotLight.getSpotlightCutOff()+1);
            break;
        case OF_KEY_DOWN:
            spotLight.setSpotlightCutOff(spotLight.getSpotlightCutOff()-1);
            break;
        case OF_KEY_RIGHT:
            // setSpotConcentration is clamped between 0 - 128 //
			// setSpotConcentration范围在0至128
            spotLight.setSpotConcentration(spotLight.getSpotConcentration()+1);
            break;
        case OF_KEY_LEFT:
            spotLight.setSpotConcentration(spotLight.getSpotConcentration()-1);
            break;
		default:
			break;
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
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /*-----------
     这个例子没有代码在draw和update中执行。
     你可以观察这个例子的唯一方式是查看console中的变化，
     理解里面的内容和代码之间的关系。
     -------------------------------------------------------------*/
	color.set("color",ofColor(127),ofColor(0,0),ofColor(255,255));
	color.addListener(this,&ofApp::colorChanged);
    
	color = ofColor(255);
	cout << color.getName() << ": " << color << endl; // color: 255, 255, 255, 255

	// we can access the properties and const methods of objects contained
	// in ofParameters
    // 我们可以访问ofParameters的各个属性和对象的常态方程式（const methods）
	cout << color.getName() << ": r " << (int)color->r << ", g " << (int)color->g << ", b " << (int)color->b << endl;

	cout << "brightness: " << color->getBrightness() << endl; // brightness: 255

	// but that's read only so always we change an object the internal event
	// in the ofParameter is triggered. Trying to do this, will fail to compile:
    //但是他们是只读的，所以，要改变这些属性，我们需要改变它的相应对象，既一个在已经激活了的ofParameter的内部的事件。
    //尝试下面的代码，你会编写失败
    
	//color->set(127);
	//color->a = 127;

	// instead we need to do:
    // 取代上面的错误代码，我们可以用下面的代码：
	color = ofColor(127,127);
	cout << color.getName() << ": " << color << endl; // color: 127, 127, 127, 127
	cout << "brightness: " << color->getBrightness() << endl; // brightness: 127

	// arithmetic operators will work though:
    // 算术操作是可以工作的
	cout << color.getName() << ": " << color << endl; // color: 127, 127, 127, 127
	color*=.5;
	cout << color.getName() << ": " << color << endl; // color: 255, 255, 255, 127




	// ofParameter has shallow copy semantics
    // ofParameter有浅拷贝的语意
	a.set("a",5,0,10);
	ofParameter<int> reference(a);

	cout << reference.getName() << ": " << reference << endl;  // a: 5

	incrementParam(reference);
	cout << reference.getName() << ": " << reference << endl;  // a: 6
	cout << a.getName() << ": " << a << endl;  				   // a: 6


	// to avoid confusion when doing assignments and arithmetic operations
	// the = operator only copies the value
    // 为了避免在执行任何和算术操作时候的混乱，等于号（＝）只复制数值
	b.set("b",0,0,10);
	b = a;
	cout << b.getName() << ": " << b << endl;  // b: 6

	// if you want to make a reference:
    // 如果你需要引用（reference）
	b.makeReferenceTo(a);
	cout << b.getName() << ": " << b << endl;  // a: 6

}

void ofApp::incrementParam(ofParameter<int> p){
	p++;
}

void ofApp::colorChanged(ofColor & color){
	cout << "colorChanged event: " << color << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

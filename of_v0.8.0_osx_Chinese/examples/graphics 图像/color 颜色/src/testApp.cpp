#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	ofSetWindowTitle("color example");
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
                        //如果关闭了垂直同步，我们可以跑的更快点...这行代码把帧数固定在了60帧每秒
    
    // initialise member variables to the centre of the screen
    //初始化屏幕中心点的数字参数
    mouseXPercent = 0.5f;
    mouseYPercent = 0.5f;

}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // here we demonstrate setting colors using HSB (Hue/Saturation/Brightness) rather than the 
    // more well-known RGB (Red/Green/Blue).
    
    // HSB allows colors to be specified in a way that is perhaps more natural to the understanding
    // of color that we have through language, using numerical values to describe 'hue', 
    // 'saturation' and 'brightness'. 
    
    // 'hue' refers to the 'color' in the rainbow sense, moving from red through yellow through
    //   green through blue through purple through red, looping around again.
    // 'saturation' refers to the intensity of the color. high saturation means intense color,
    //   low saturation means washed out or black and white.    
    // 'brightness' refers to how light or dark the color is. high brightness means a bright color,
    //   low brightness is dark. if the brightness is 0 the resulting color will be black, regardless 
    //   of the values for hue or saturation.
        
    // in ofColor all the values are specified as 0..255 .
    
    // for example, to specify an orange color that is strong and bright, you start by specifying the 
    // hue for the orange you want (a number from 15-30, 15 is more red and 30 is more yellow), then 
    // the saturation (something between 180 and 255 for high saturation) and the brightness (180 to 
    // 255 for bright).
    
    // for grays (and black and white) you can use any value for hue, set the saturation to 0 and 
    // control the level of gray with the brightness value: 255 is white, 0 is black, 128 is 50% gray.    

    
    
    // we want to draw a grid of 5 pixel x 5 pixel rectangles with a fixed hue, varying in 
    // saturation and brightness over X and Y
    
    // we use one hue (value from 0..255) for the whole grid. it changes over time. we use fmodf to
    // keep the hue value between 0 and 255, it works just like integer modulo (the % operator) but 
    // for floats.
    
    
    //我们会演示用HSB（色调）设置颜色。虽然RGB调色方式更有名，但是HSB方式其实比RGB方式更好，。
    //HSB允许我们通过调整3个参数“色相”，“饱和度”，“明度”去指定颜色，这比理解语言中对颜色的抽象定义自然的多，
    //色相有点像彩虹，从红，到黄，到绿，到蓝，到紫，到红，不断循环。
    //饱和度指的是颜色的强度。高饱和度代表亮的颜色,低饱和度代表暗的颜色。
    //如果明度设置为0，不论色相和饱和度的数字是多少颜色都会变成黑色。
    
    //在ofColor里，所有的颜色范围都在0-255之间
    //让我们举个例子来说明。比如说我们要设置一个强烈，明亮的橙色。
    //你需要先设置色相到你想要的橙色（一个15-30之间的数值可能是你想要的，15会偏红一点，30会偏黄一点)。
    //然后调整饱和度（180-255之间可以得到比较饱满的颜色），再调整明度（180-255之间可以得到明亮的颜色）
    //想得到灰色（或则黑，白）你可以用任意的色相，设置饱和度到0，然后控制明度来调节灰度：255是纯白，0是纯黑，128是50%灰度
   
    //我们将画一个由5x5像素格子组成的方形。这个格子的色相是固定的，但是它的饱和度和明度是由鼠标的X，Y参数控制
    //我们把一个固定的色相（0-255之间）应用到所有的格子里。色相会随着时间改变。我们用fmodf指令来保证色相的值在0-255之间，这就像是运用在浮点上的取余运算（%运算符）
    
    
    
    
    float hue = fmodf(ofGetElapsedTimef()*10,255);
    cout<<hue<<endl;
    int step = 5;
    // step through horizontally 设置水平轴
    for ( int i=0; i<ofGetWidth(); i+=step )
    {
        // step through vertically 设置垂直轴
        for ( int j=0; j<ofGetHeight(); j+=step )
        {
            // set HSB using our hue value that changes over time, saturation from the X position (i), 
            // and brightness from the Y position (j). we also invert the Y value since it looks 
            // nicer if the dark/black colors are along the bottom.
            
            //设置色相随时间改变，饱和度随鼠标X坐标(i)改变，明度随鼠标Y坐标（j）改变。我们也会反转鼠标Y的数值使得黑色/暗色保持在底部，这会看起来好一点。
            ofColor c;
            
            // the range of each of the arguments here is 0..255 so we map i and j to that range.
            //每一个参数的范围必须在0-255之间，所以我们需要用一个映射把i和j限制在这个范围内。
            c.setHsb( hue, ofMap(i, 0,ofGetWidth(), 0,255), ofMap(j, ofGetHeight(),0, 0,255 ) );
            
            // assign the color and draw a rectangle
            //分配颜色，并画矩形
            ofSetColor( c );
            ofRect( i, j, step-1, step-1 );
        }
    }
    
    // now we will draw a larger rectangle taking the color under the mouse
    
    // calculate the color under the mouse, using the same calculations as when drawing the grid, 
    // using mouseX and mouseY in place of i and j; draw a rectangle with this color. here we use 
    // ofColor::fromHsb which allows us to set the HSB color in a single line of code.
    
    //现在我们会画一个大一些的矩形，它的颜色就是鼠标下面的颜色
    
    //计算鼠标下面的颜色，使用和画格子时同样的算法,
    //使用mouseX 和 mouseY替换i 和 j；用这个颜色画一个矩形。这里我们使用了ofColor::formHsb， 它让我们可以通过一行代码设置HSB色彩。
    
    ofColor color = ofColor::fromHsb(hue, 
                                     ofMap( mouseX, 0,ofGetWidth(), 0,255 ), 
                                     ofMap( mouseY, ofGetHeight(),0, 0,255 ) );
    
    ofSetColor( color );
    ofFill();
    ofRect( mouseX, mouseY, 100, 100 );
    
    // now draw a white border around the rectangle
    // 现在为每个四边形画一个边框
    ofNoFill();
    ofSetHexColor(0xFFFFFF);
    ofRect( mouseX, mouseY, 100, 100 );
    ofFill();    
    
    // finally we draw text over the rectangle giving the resulting HSB and RGB values 
    // under the mouse
    // 最后我们用文字标出HSB和RGB的值
    // 在底部显示
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString("HSB: "+ofToString(int(hue))+
                       " "+ofToString(int(color.getSaturation()))+
                       " "+ofToString(int(color.getBrightness())),
                       10, ofGetHeight()-13 );
    ofDrawBitmapString("RGB: "+ofToString(int(color.r))+
                       " "+ofToString(int(color.g))+
                       " "+ofToString(int(color.b)), 
                       200, ofGetHeight()-13 );
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    // update mouse x and y percent when the mouse moves
    // 当鼠标移动时，更新鼠标坐标X和Y的百分比
    mouseXPercent = float(x) / ofGetWidth();
    mouseYPercent = float(y) / ofGetHeight();
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
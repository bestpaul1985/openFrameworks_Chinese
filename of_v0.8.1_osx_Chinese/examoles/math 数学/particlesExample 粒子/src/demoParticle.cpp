//04-25-2014
#include "demoParticle.h"


//------------------------------------------------------------------
demoParticle::demoParticle(){
	attractPoints = NULL;
}

//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
	mode = newMode;
}

//------------------------------------------------------------------
void demoParticle::setAttractPoints( vector <ofPoint> * attract ){
	attractPoints = attract;
}

//------------------------------------------------------------------
void demoParticle::reset(){
    
	// the unique val allows us to set properties slightly differently for each particle
    // 给粒子一个随机的数字
	uniqueVal = ofRandom(-10000, 10000);
	
	// 位置，速度，缩放度都是随机的
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.5, 1.0);
	
	if( mode == PARTICLE_MODE_NOISE ){
		drag  = ofRandom(0.97, 0.99);
		vel.y = fabs(vel.y) * 3.0;	// make the particles all be going down
        // 让粒子都向下移动
	}else{
		drag  = ofRandom(0.95, 0.998);
	}
}

//------------------------------------------------------------------
void demoParticle::update(){
    
	// 1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN
	// 1 - 加载的力取决于我们选择何种模式
	if( mode == PARTICLE_MODE_ATTRACT ){
		ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
		frc = attractPt-pos;		// we get the attraction force/vector by looking at the mouse pos relative to our pos
        // 粒子获得的引力是通过计算鼠标位置和粒子位置的关系得到的
        
		frc.normalize();			// by normalizing we disregard how close the particle is to the attraction point
                                    // 通过初始化力，我们忽略了粒子和吸引点之间的距离。
        
		vel *= drag;				// apply drag
                                    // 用拖拽
        
		vel += frc * 0.6;			// apply force
                                    // 用力
	}
	else if( mode == PARTICLE_MODE_REPEL ){
		ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
		frc = attractPt-pos;
		
		// let get the distance and only repel points close to the mouse
        // 击退离鼠标够近的粒子
		float dist = frc.length();
		frc.normalize();
		
		vel *= drag;
		if( dist < 150 ){
			vel += -frc * 0.6;		// notice the frc is negative
                                    // 注意，力是相反的
		}else{
            
			//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
            //如果粒子不够靠近，我们可以用噪点制造一些随机移动。这就是为什么我们前面创建了一个随机数字,它让每个粒子的移动略微不同。
			frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
			frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
			vel += frc * 0.04;
		}
	}
	else if( mode == PARTICLE_MODE_NOISE ){
        
		/* lets simulate falling snow
         the fake wind is meant to add a shift to the particles based on where in x they are
         we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
         
         下面，我们会用粒子模拟下雪的效果
         为了模拟风对雪的影响，我们会在x轴上加入一个移动效果
         提供y坐标为了不给x坐标过多的影响力
         */
		float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
		
		frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
		frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
        
		vel *= drag;
		vel += frc * 0.4;
		
<<<<<<< HEAD:of_v0.8.1_osx_Chinese/examoles/math 数学/particlesExample 粒子/src/demoParticle.cpp
		//we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
        //当粒子到达窗口底部的时候，让粒子返回窗口顶部
=======
		// we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
		// 如果往下移动时发现跨过边界，就屏幕下消失然后从上面出现
>>>>>>> d8732e62180fb6391f7c68518efa473f8cbbff7e:of_v0.8.1_osx_Chinese/examples/math 数学/particlesExample 粒子/src/demoParticle.cpp
		if( pos.y + vel.y > ofGetHeight() ){
			pos.y -= ofGetHeight();
		}
	}
	else if( mode == PARTICLE_MODE_NEAREST_POINTS ){
		
		if( attractPoints ){
<<<<<<< HEAD:of_v0.8.1_osx_Chinese/examoles/math 数学/particlesExample 粒子/src/demoParticle.cpp

			//1 - find closest attractPoint
            //1 - 找到最接近的吸引点
=======
            
			// 1 - find closest attractPoint
			// 1 - 寻找周围最接近的粒子
>>>>>>> d8732e62180fb6391f7c68518efa473f8cbbff7e:of_v0.8.1_osx_Chinese/examples/math 数学/particlesExample 粒子/src/demoParticle.cpp
			ofPoint closestPt;
			int closest = -1;
			float closestDist = 9999999;
			
			for(unsigned int i = 0; i < attractPoints->size(); i++){
				float lenSq = ( attractPoints->at(i)-pos ).lengthSquared();
				if( lenSq < closestDist ){
					closestDist = lenSq;
					closest = i;
				}
			}
			
<<<<<<< HEAD:of_v0.8.1_osx_Chinese/examoles/math 数学/particlesExample 粒子/src/demoParticle.cpp
			//2 - if we have a closest point - lets calcuate the force towards it
            //2 - 找到最接近的吸引点后，计算吸引力大小
=======
			// 2 - if we have a closest point - lets calcuate the force towards it
			// 2 - 计算力对closetPt产生的力量
>>>>>>> d8732e62180fb6391f7c68518efa473f8cbbff7e:of_v0.8.1_osx_Chinese/examples/math 数学/particlesExample 粒子/src/demoParticle.cpp
			if( closest != -1 ){
				closestPt = attractPoints->at(closest);
				float dist = sqrt(closestDist);
				
<<<<<<< HEAD:of_v0.8.1_osx_Chinese/examoles/math 数学/particlesExample 粒子/src/demoParticle.cpp
				//in this case we don't normalize as we want to have the force proportional to distance
                //在这个例子中，当我们更具距离的差值来计算吸引力
=======
				// in this case we don't normalize as we want to have the force proportional to distance
				// 不要规范为0至1，力量必须相对一距离
>>>>>>> d8732e62180fb6391f7c68518efa473f8cbbff7e:of_v0.8.1_osx_Chinese/examples/math 数学/particlesExample 粒子/src/demoParticle.cpp
				frc = closestPt - pos;
                
				// 别忘了乘以拖拽
				vel *= drag;
<<<<<<< HEAD:of_v0.8.1_osx_Chinese/examoles/math 数学/particlesExample 粒子/src/demoParticle.cpp
				 
				//lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
                //让我们限制吸引点的吸引范围
                //当按下f键的时候让吸引点停止工作
				if( dist < 300 && dist > 40 && !ofGetKeyPressed('f') ){
					vel += frc * 0.003;
				}else{
					//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
                    //如果粒子不够靠近，我们可以用噪点制造一些随机移动。这就是为什么我们前面创建了一个随机数字,它让每个粒子的移动略微不同。
=======
                
				// lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
				// 设置吸引力的底线，如果按下'f'就放弃
				if( dist < 300 && dist > 40 && !ofGetKeyPressed('f') ){
					vel += frc * 0.003;
				}else{
					// if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
					// 距离够远的话可以考虑添加一点随机行为
>>>>>>> d8732e62180fb6391f7c68518efa473f8cbbff7e:of_v0.8.1_osx_Chinese/examples/math 数学/particlesExample 粒子/src/demoParticle.cpp
					frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
					frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
					vel += frc * 0.4;
				}
			}
		}
	}
	
	
<<<<<<< HEAD:of_v0.8.1_osx_Chinese/examoles/math 数学/particlesExample 粒子/src/demoParticle.cpp
	//2 - UPDATE OUR POSITION
	//2 - 更新粒子的位置
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN
    //3- （可选）把粒子限制在窗口范围内
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
    //我们可以现在就用一个框来限制粒子的运动范围-或者在ofApp一级里面做这件事
=======
	// 2 - UPDATE OUR POSITION
	// 2 - 更新位置
	pos += vel;
	
	
	// 3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN
	// we could also pass in bounds to check - or alternatively do this at the ofApp level
	// 防止粒子走出屏幕，碰到边界时就立刻改变方向
>>>>>>> d8732e62180fb6391f7c68518efa473f8cbbff7e:of_v0.8.1_osx_Chinese/examples/math 数学/particlesExample 粒子/src/demoParticle.cpp
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -1.0;
	}
}

//------------------------------------------------------------------
void demoParticle::draw(){
    
	// 模式来决定颜色
	if( mode == PARTICLE_MODE_ATTRACT ){
		ofSetColor(255, 63, 180);
	}
	else if( mode == PARTICLE_MODE_REPEL ){
		ofSetColor(208, 255, 63);
	}
	else if( mode == PARTICLE_MODE_NOISE ){
		ofSetColor(99, 63, 255);
	}
	else if( mode == PARTICLE_MODE_NEAREST_POINTS ){
		ofSetColor(103, 160, 237);
	}
	
	// 最后，画出粒子
	ofCircle(pos.x, pos.y, scale * 4.0);
}


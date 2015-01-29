#include "testApp.h"

const float ratioX = 1024.0f/640.0f;
const float ratioY = 768.0f/480.0f;
//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_NOTICE);

#ifdef _DEBUG
	_bFullScreen = false;
#else
	_bFullScreen = true;
#endif
	ofSetFullscreen(_bFullScreen);

	_niContext.setup();
	
	_niDepthGenerator.setup(&_niContext);
	_niImageGenerator.setup(&_niContext);
	_niUserGenerator.setup(&_niContext);
	_niUserGenerator.setListener(this);
	_niUserGenerator.setMaxNumberOfUsers(8);

	_offsetX = 0.0f;
	_offsetY = 0.0f;
	_ThresholdLeft = 68;
	_ThresholdRight = 960;
	verdana.loadFont(ofToDataPath("verdana.ttf"), 24);

	_loader.loadImageFromDirectory(_titles, "titles");

	gui.addPage("offset").setXMLName("offset.xml");
	gui.addTitle("offset");

	gui.addSlider(" X offset", _offsetX, -200, 100);
	gui.addSlider(" Y offset", _offsetY, -200, 100);
	gui.addSlider("Left Threshold", _ThresholdLeft, 0, 124);
	gui.addSlider("Right Threshold", _ThresholdRight, 900, 1024);

	gui.loadFromXML();
	gui.setDefaultKeys(true);
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0, 0, 0);
	_niContext.update();
	_niDepthGenerator.update();
	_niImageGenerator.update();
	_niUserGenerator.update();


	//update buddy position
	//
	if (!_buddys.empty()){
		list<buddy>::iterator it = _buddys.begin();
		list<buddy>::iterator itend = _buddys.end();
		for(; it != itend; ++it){
			ofxTrackedUser*  trackedUser = _niUserGenerator.getTrackedUser(it->_ID);
			if (trackedUser != NULL){
				ofPoint p;
				p.x = trackedUser->neck.position[0].X * ratioX;
				p.y = trackedUser->neck.position[0].Y * ratioY;
				
				it->_loc = p;
				//cout << "location : " << it->_loc.x << " " << it->_loc.y << endl;
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);

	ofPushMatrix();

	ofTranslate(0, 0);
	//        openNIDevices[deviceID].drawDebug(); // debug draw does the equicalent of the commented methods below
	//        openNIDevices[deviceID].drawDepth(0, 0, 640, 480);
	_niImageGenerator.draw(0, 0, 1024, 768);
	//_niUserGenerator.draw();
	if (!_buddys.empty()){
		list<buddy>::iterator it = _buddys.begin();
		list<buddy>::iterator itend = _buddys.end();
		ofEnableAlphaBlending();
		for(; it != itend; ++it){
			if ( it->_loc.x <= _ThresholdLeft || it->_loc.x > _ThresholdRight) continue;
			ofImage *title = &_titles.at(it->_titleIndex);
			int width = title->getWidth()/2;
			int height = title->getHeight()*1.8;

			title->draw(it->_loc.x - width + _offsetX, it->_loc.y - height + _offsetY);
		}
		ofDisableAlphaBlending();
	}

	ofPopMatrix();

	gui.draw();

	/*ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate());
	verdana.drawString(msg, 20, 480 + 26);*/
}
void testApp::exit(){
	_niContext.shutdown();
}

void testApp::UserIn(int id){
	cout << "Get New user id = " << id <<endl;

	ofSeedRandom(ofGetElapsedTimeMillis());
	int titileIndex = ofRandom(_titles.size());
	ofPoint loc(0, 0);
	buddy bud(id, loc, titileIndex);

	// TODO : if id exist
	//.....
	_buddys.push_back(bud);
	cout << "buddys size = " << _buddys.size() << endl;;
}

void testApp::UserOut(int id){
	cout << "Get Lost user id = " << id <<endl;
	list<buddy>::iterator it = std::find_if(_buddys.begin(), 
											_buddys.end(), 
											std::bind2nd(buddyFind(), id));
	if (it != _buddys.end()){
		_buddys.erase(it);
		cout << "buddys size = " << _buddys.size() << endl;;
	}
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if (key == 'f'){
		_bFullScreen = !_bFullScreen;
		ofSetFullscreen(_bFullScreen);
	}
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
#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "ofxSimpleGuiToo.h"
#include "ofxThreadedDirLoader.h"

struct buddy{
public:
	buddy(int id, ofPoint p, int index):
		_ID(id), 
		_loc(p),
		_titleIndex(index){}

	int			_ID;
	ofPoint		_loc;
	int			_titleIndex;
};
struct buddyFind:public std::binary_function<buddy, int, bool>
{
	bool operator ()(const buddy &b, const int id)const
	{
		return (b._ID == id);
	}
};

class testApp : public ofBaseApp, public ofxUserListener{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

protected:
		void UserIn(int id);
		void UserOut(int id);
		
private:
		ofxOpenNIContext		_niContext;
		ofxDepthGenerator		_niDepthGenerator;
		ofxImageGenerator		_niImageGenerator;
		ofxUserGenerator		_niUserGenerator;


		vector<ofImage>			_titles;

		ofxThreadedDirLoader	_loader;

		ofTrueTypeFont verdana;

		bool	_bFullScreen;

		list<buddy>			_buddys;

		int					_offsetX;
		int					_offsetY;
		int					_ThresholdLeft;
		int					_ThresholdRight;

		bool				_bShowTest;
};

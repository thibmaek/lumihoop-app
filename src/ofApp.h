#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSocketIO.h"
#include "ofxSocketIOData.h"
#include "ofxKinect.h"
#include "ofxXmlSettings.h"

/* with <3 your friends Kev & Thib */

class ofApp : public ofBaseApp{
	public:
		void setup();
    void update();
    void draw();
	  void keyPressed(int key);
	
    /* - methods - */
    void drawPointCloud();
		void saveState();
		void loadState();
  
    /* - global variables - */
    float hoopScale, xPos, yPos;
	  int numPointsInRegion, scaleFactorHoop;
		//const char* debugMode = std::getenv("LUMIHOOPDEBUG");
  	bool showmsg = false;
	  bool debugMode = false;
	
    /* - instances - */
    ofxSocketIO socketIO;
    ofxKinect kinect;
    ofEasyCam easyCam;
    ofMesh pointCloud;
	  ofSoundPlayer scoreSound;
    ofxPanel gui;
		ofxXmlSettings state;
    ofxFloatSlider kinectDistanceSlider;
    ofxFloatSlider kinectZSlider;
		ofxFloatSlider kinectAngleSlider;
		ofxFloatSlider kinectSphereZSlider;
	  ofxLabel statusLabel;
	  ofxLabel hostNameLabel;
		ofxButton savebtn;
		ofxButton loadbtn;
	
	  ofVideoPlayer circle_alpha;
	  ofVideoPlayer bg_anim;
	  ofVideoPlayer score_anim;
	
  
    // socket methods
    void onConnection();
    void bindEvents();
    void gotEvent(std::string& name);
  
    // socket events & responses
    ofEvent<ofxSocketIOData&> hoopPlacedEvent;
    void drawHoop(ofxSocketIOData& data);
	
    // socket variables
    bool isConnected;
    std::string address;
    std::string status;
		std::string hostname = ofSystem("uname -n | tr -d '\n'");
};

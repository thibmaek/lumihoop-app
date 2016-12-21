#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSocketIO.h"
#include "ofxSocketIOData.h"
#include "ofxKinect.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
    void update();
    void draw();
  
    /* - methods - */
    void drawPointCloud();
  
    /* - global variables - */
    float hoopScale, xPos, yPos;
	  int numPointsInRegion, scaleFactorHoop;
		const char* debugMode = std::getenv("LUMIHOOPDEBUG");
  	bool showmsg;
	
    /* - instances - */
    ofxSocketIO socketIO;
    ofxKinect kinect;
    ofEasyCam easyCam;
    ofMesh pointCloud;
	  ofSoundPlayer scoreSound;
    ofxPanel gui;
    ofxFloatSlider kinectDistanceSlider;
    ofxFloatSlider kinectXSlider;
    ofxFloatSlider kinectYSlider;
    ofxFloatSlider kinectZSlider;
		ofxFloatSlider kinectAngleSlider;
		ofxFloatSlider kinectSphereZSlider;
	
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
};

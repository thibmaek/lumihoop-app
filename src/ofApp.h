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
    bool debugMode = false;
  
    /* - instances - */
    ofxSocketIO socketIO;
    ofxKinect kinect;
    ofEasyCam easyCam;
    ofMesh pointCloud;
    ofxPanel gui;
    ofxFloatSlider kinectDistanceSlider;
    ofxFloatSlider kinectXSlider;
    ofxFloatSlider kinectYSlider;
    ofxFloatSlider kinectZSlider;
		ofxFloatSlider kinectAngleSlider;
		ofxFloatSlider kinectSphereZSlider;

  
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

#pragma once

#include "ofMain.h"
#include "ofxSocketIO.h"
#include "ofxSocketIOData.h"
#include "ofxKinect.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
    void update();
    void draw();
  
    int hoopX, hoopY;
    float hoopScale;
  
    void gotEvent(std::string& name);
    void onDrawHoop(ofxSocketIOData& data);
  
    ofxSocketIO socketIO;
  
    bool isConnected;
    void onConnection();
    void bindEvents();
    ofEvent<ofxSocketIOData&> serverEvent;
    ofEvent<ofxSocketIOData&> pingEvent;
  
    std::string address;
    std::string status;
  
    ofxKinect kinect;
    ofEasyCam easyCam;
    ofMesh pointCloud;
};

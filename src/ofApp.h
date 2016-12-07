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
  
    /* - Hoop variables - */
    int hoopX, hoopY;
    float hoopScale;

    /* - ofxSocketIO - */
    ofxSocketIO socketIO;
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
  
  
    /* - ofxKinect, ofEasyCam, ofMesh - */
    ofxKinect kinect;
    ofEasyCam easyCam;
    ofMesh pointCloud;
};

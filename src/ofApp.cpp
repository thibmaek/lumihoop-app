#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetLogLevel(OF_LOG_VERBOSE);
  
  ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
  options.host = "localhost";
  options.port = 3000;
  client.connect(options);
  
  ofSetLogLevel(OF_LOG_ERROR);
  client.addListener(this);
  
  kinect.init();
  kinect.open();
  kinect.isConnected() ? ofLog() << "kinect connected" : ofLog() << "kinect not connected";
  
  easyCam.enableMouseInput();
  pointCloud.setMode(OF_PRIMITIVE_POINTS);
  
  ofSetFrameRate(60);
}

void ofApp::update() {
  kinect.update();
  if(kinect.isFrameNewDepth()) {
    pointCloud.clear();
    for(int y = 0; y < kinect.height; y++) {
      for(int x= 0; x < kinect.width; x++) {
        int z = kinect.getDistanceAt(x, y);
        if(z > 0) {
          pointCloud.addColor(ofColor(0xff));
          ofVec3f pt = kinect.getWorldCoordinateAt(x, y);
          pointCloud.addVertex(pt);
        }
      }
    }
  }
}

void ofApp::draw() {
  ofBackground(0);
  easyCam.begin();
  glPushMatrix();
  ofScale(1, -1, -1);
  ofTranslate(0, 0, -100);
  ofEnableDepthTest();
  pointCloud.drawVertices();
  ofDisableDepthTest();
  ofPopMatrix();
  easyCam.end();
  
  ofDrawBitmapString(client.isConnected() ? "Client is connected" : "Client disconnected :(", 10,50);
}

void ofApp::onConnect( ofxLibwebsockets::Event& args ){
  cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
  cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
  cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
  cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
  cout<<"got message "<<args.message<<endl;
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
  cout<<"got broadcast "<<args.message<<endl;
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  isConnected = false;
  address = "http://localhost:3000";
  status = "not connected";
  socketIO.setup(address);
  ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);
  ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
  
//  kinect.init();
//  kinect.open();
//  kinect.isConnected() ? ofLog() << "kinect connected" : ofLog() << "kinect not connected";
//  
//  easyCam.enableMouseInput();
//  pointCloud.setMode(OF_PRIMITIVE_POINTS);
  
  ofSetFrameRate(60);
}

void ofApp::update() {
//  kinect.update();
//  if(kinect.isFrameNewDepth()) {
//    pointCloud.clear();
//    for(int y = 0; y < kinect.height; y++) {
//      for(int x= 0; x < kinect.width; x++) {
//        int z = kinect.getDistanceAt(x, y);
//        if(z > 0) {
//          pointCloud.addColor(ofColor(0xff));
//          ofVec3f pt = kinect.getWorldCoordinateAt(x, y);
//          pointCloud.addVertex(pt);
//        }
//      }
//    }
//  }
}

void ofApp::draw() {
  ofBackground(0);
  ofDrawBitmapStringHighlight(ofApp::status, 20, 20);
  ofSetColor(255, 105, 180);
  ofNoFill();
  ofDrawCircle(hoopX, hoopY, hoopScale);
//  easyCam.begin();
//  glPushMatrix();
//  ofScale(1, -1, -1);
//  ofTranslate(0, 0, -100);
//  ofEnableDepthTest();
//  pointCloud.drawVertices();
//  ofDisableDepthTest();
//  ofPopMatrix();
//  easyCam.end();
}

void ofApp::onConnection () {
  isConnected = true;
  bindEvents();
}

void ofApp::bindEvents () {
  std::string serverEventName = "drawHoop";
  socketIO.bindEvent(serverEvent, serverEventName);
  ofAddListener(serverEvent, this, &ofApp::onDrawHoop);
}

void ofApp::gotEvent(string& name) {
  status = name;
}

//--------------------------------------------------------------
void ofApp::onDrawHoop (ofxSocketIOData& data) {
  hoopX = data.getIntValue("pageX");
  hoopY = data.getIntValue("pageY");
  hoopScale = data.getFloatValue("scale");
  
  ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("pageX")));
  ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("pageY")));
  ofLogNotice("ofxSocketIO", ofToString(data.getFloatValue("scale")));
}

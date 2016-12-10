#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  // MARK: - Initialise socket connection
  isConnected = false;
  address = "http://localhost:3000";
  status = "not connected";
  socketIO.setup(address);
  ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);
  ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
  
  // MARK: - Initialise Kinect connection
  kinect.init();
  kinect.open();
  if (kinect.isConnected()) {
    easyCam.enableMouseInput();
    pointCloud.setMode(OF_PRIMITIVE_POINTS);
  }
  
  // MARK: - Preset drawing setting
  ofSetWindowShape(1024, 768);
  ofSetCircleResolution(64);
  ofSetFrameRate(60);
  
  // MARK: - Initialise debug interface
  gui.setup();
  gui.add(slider.setup("Beamer distance", 0.5, 0, 1.0));
  
  debugMode = true;
}

void ofApp::update() {
  // MARK: - Generate pointcloud from Kinect data
  if(kinect.isConnected()) {
    kinect.update();
    if(kinect.isFrameNewDepth()) {
      pointCloud.clear();
      for(int y = 0; y < kinect.height; y++) {
        for(int x= 0; x < kinect.width; x++) {
          if(kinect.getDistanceAt(x, y) > 0) {
            pointCloud.addColor(ofColor(0xff));
            ofVec3f pt = kinect.getWorldCoordinateAt(x, y);
            pointCloud.addVertex(pt);
          }
        }
      }
    }
  }
}

void ofApp::draw() {
  ofBackground(0);
  
  // MARK: - Draw hoop if global vars are not null
  if(hoopX && hoopY && hoopScale) {
    ofSetColor(255, 105, 180);
    ofNoFill();
    ofSetLineWidth(5);
    ofDrawCircle(hoopX, hoopY, hoopScale * 100);
  }
  
  // MARK: - Display the pointcloud & start easyCam
  drawPointCloud();
  
  // MARK: - Draw debug interface
  if(debugMode) {
    ofDrawBitmapStringHighlight(ofApp::status, 10, 100);
    gui.draw();
  }
}

// MARK: - #BIND_ON_CONNECT
void ofApp::onConnection () {
  isConnected = true;
  bindEvents();
}

// MARK: - #BIND_EVENTS_TO_CALLBACKS
void ofApp::bindEvents () {
  std::string hoopPlacedEventName = "drawHoop";
  socketIO.bindEvent(hoopPlacedEvent, hoopPlacedEventName);
  ofAddListener(hoopPlacedEvent, this, &ofApp::drawHoop);
}

// MARK: - #PROPAGATE_EVENT
void ofApp::gotEvent(string& name) {
  ofLogNotice("ofxSocketIO[gotEvent]", name);
  status = name;
}

//--------------------------------------------------------------
// MARK: - #DRAWS
void ofApp::drawPointCloud() {
  easyCam.begin();
  glPushMatrix();
  ofScale(1, -1, -1);
  ofTranslate(0, 0, -100);
  ofEnableDepthTest();
  pointCloud.drawVertices();
  ofDisableDepthTest();
  ofPopMatrix();
  easyCam.end();
}

//--------------------------------------------------------------
// MARK: - #EVENTS
void ofApp::drawHoop (ofxSocketIOData& data) {
  // MARK: - Log data to console
  ofLogNotice("ofxSocketIO[pageX]", ofToString(data.getIntValue("pageX")));
  ofLogNotice("ofxSocketIO[pageY]", ofToString(data.getIntValue("pageY")));
  ofLogNotice("ofxSocketIO[scale]", ofToString(data.getFloatValue("scale")));
  
  // MARK: - Assign data values to global variables
  hoopX = data.getIntValue("pageX");
  hoopY = data.getIntValue("pageY");
  hoopScale = data.getFloatValue("scale");
}

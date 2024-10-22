#include "ofApp.h"

ofPlanePrimitive plane;

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
	ofSetFrameRate(60);
	easyCam.enableMouseInput();
	pointCloud.setMode(OF_PRIMITIVE_POINTS);
	
  // MARK: - Initialise debug interface
	loadbtn.addListener(this, &ofApp::loadState);
	savebtn.addListener(this, &ofApp::saveState);
	
  gui.setup();
	gui.setDefaultWidth(ofGetWidth()/2);
  gui.add(kinectDistanceSlider.setup("Kinect distance", 2850, 80, 5000));
	gui.add(kinectZSlider.setup("Kinect Scale Z", -0.24, -2, 2));
	gui.add(kinectAngleSlider.setup("Kinect Angle", 0, -10, 10));
	gui.add(statusLabel.setup("status", ofApp::status));
	gui.add(hostNameLabel.setup("Connect to", "http://" + hostname + ":3000"));
	gui.add(savebtn.setup("Save settings"));
	gui.add(loadbtn.setup("Load settings"));

	
	// MARK: - Preset tracking variables
	numPointsInRegion = 0;
	scaleFactorHoop = 200;
  
  // MARK: - Load textures & sounds
	scoreSound.load("score.mp3");
	circle_alpha.setPixelFormat(OF_PIXELS_BGRA);
	circle_alpha.load("circle_alpha.mov");
	circle_alpha.play();
	bg_anim.load("bg.mov");
	bg_anim.play();
	score_anim.setPixelFormat(OF_PIXELS_BGRA);
	score_anim.load("score.mov");
	score_anim.play();
}

void ofApp::update() {
	// MARK: - Update textures
	bg_anim.update();
	circle_alpha.update();
	score_anim.update();
	
	// MARK: - Set Kinect angle via slider
	kinect.setCameraTiltAngle(kinectAngleSlider);
	
	// MARK: - Generate pointcloud from Kinect data
  kinect.update();
	numPointsInRegion = 0;
  if(kinect.isFrameNewDepth()) {
		pointCloud.clear();
    for(int y = 0; y < kinect.height; y++) {
      for(int x= 0; x < kinect.width; x++) {
        int z = kinect.getDistanceAt(x, y);
        if(z > 0) {
          pointCloud.addColor(kinect.getColorAt(x, y));
          ofVec3f pt = kinect.getWorldCoordinateAt(x, y);
          pointCloud.addVertex(pt);
						
			  	int halfRegionSize = (hoopScale) / 2;
					if((pt.x > xPos-halfRegionSize && pt.x < xPos + halfRegionSize)
						&& (pt.y > yPos-halfRegionSize && pt.y < yPos + halfRegionSize)
						&& (pt.z > kinectDistanceSlider-halfRegionSize && pt.z < kinectDistanceSlider + halfRegionSize)){
							numPointsInRegion += 1;
          }
				}
			}
		}
	}
}
											
void ofApp::saveState() {
	state.setValue("state:kinectDistanceSlider", kinectDistanceSlider);
	state.setValue("state:kinectZSlider", kinectZSlider);
	state.saveFile("state.xml");
}

void ofApp::loadState() {
	state.loadFile("state.xml");
	kinectZSlider = state.getValue("state:kinectZSlider", 2850);
	kinectDistanceSlider = state.getValue("state:kinectDistanceSlider", -0.239999995);
}

// MARK: - #TOGGLE_UI
void ofApp::keyPressed(int key){
	if (key == ' '){
		if(debugMode == true) {
			debugMode = false;
		}
		else if(debugMode == false) {
			debugMode = true;
		}
	}
}

void ofApp::draw() {
	// MARK: - Draw backgrounds
  ofBackground(0);
	bg_anim.draw(0, 0, ofGetWidth(), ofGetWidth());
  
  // MARK: - Start tracking & drawing hoops
	easyCam.begin();
	ofPushMatrix();
	ofScale(1, -1, kinectZSlider);
	ofTranslate(0, 0, -1000);
	
	if(debugMode) {
		ofEnableDepthTest();
		pointCloud.drawVertices();
		ofDisableDepthTest();
	}
	
	if(numPointsInRegion > 100) {
		ofFill();
		ofLogNotice("DETECTED");
		std::string hoopHitEventName = "detectHit";
		std::string param = "param";
		socketIO.emit(hoopHitEventName, param);
		scoreSound.play();
		hoopScale = 0;
		showmsg = true;
	} else {
		ofNoFill();
	}
	
	if(debugMode) ofDrawBox(xPos, yPos, kinectDistanceSlider-220, hoopScale, hoopScale, 400);
	
	if(showmsg) {
		ofPushMatrix();
		ofScale(1, -1, 1);
		ofTranslate(0, 0, kinectDistanceSlider-220);
		score_anim.draw(-320,-240, 640, 480);
		ofPopMatrix();
	} else {
		score_anim.draw(-320,-240, 0, 0);
	}
	
	
	// MARK: - DRAW CIRCLE ANIMATION
	ofPushMatrix();
	ofTranslate(0, 0, kinectDistanceSlider-220);
	circle_alpha.draw(xPos-(hoopScale/2), yPos-(hoopScale/2), hoopScale, hoopScale);
	ofPopMatrix();

	ofPopMatrix();
	easyCam.end();
	
  // MARK: - Draw debug interface
  if(debugMode) {
    gui.draw();
    kinect.setCameraTiltAngle(kinectAngleSlider);
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

// MARK: - #EVENTS
void ofApp::drawHoop (ofxSocketIOData& data) {
  // MARK: - Log data to console
  ofLogNotice("ofxSocketIO[pageX]", ofToString(data.getFloatValue("relX")));
  ofLogNotice("ofxSocketIO[pageY]", ofToString(data.getFloatValue("relY")));
  ofLogNotice("ofxSocketIO[scale]", ofToString(data.getFloatValue("scale")));

  // MARK: - Assign data values to global variables
	if(data.getFloatValue("scale") > 2.4){
		hoopScale = 2.2 * scaleFactorHoop;
	} else {
		hoopScale = (data.getFloatValue("scale"))* scaleFactorHoop;
	}
	
  xPos = (data.getFloatValue("relX"))* ofGetWidth();
  yPos = (data.getFloatValue("relY"))* ofGetHeight();
	
	showmsg = false;
}

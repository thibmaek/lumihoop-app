#pragma once

#include "ofMain.h"
#include "ofxLibwebsockets.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
    void draw();

    ofxLibwebsockets::Client client;
    void onConnect(ofxLibwebsockets::Event& args);
    void onOpen(ofxLibwebsockets::Event& args);
    void onClose(ofxLibwebsockets::Event& args);
    void onIdle(ofxLibwebsockets::Event& args);
    void onMessage(ofxLibwebsockets::Event& args);
    void onBroadcast(ofxLibwebsockets::Event& args);
};

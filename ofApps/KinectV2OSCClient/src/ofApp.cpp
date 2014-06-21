#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);

	const int port = 30001;
	oscReceiver.setup(port);
	ofLog(OF_LOG_VERBOSE, "Receiving OSC on port: " + ofToString(port));


}

//--------------------------------------------------------------
void ofApp::update(){
	ofxOscMessage m;
	while (oscReceiver.getNextMessage(&m)) {
		ofLog(OF_LOG_VERBOSE, m.getAddress());

		for (int i = 0; i < m.getNumArgs(); i++) {
			ofxOscArgType argType = m.getArgType(i);

			switch (argType)
			{
			case OFXOSC_TYPE_FLOAT:
				ofLog(OF_LOG_VERBOSE, ofToString(i) + ": " + ofToString(m.getArgAsFloat(i)));
				break;
			case OFXOSC_TYPE_INT32:
				ofLog(OF_LOG_VERBOSE, ofToString(i) + ": " + ofToString(m.getArgAsInt32(i)));
				break;
			case OFXOSC_TYPE_STRING:
				ofLog(OF_LOG_VERBOSE, ofToString(i) + ": " + ofToString(m.getArgAsString(i)));
				break;
			default:
				ofLog(OF_LOG_VERBOSE, ofToString(i) + ": " + "unhandled");
				break;
			}

		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

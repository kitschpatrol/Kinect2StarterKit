#include "testApp.h"
#define VM_DEVELOPMENT 1

//--------------------------------------------------------------
void testApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);

#if VM_DEVELOPMENT
	kinect.initSensor();
	kinect.initColorStream(false);
	kinect.initDepthStream(true);
	//kinect.initBodyIndexStream();
	kinect.initSkeletonStream(false);
	//kinect.setUseTexture(true);
	//simple start
	kinect.start();
#endif

	ofDisableAlphaBlending(); //Kinect alpha channel is default 0;

	//sender.setup("192.168.10.113", 12345);
	sender.setup("192.168.10.101", 3001);
}


const string trackingStateNames[] = {
	"untracked",
	"inferred",
	"tracked"
};

const string jointNames[] = {
	"spinebase",
	"spinemid",
	"beck",
	"head",
	"shoulderleft",
	"elbowleft",
	"wristleft",
	"handleft",
	"shoulderright",
	"elbowright",
	"elbowright",
	"wristright",
	"handright",
	"hipleft",
	"kneeleft",
	"ankleleft",
	"footleft",
	"hipright",
	"kneeright",
	"ankleright",
	"footright",
	"spineshoulder",
	"handtipleft",
	"thumbleft",
	"handtipright",
	"thumbright"
};

//--------------------------------------------------------------
void testApp::update() {
#if VM_DEVELOPMENT
	kinect.update();

	// Broadcast OSC
	if (kinect.isFrameNew()) {
		
		// Interate through skeletons
		ofxOscBundle skeletonsBundle; // note the plural!

		vector<Kv2Skeleton> localSkeletons = kinect.getSkeletons();

		for (int i = 0; i < localSkeletons.size(); i++) {
			if (localSkeletons[i].tracked) {
				// Iterate through joints
				ofxOscBundle skeletonBundle;

				for (int j = 0; j < 26; j++) {
					JointType jointType = (JointType)j;
					Kv2Joint joint = localSkeletons[i].joints[jointType];
					/*
				for (map<JointType, Kv2Joint>::iterator it = localSkeletons[i].joints.begin(); it != localSkeletons[i].joints.end(); ++it) {
					// Skeleton index
					JointType jointType = it->first;
					Kv2Joint joint = it->second;
					*/
					// Get position and rotation
					ofxOscMessage jointPositionMessage;
					jointPositionMessage.setAddress("/skeletons/" + ofToString(i) + "/joints/" + jointNames[jointType] + "/position"); // position is X Y Z
					jointPositionMessage.addFloatArg(joint.getPosition().x);
					jointPositionMessage.addFloatArg(joint.getPosition().y);
					jointPositionMessage.addFloatArg(joint.getPosition().z);
					skeletonBundle.addMessage(jointPositionMessage);

					ofxOscMessage jointOrientationMessage;
					jointOrientationMessage.setAddress("/skeletons/" + ofToString(i) + "/joints/" + jointNames[jointType] + "/orientation"); // quaternion is X Y Z W
					jointOrientationMessage.addFloatArg(joint.getOrientation().asVec4().x);
					jointOrientationMessage.addFloatArg(joint.getOrientation().asVec4().y);
					jointOrientationMessage.addFloatArg(joint.getOrientation().asVec4().z);
					jointOrientationMessage.addFloatArg(joint.getOrientation().asVec4().w);
					skeletonBundle.addMessage(jointOrientationMessage);

					//ofxOscMessage jointTrackingStateMessage;
					//jointTrackingStateMessage.setAddress("/skeletons/" + ofToString(i) + "/joints/" + jointNames[jointType] + "/tracking"); // string state
					//jointTrackingStateMessage.addStringArg(trackingStateNames[joint.getTrackingState()]);
					//skeletonBundle.addMessage(jointTrackingStateMessage);
				}
				
				skeletonsBundle.addBundle(skeletonBundle);
			}
		}

		sender.sendBundle(skeletonsBundle);
	}
#endif		
}

//--------------------------------------------------------------
void testApp::draw() {
	ofBackground(0, 255);
	
#if VM_DEVELOPMENT
	kinect.draw(0,0);
	kinect.drawDepth(0, 0);
	kinect.drawBodyIndex(500, 0);
	kinect.drawAllSkeletons(ofVec2f(640,480));
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 't' || key == 'T'){
		ofLog(OF_LOG_NOTICE, "Sending OSC test message");
		ofxOscMessage m;
		m.setAddress("/test");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef());
		sender.sendMessage(m);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
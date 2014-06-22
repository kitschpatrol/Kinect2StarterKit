#include "ofApp.h"

TrackingState trackingStateFromOscTrackingStateName(string trackingStateName) {
	const int trackingStateCount = 3;
	const string trackingStateNames[] = {
		"untracked",
		"inferred",
		"tracked"
	};

	for (int i = 0; i < trackingStateCount; i++) {
		if (trackingStateNames[i] == trackingStateName) {
			return (TrackingState)i;
		}
	}
}


JointType jointTypeFromOscJointName(string jointName) {
	const int oscJointCount = 26;
	const string oscJointNames[] = {
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

	for (int i = 0; i < oscJointCount; i++) {
		if (oscJointNames[i] == jointName) {
			return (JointType)i;
		}
	}

}



//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	messagesReceived = 0;
	const int port = 3001;
	oscReceiver.setup(port);
	skeletons.resize(6);
	ofLog(OF_LOG_VERBOSE, "Receiving OSC on port: " + ofToString(port));
}





//--------------------------------------------------------------
void ofApp::update(){
	static int updateCalls = 0;
	updateCalls++;
	ofxOscMessage m;

	if (oscReceiver.hasWaitingMessages()) {
		ofLog(OF_LOG_VERBOSE, "-------- messages available ---------");
		int messagesInUpdate = 0;
		while (oscReceiver.getNextMessage(&m)) {
			messagesReceived++;
			messagesInUpdate++;
			// Log stuff
			//ofLog(OF_LOG_VERBOSE, m.getAddress());
			for (int i = 0; i < m.getNumArgs(); i++) {

				//ofxOscArgType argType = m.getArgType(i);
				
				//ofLog(OF_LOG_VERBOSE, m.getArgTypeName(i));

				/*
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
				*/
			}

			// Extract the skeletons
			vector<string> addressComponents = ofSplitString(m.getAddress(), "/", true, true);

			if (addressComponents[0] == "skeletons") {

				// Get index
				int skeletonIndex = ofToInt(addressComponents[1]);

				//	map<JointType, Kv2Joint> joints;

				// Check for tracking
				if (addressComponents[2] == "tracked") {
					skeletons[skeletonIndex].tracked = (m.getArgAsString(0) == "yes");
				}
				else if (addressComponents[2] == "joints") {
					// Joint name

					Kv2Joint joint;
					JointType jointType = jointTypeFromOscJointName(addressComponents[3]);
					Kv2Joint existingJoint = skeletons[skeletonIndex].joints[jointType];

					// Joint values
					if (addressComponents[4] == "position") {
						// Use existing orientation
						_JointOrientation orientation;
						orientation.JointType = jointType;
						orientation.Orientation.x = existingJoint.getOrientation().asVec4().x;
						orientation.Orientation.y = existingJoint.getOrientation().asVec4().y;
						orientation.Orientation.z = existingJoint.getOrientation().asVec4().z;
						orientation.Orientation.w = existingJoint.getOrientation().asVec4().w;

						// use position from args

						_Joint joint;
						joint.JointType = jointType;
						joint.Position.X = m.getArgAsFloat(0);
						joint.Position.Y = m.getArgAsFloat(1);
						joint.Position.Z = m.getArgAsFloat(2);

						// tracking state from existing object
						joint.TrackingState = existingJoint.getTrackingState();

						// Update the skeleton
						skeletons[skeletonIndex].joints[jointType] = Kv2Joint(joint, orientation);
					}
					else if (addressComponents[4] == "orientation") {
						// Orientation from args
						_JointOrientation orientation;
						orientation.JointType = jointType;
						orientation.Orientation.x = m.getArgAsFloat(0);
						orientation.Orientation.y = m.getArgAsFloat(1);
						orientation.Orientation.z = m.getArgAsFloat(2);
						orientation.Orientation.w = m.getArgAsFloat(3);

						// Joint from existing object
						_Joint joint;
						joint.JointType = jointType;
						joint.Position.X = existingJoint.getPosition().x;
						joint.Position.Y = existingJoint.getPosition().y;
						joint.Position.Z = existingJoint.getPosition().z;

						// tracking state from existing object
						joint.TrackingState = existingJoint.getTrackingState();

						// Update the skeleton
						skeletons[skeletonIndex].joints[jointType] = Kv2Joint(joint, orientation);
					}
					else if (addressComponents[4] == "tracking") {
						// Use existing orientation
						_JointOrientation orientation;
						orientation.JointType = jointType;
						orientation.Orientation.x = existingJoint.getOrientation().asVec4().x;
						orientation.Orientation.y = existingJoint.getOrientation().asVec4().y;
						orientation.Orientation.z = existingJoint.getOrientation().asVec4().z;
						orientation.Orientation.w = existingJoint.getOrientation().asVec4().w;

						// Joint from existing object
						_Joint joint;
						joint.JointType = jointType;
						joint.Position.X = existingJoint.getPosition().x;
						joint.Position.Y = existingJoint.getPosition().y;
						joint.Position.Z = existingJoint.getPosition().z;

						// tracking state from existing object
						joint.TrackingState = trackingStateFromOscTrackingStateName(m.getArgAsString(0));

						// Update the skeleton
						skeletons[skeletonIndex].joints[jointType] = Kv2Joint(joint, orientation);
					}
				}

				// TODO
				// Hands
				// Face / emotion
				// Identity
			}

			/*
			vector<string>::iterator it;
			for (it = addressComponents.begin(); it != addressComponents.end(); it++) {
				string component = *it;



				ofLog(OF_LOG_VERBOSE, "path component:" + component);
			}
			*/
		}


		ofLog(OF_LOG_VERBOSE, "messages received: " + ofToString(messagesReceived));
		//ofLog(OF_LOG_VERBOSE, "messages in update: " + ofToString(messagesInUpdate));
		//ofLog(OF_LOG_VERBOSE, "update calls: " + ofToString(updateCalls));

	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(200);

	ofPushStyle();

	ofPushMatrix();

	int longestSideOfWindow = MAX(ofGetWidth(), ofGetHeight());
	ofScale(longestSideOfWindow, longestSideOfWindow);


	// Draw tracked joints...

	 for (vector<Kv2Skeleton>::iterator it = skeletons.begin(); it != skeletons.end(); it++) {
		Kv2Skeleton skeleton = *it;
		
		if (skeleton.tracked) {

		for (map<JointType, Kv2Joint>::iterator it = skeleton.joints.begin(); it != skeleton.joints.end(); it++) {
			Kv2Joint joint = it->second;

			switch (joint.getTrackingState()) {
			case TrackingState_Tracked:
				ofSetColor(ofColor::green);
				break;
			case TrackingState_Inferred:
				ofSetColor(ofColor::yellow);
				break;
			case TrackingState_NotTracked:
				ofSetColor(ofColor::red);
				break;
			}

			ofFill();

			//ofLog(OF_LOG_VERBOSE, ofToString(joint.getPosition().length()));

			ofCircle(joint.getPosition().x, joint.getPosition().y, .05);
		}

		}
	}

	 ofPopMatrix();
	ofPopStyle();
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

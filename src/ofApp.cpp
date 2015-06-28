#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableSmoothing();
	ofSetFrameRate(30);
	ofBackground(0);
	particleNet = new ParticleNet(N_PARTICLES);

	nBandsToGet = 8;

	sound.loadSound("mp3/test2.mp3");
	sound.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	float sumLow = 0;
	particleNet->pull(ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 100, 200, 200, val[0]);
	particleNet->hit(3, 0, ofVec2f(0, 10) * val[1]);
	particleNet->hit(6, 0, ofVec2f(0, 10) * val[2]);
	particleNet->hit(9, 0, ofVec2f(0, 10) * val[3]);
	particleNet->hit(12, 0, ofVec2f(0, 10) * val[4]);
	particleNet->hit(15, 0, ofVec2f(0, 10) * val[5]);
	particleNet->hit(18, 0, ofVec2f(0, 10) * val[6]);
	particleNet->hit(21, 0, ofVec2f(0, 10) * val[7]);

	particleNet->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	particleNet->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

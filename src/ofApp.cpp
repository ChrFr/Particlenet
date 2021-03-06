#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableSmoothing();
	ofSetFrameRate(30);
	ofBackground(0);
	particleNet = new ParticleNet(N_PARTICLES);

	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	soundStream.listDevices();

	//if you want to set a different device id 
	//soundStream.setDeviceID(1); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.

	int bufferSize = 256;

	left = new std::complex<double>[bufferSize];
	for (int i = 0; i<bufferSize; i++)
		left[i] = 0.0;
/*	
	left.assign(bufferSize, 0.0);/*
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);

	bufferCounter = 0;
	drawCounter = 0;
	smoothedVol = 0.0;
	scaledVol = 0.0;*/
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
	emath::fft(8, left);
	val = 0;
	for (int i = 0; i < 20; i++){
		double power = left[i].real()*left[i].real() + left[i].imag()*left[i].imag();
		val += sqrt(power);
	}
	val /= 20;


	//float * val = ofSoundGetSpectrum(nBandsToGet);
	//float sumLow = 0;
	/*
	particleNet->pull(ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 100, 200, 200, val[0]);
	particleNet->hit(3, 0, ofVec2f(0, 10) * val[1]);
	particleNet->hit(6, 0, ofVec2f(0, 10) * val[2]);
	particleNet->hit(9, 0, ofVec2f(0, 10) * val[3]);
	particleNet->hit(12, 0, ofVec2f(0, 10) * val[4]);
	particleNet->hit(15, 0, ofVec2f(0, 10) * val[5]);
	particleNet->hit(18, 0, ofVec2f(0, 10) * val[6]);
	particleNet->hit(21, 0, ofVec2f(0, 10) * val[7]);*/
	particleNet->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    particleNet->draw();
	ofSetColor(255, 255, 255);
	std::ostringstream strs;
	strs << val;
	std::string str = strs.str();
	ofDrawBitmapString(str, 20, 50);
}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){

	//float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i * 2] * 0.5;
		//right[i] = input[i * 2 + 1] * 0.5;

		//curVol += left[i] * left[i];
		//curVol += right[i] * right[i];
		numCounted += 2;
	}

	//this is how we get the mean of rms :) 
	//curVol /= (float)numCounted;

	// this is how we get the root of rms :) 
	//curVol = sqrt(curVol);

	//smoothedVol *= 0.93;
	//smoothedVol += 0.07 * curVol;

	bufferCounter++;

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

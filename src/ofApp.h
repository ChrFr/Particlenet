#pragma once
//#define OF_SOUND_PLAYER_OPENAL
//#undef OF_SOUND_PLAYER_FMOD
#include "ofMain.h"

#include "ParticleNet.h"
#include "arithmetic.h"

#define N_PARTICLES 10000

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ParticleNet *particleNet;

	void audioIn(float * input, int bufferSize, int nChannels);

	std::complex<double>* left;
	std::complex<double>* right;
	std::complex<double> val;
	//vector <float> left;
	//vector <float> right;
	vector <float> volHistory;
	ofPoint lastMousePos;

	int bufferCounter;
	int drawCounter;

	float smoothedVol;
	float scaledVol;

	ofSoundStream soundStream;
	ofSoundPlayer sound;

	int nBandsToGet;

};


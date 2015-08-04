#ifndef particle_h
#define particle_h

#include "ofMain.h"

class Particle {
private:

	//the radius of the area of effect around the particle
	float forceRadius;
	float maxDistance;
	
	float startSize;

public:
	// Constructor
	Particle(float x, float y, float size, int c, int r, float forceRadius, float maxDistance);

	// Methods
	virtual void draw() = 0;

	ofColor startColor;
	ofColor color;

	//current position
	ofPoint pos;

	//start position
	ofPoint startPos;
		
	ofPoint velocity;
	ofPoint direction;
	vector<Particle *> neighbours;

	//position in grid	
	float c;
	float r;

	float size;

	//the z-position of the particle
	float z;

	void adaptAppearance();

	void update();

	void Particle::pull(float z);
};
#endif
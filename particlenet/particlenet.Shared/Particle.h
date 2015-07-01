#ifndef particle_h
#define particle_h

#include "ofMain.h"

class Particle {
private:

	//the radius of the area of effect around the particle
	float forceRadius;
	float maxDistance;

	//the energy the particle moves with
	float kineticEnergy;

	float startSize;

public:
	// Constructor
	Particle(float x, float y, float size, int c, int r, float forceRadius, float maxDistance);

	// Methods
	virtual void draw() = 0;

	ofColor startColor;
	ofColor color;

	//current position
	ofVec2f pos;

	//start position
	ofVec2f startPos;

	//position in grid	
	float c;
	float r;

	float size;

	//the z-position of the particle
	float z;

	void adaptAppearance();

	void update();

	ofVec2f kDir;
};
#endif
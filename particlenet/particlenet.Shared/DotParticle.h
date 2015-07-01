#ifndef dotparticle_h
#define dotparticle_h

#include "Particle.h"
#include "ofMain.h"

class DotParticle : public Particle {
public:
	// Constructor
	DotParticle::DotParticle(float x, float y, float size, float c, float r, float forceRadius, float maxDistance);

	void draw();
};
#endif
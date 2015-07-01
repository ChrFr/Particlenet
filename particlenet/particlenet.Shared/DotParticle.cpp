
#include "DotParticle.h"

DotParticle::DotParticle(float x, float y, float size, float c, float r, float forceRadius, float maxDistance) : Particle(x, y, size, c, r, forceRadius, maxDistance){};

void DotParticle::draw(){
	adaptAppearance();
	ofSetColor(color);
	ofCircle(pos.x, pos.y, size);
}
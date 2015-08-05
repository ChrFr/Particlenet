#include "Particle.h"

Particle::Particle(float x, float y, float size, int c, int r, float forceRadius, float maxDistance) : startSize(size), size(size), c(c), r(r), forceRadius(forceRadius), maxDistance(maxDistance){
	z = 0;
	velocity = ofPoint(0, 0);
	pos = ofPoint(x, y);
	startPos = ofPoint(x, y);
}

void Particle::adaptAppearance(){
	int brightness = 128 + z * 128;
	int saturation = 255;
	float energy = (direction.length() > 2) ? 2: direction.length();
	ofPoint dist = startPos-pos;
	float hue = 170 - (dist.length() / maxDistance) * 170;
	if (hue < 0)
		hue = 0;
	if (z > 0)
		saturation -= z * 128;
	size = startSize + startSize * z;
	color.setHue(hue);
	color.setSaturation(saturation);
	color.setBrightness(brightness);
}

void Particle::update(){
	
	// push neighbours	
	if(direction.length() > 0.1) 
		for (int j = 0; j < neighbours.size(); j++){
			Particle* neighbour = neighbours.at(j);
			if(neighbour){
				//if((neighbour)){// && (pos - neighbour->pos).length() <= 20){
				ofPoint a = pos - neighbour->pos;
				float b = a.getNormalized().dot(direction.getNormalized());
				// is neighbour in direction of movement?
				if(b > 0.5 && b <= 1){
					neighbour->nextDir = a.getNormalized() * direction.length() * 0.8;
				}			
			}
		}
		
	// particle is always dragged back to its starting point
	ofPoint dist = startPos-pos;
	ofPoint retraction = dist.getNormalized() * (dist.length() / maxDistance);
	pos += direction + retraction;

	// energy reduces over time
	direction *= 0.95;	
	/*
	if(nextDir.length() > 0){
		direction = nextDir;
		nextDir = ofPoint(0, 0);
	}*/

	// move z 
	if (z > 0)
		z -= 0.1;
	else if (z < 0)
		z = 0;
}

// pull single particle and its neighbours recursively
void Particle::pull(float z){
	//end of recursion
	if (z < 0.1 || this->z >= z)
		return;
	this->z = z;
	for (int j = 0; j < neighbours.size(); j++){
		Particle* neighbour = neighbours[j];
		if (neighbour)
			neighbour->pull(z * 0.8);
	}
}

void Particle::push(ofPoint dir){
	direction = dir;
	if(dir.length() < 0.1)
		return;
	for (int j = 0; j < neighbours.size(); j++){
		Particle* neighbour = neighbours.at(j);
		if((neighbour)){// && (pos - neighbour->pos).length() <= 20){
			ofPoint a = pos - neighbour->pos;
			float b = a.getNormalized().dot(direction.getNormalized());
			// is neighbour in direction of movement? (theta < 90°)
			if(b > 0.25 && b <= 1){
				neighbour->push(a.getNormalized() * direction.length() * 0.8);
			}	
		}
	}
};
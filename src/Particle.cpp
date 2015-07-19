#include "Particle.h"

Particle::Particle(float x, float y, float size, int c, int r, float forceRadius, float maxDistance) : startSize(size), size(size), c(c), r(r), forceRadius(forceRadius), maxDistance(maxDistance){
	z = 0;
	kDir = ofVec2f(0, 0);
	pos = ofVec2f(x, y);
	startPos = ofVec2f(x, y);
}

void Particle::adaptAppearance(){
	int brightness = 128 + z * 128;
	int saturation = 255;
	float hue = 170 - kDir.length() * 70;
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
	//z blocks movement
	kDir *= (1 - z);
	if (kDir.length() != 0){
		pos += kDir;
		//kDir *= 0.9;
	}
	//if((pos - startPos).length() <= 0) this won't work (no negative length)
	//	kDir *= 0;
	if ((pos - startPos).length() >= maxDistance || kDir.length() < 0.1){
		//kDir *=  startPos - pos;
		//if(kDir.length() < 1)
		kDir = kDir.normalize();
		kDir *= -1;
	}/*
	 if(kDir.length() != 0){
	 kDir *= (1 - z);
	 kDir *= 0.95;
	 if((pos - startPos).length() >= maxDistance){
	 if(kDir.length() < 1)
	 kDir = kDir.normalize();
	 pos -= 5 * kDir;
	 }
	 else
	 pos += kDir;
	 }*/
	if (z > 0)
		z -= 0.1;
	else if (z < 0)
		z = 0;
}
#ifndef particlenet_h
#define particlenet_h

#include "ofMain.h"
#include "Particle.h"
#include "DotParticle.h"

//maximum energy a particle can have in z-direction (=peak)
#define MAX_Z_ENERGY 1

class ParticleNet
{
private:
	//number of particles per row
	int columns;
	//number of rows
	int rows;

	int pxDistance;

	vector<Particle *> particles;

	Particle** getNeighbours(int c, int r);
	Particle** getNeighbours(int pos);
	void ParticleNet::pull(Particle *particle, float z);

public:
	// Constructor
	ParticleNet(int nParticles);

	//TODO: rewrite for x/y or shapes
	void pull(int x, int y, int width, int height, float energy);

	Particle* at(int r, int c);
	void drawMulticolorLine(int x1, int y1, int x2, int y2, ofColor color1, ofColor color2);

	void hit(int c, int r, ofVec2f dir);

	void draw();
	void update();
};
#endif
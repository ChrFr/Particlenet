#include "ParticleNet.h"

ParticleNet::ParticleNet(int nParticles){
	float size = 2;
	columns = sqrt((ofGetWindowWidth() / ofGetWindowHeight()) * nParticles);
	rows = nParticles / columns;

	pxDistance = ofGetWindowWidth() / columns;

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			particles.push_back(new DotParticle(c * pxDistance + pxDistance / 2, r * pxDistance + pxDistance / 2, size, c, r, pxDistance / 2, pxDistance));
	for (int i = 0; i < particles.size(); i++)
		particles[i]->neighbours = getNeighbours(particles[i]->c, particles[i]->r);
}

void ParticleNet::draw(){
	vector<Particle*>::iterator it = particles.begin();
	while (it != particles.end()){
		(*it)->draw();

		//Particle** neighbours = getNeighbours(i);	
		/*
		//draw lines to the left/upperleft/upper/right neighbour
		for(int n = 0; n < 4; n++)
			if((*it)->neighbours[n])
				drawMulticolorLine((*it)->pos.x, (*it)->pos.y, (*it)->neighbours[n]->pos.x, (*it)->neighbours[n]->pos.y, (*it)->color, (*it)->neighbours[n]->color);
		*/
		++it;
	}
}

//sadly there is no gradient color for lines
void ParticleNet::drawMulticolorLine(int x1, int y1, int x2, int y2, ofColor color1, ofColor color2){
	//easy half split line by now; maybe more complex later
	int xm = x1 + ((x2 - x1) / 2);
	int ym = y1 + ((y2 - y1) / 2);

	ofSetColor(color1);
	ofLine(x1, y1, xm, ym);

	ofSetColor(color2);
	ofLine(xm, ym, x2, y2);
}

vector<Particle *> ParticleNet::getNeighbours(int pos){
	int r = pos / columns;
	int c = pos % columns;
	return getNeighbours(c, r);
}

vector<Particle *> ParticleNet::getNeighbours(int c, int r){

	// every particle has potentially 8 neighbours
	vector<Particle *> neighbours;

	Particle * neighbour;
	
	// upper left
	neighbours.push_back(at(c - 1, r - 1));
	// upper
	neighbours.push_back(at(c, r - 1));
	// upper right
	neighbours.push_back(at(c + 1, r - 1));
	// right
	neighbours.push_back(at(c + 1, r));
	// lower right
	neighbours.push_back(at(c + 1, r + 1));
	// lower
	neighbours.push_back(at(c, r + 1));
	// lower left
	neighbours.push_back(at(c - 1, r + 1));
	//left
	neighbours.push_back(at(c - 1, r));

	return neighbours;
};

Particle * ParticleNet::at(int c, int r){
	int pos;
	//out of bounds
	if (r < 0 || c < 0 || r >= rows || c >= columns)
		return NULL;

	pos = c + r * columns;
	return particles.at(pos);
}

void ParticleNet::pull(int x, int y, int width, int height, float energy){
	int c0 = (x / pxDistance);
	int r0 = (y / pxDistance);
	int c1 = c0 + (width / pxDistance);
	int r1 = r0 + (height / pxDistance);

	if (energy > MAX_Z_ENERGY)
		energy = MAX_Z_ENERGY;
	float z = energy / MAX_Z_ENERGY;
	if (z > 1)
		z = 1;
	else if (z < -1)
		z = -1;
	for (int r = r0; r <= r1; r++)
		for (int c = c0; c <= c1; c++){
			at(c, r)->pull(z);
		}
};

void ParticleNet::push(int x, int y, ofPoint dir){
	
	int c = (x / pxDistance);
	int r = (y / pxDistance);

	Particle *particle = at(c, r);
	//if ((particle->pos - particle->startPos).length() <= pxDistance / 2)
		particle->direction = dir;
		//particle->push(dir);
};

void ParticleNet::update(){
	vector<Particle *>::iterator it = particles.begin();
	while (it != particles.end()){
		
		(*it)->update();
		it++;
	}
	it = particles.begin();
	while (it != particles.end()){
		
		(*it)->direction = (*it)->nextDir;
		(*it)->nextDir = ofPoint(0, 0);
		it++;
	}

};
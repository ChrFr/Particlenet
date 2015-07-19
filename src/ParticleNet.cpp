#include "ParticleNet.h"

ParticleNet::ParticleNet(int nParticles){
	float size = 4;
	columns = sqrt((ofGetWindowWidth() / ofGetWindowHeight()) * nParticles);
	rows = nParticles / columns;

	pxDistance = ofGetWindowWidth() / columns;

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			particles.push_back(new DotParticle(c * pxDistance + pxDistance / 2, r * pxDistance + pxDistance / 2, size, c, r, pxDistance / 2, pxDistance));

}

void ParticleNet::draw(){
	vector<Particle *>::iterator it = particles.begin();
	int i = 0;
	while (it != particles.end()){
		(*it)->draw();

		//Particle** neighbours = getNeighbours(i);	

		//draw lines to the left/upperleft/upper/right neighbour
		//for(int n = 0; n < 4; n++)
		//if(neighbours[n])
		//drawMulticolorLine((*it)->x, (*it)->y, neighbours[n]->x, neighbours[n]->y, (*it)->color, neighbours[n]->color);
		++it;
		++i;
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

Particle** ParticleNet::getNeighbours(int pos){
	int r = pos / columns;
	int c = pos % columns;
	return getNeighbours(c, r);
}

Particle** ParticleNet::getNeighbours(int c, int r){

	// every particle has potentially 8 neighbours
	Particle** neighbours = new Particle*[8];

	// upper left
	neighbours[0] = at(c - 1, r - 1);
	// upper
	neighbours[1] = at(c, r - 1);
	// upper right
	neighbours[2] = at(c + 1, r - 1);
	// right
	neighbours[3] = at(c + 1, r);
	// lower right
	neighbours[4] = at(c + 1, r + 1);
	// lower
	neighbours[5] = at(c, r + 1);
	// lower left
	neighbours[6] = at(c - 1, r + 1);
	//left
	neighbours[7] = at(c - 1, r);

	return neighbours;
};

Particle* ParticleNet::at(int c, int r){
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
			pull(at(c, r), z);
		}
};

// pull single particle and its neighbours recursively
void ParticleNet::pull(Particle *particle, float z){
	//end of recursion
	if (z < 0.1 || particle->z >= z)
		return;
	particle->z = z;
	Particle** neighbours = getNeighbours(particle->c, particle->r);
	for (int j = 0; j < 8; j++){
		Particle* neighbour = neighbours[j];
		if (neighbour)
			pull(neighbour, z * 0.8);
	}
}

void ParticleNet::hit(int c, int r, ofVec2f dir){
	Particle *particle = at(c, r);
	if ((particle->pos - particle->startPos).length() <= pxDistance / 2)
		particle->kDir += dir;
	//cout << at(c, r)->kDir.length(); cout << "\n";
};

void ParticleNet::update(){
	vector<Particle *>::iterator it = particles.begin();
	int i = 0;
	while (it != particles.end()){
		Particle** neighbours = getNeighbours((*it)->c, (*it)->r);
		//TODO: real direction
		if ((*it)->kDir.length() != 0){
			for (int j = 0; j < 8; j++){
				if ((j <= 2 && (*it)->kDir.y > 0))
					continue;
				Particle* neighbour = neighbours[j];
				if ((neighbours[j]) && (neighbours[j]->pos - (*it)->pos).length() <= pxDistance){
					neighbours[j]->kDir += (*it)->kDir / 5;
					(*it)->kDir /= 5;
				}
			}
		}
		/*
		if ((*it)->kDir.length() != 0 && (neighbours[5]) && (neighbours[5]->pos - (*it)->pos).length() < pxDistance / 2){
		neighbours[5]->kDir += (*it)->kDir/2;
		(*it)->kDir /= 2;
		}*/
		(*it)->update();
		it++;
		i++;
	}
};
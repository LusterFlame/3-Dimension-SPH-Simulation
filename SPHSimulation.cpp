#include <iostream>
#include <cstdlib>
#include <functional>

// When the makeSPHFile() function is called, will create a file that saves the position of all particles for every frame.

class SystemState{
public:
	int particleNum;
	float particleMass;
	float* density;			// Density for each particle (e.g., rho[0:2] for particle #0's x, y, z)
	float* position; 		// Position for each particle (e.g., position[0:2] for particle #0's x, y, z) [-5,5]x[-5,5]x[-5,5]
	float* vF;				// Velocity (Full Step) (e.g., vF[0:2] for particle #0's x, y, z)
	float* vH;				// Velocity (Half Step) (e.g., vH[0:2] for particle #0's x, y, z)
	float* acceleration; 	// Acceleration (e.g., a[0:2] for particle #0's x, y, z)
};

class Parameters{
public:
	std::string fileName;	// Name for output file
	int frame;				// Total frame to calculate
	int steps;				// Steps each frame, steps * timeStep = 1 time-intergral for a frame
	float radii;			//
	float timeStep;			// delta-t used in Leap-Frog
	float referenceDensity;	// 
	float bulkModules;		//
	float viscosity;		//
	float gravity;			//
};

void setInitial(std::function<int(float, float, float)> initialPosFunc, SystemState* s, Parameters* p, std::string fileName, int particleNum, int frame, int steps, float timeStep, float radii, float referenceDensity, float bulkModules, float viscosity);
void setInitial(std::function<int(float, float, float)> initialPosFunc, SystemState* s, Parameters* p);
void setPosition(std::function<int(float, float, float)> initialPosFunc, SystemState* s, Parameters* p);
void getDensity(SystemState* s, Parameters* p);

void setInitial(std::function<int(float, float, float)> initialPosFunc,
				SystemState* s,
				Parameters* p,
				std::string fileName,
				float particleMass,
				int frame,
				int steps,
				float timeStep, 
				float radii, 
				float referenceDensity, 
				float bulkModules, 
				float viscosity){
	// Set the parameters
	s->particleMass = particleMass;
	p->fileName = fileName;
	p->frame = frame;
	p->steps = steps;
	p->radii = radii;
	p->timeStep = timeStep;
	p->referenceDensity = referenceDensity;
	p->bulkModules = bulkModules;
	p->viscosity = viscosity;
	p->gravity = 9.8f;

	setPosition(initialPosFunc, s, p);
}

void setInitial(std::function<int(float, float, float)> initialPosFunc, SystemState* s, Parameters* p){
	s->particleMass = 1.0f;
	p->fileName = "default.sph";
	p->frame = 400;
	p->steps = 100;
	p->radii = 0.1f;
	p->timeStep = 0.0001f;
	p->referenceDensity = 1000.0f;
	p->bulkModules = 1000.0f;
	p->viscosity = 0.1f;
	p->gravity = 9.8f;

	setPosition(initialPosFunc, s, p);
}

void setPosition(std::function<int(float, float, float)> initialPosFunc, SystemState* s, Parameters* p){
	int count = 0;
	float gap = p->radii * 1.8f;
	std::cout << "\nI am in here\n";
	for(float x = -4.9f;x < 4.9f;x += gap){
		for(float y = -4.9f;y < 4.9f;y += gap){
			for(float z = -4.9f;z < 4.9f;z += gap){
				if(initialPosFunc(x, y, z)){
					std::cout << "not yet u qrick\n" << std::endl;
					s->position[3 * count + 0] = x;  // Initial X position
					s->position[3 * count + 1] = y; // Initial Y position
					s->position[3 * count + 2] = z; // Initial Z position
					++count;
					std::cout << "added one" << std::endl;
				}
			}
		}
	}
	s->particleNum = count;
}


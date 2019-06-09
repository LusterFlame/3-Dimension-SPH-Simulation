#include <iostream>
#include <cstdlib>

/*

	The universe is [-5,5]x[-5,5]x[-5,5].

*/

bool centerBox(float x, float y, float z);
bool centerSphere(float x, float y, float z);

bool centerBox(float x, float y, float z){
	std::cout << "\nx = " << x << ", y = " << y << ", z = " << z << " ///" << ((x >= -1.5f && x <= 1.5f) && (y >= -1.5f && y <= 1.5f) && (z >= -1.5f && z <= 1.5f));
	return ((x >= -1.5f && x <= 1.5f) && (y >= -1.5f && y <= 1.5f) && (z >= -1.5f && z <= 1.5f));
}

bool centerSphere(float x, float y, float z){
	float radius = 1.5f;
	float key = x * x + y * y + z * z;
	return (key < radius * radius * radius);
}
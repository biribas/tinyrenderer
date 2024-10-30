#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include <geometry.hpp>

class Model {
private:
	std::vector<Vec3f> verts_;  						// Stores vertices as a vector of Vec3f objects.
	std::vector<std::vector<int> > faces_;  // Stores faces, each as a vector of vertex indices.

public:
	Model(const char *filename); 		// Constructor: loads a model from a file.
	~Model();                    		// Destructor.

	int nverts();                		// Returns the number of vertices.
	int nfaces();                		// Returns the number of faces.

	Vec3f vert(int idx);           	// Returns the vertex at index idx.
	std::vector<int> face(int i); 	// Returns the face at index idx.
};

#endif // __MODEL_H__

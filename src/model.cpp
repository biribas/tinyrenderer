#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <geometry.hpp>
#include <model.hpp>
#include <gl.hpp>

Model::Model(const char *filename) : verts_(), faces_() {
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail()) return;

  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());

    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      Vec3f v;
      for (int i = 0; i < 3; i++) {
        iss >> v.raw[i];
      }
      verts_.push_back(v);
    } 
    else if (!line.compare(0, 2, "f ")) {
      std::vector<int> f;
      f.reserve(3);

      int itrash, idx;
      iss >> trash;
      while (iss >> idx >> trash >> itrash >> trash >> itrash) {
        idx--; // in wavefront obj all indices start at 1, not zero
        f.push_back(idx);
      }
      
      if (!is_triangle_clockwise(verts_[f[0]], verts_[f[1]], verts_[f[2]])) {
        std::swap(f[1], f[2]);
      }
      
      faces_.push_back(f);
    }
  }
  std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}

Model::~Model() {}

int Model::nverts() { return (int)verts_.size(); }

int Model::nfaces() { return (int)faces_.size(); }

std::vector<int> Model::face(int idx) { return faces_[idx]; }

Vec3f Model::vert(int idx) { return verts_[idx]; }

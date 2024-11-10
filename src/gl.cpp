#include <gl.hpp>

void triangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color) {
  // Finding the bounding box
  int x_min = std::min(std::min(v0.value.x, v1.value.x), v2.value.x);
  int y_min = std::min(std::min(v0.value.y, v1.value.y), v2.value.y);
  int x_max = std::max(std::max(v0.value.x, v1.value.x), v2.value.x);
  int y_max = std::max(std::max(v0.value.y, v1.value.y), v2.value.y);
  
  for (int y = y_min; y <= y_max; y++) {
    for (int x = x_min; x <= x_max; x++) {
      Vec2i p(x, y);
      
      // Barycentric Weights
      int w0 = (v1 - v0) ^ (p - v0);
      int w1 = (v2 - v1) ^ (p - v1);
      int w2 = (v0 - v2) ^ (p - v2);
      
      if (w0 < 0 || w1 < 0 || w2 < 0) continue;
      image.set(x, y, color);
    }
  }
}

void line(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color) {
  bool steep = false;
  if (std::abs(p0.value.x - p1.value.x) < std::abs(p0.value.y - p1.value.y)) {
    std::swap(p0.value.x, p0.value.y);
    std::swap(p1.value.x, p1.value.y);
    steep = true;
  }

  if (p0.value.x > p1.value.x) {
    std::swap(p0.value.x, p1.value.x);
    std::swap(p0.value.y, p1.value.y);
  }

  int dy = p1.value.y - p0.value.y;
  int dx = p1.value.x - p0.value.x;
  int derr = std::abs(dy) * 2;
  int error = 0;
  int y = p0.value.y;

  for (int x = p0.value.x; x <= p1.value.x; x++) {
    if (steep) image.set(y, x, color);
    else image.set(x, y, color);

    error += derr;
    if (error > dx) {
      y += (p1.value.y > p0.value.y ? 1 : -1);
      error -= 2 * dx;
    }
  }
}

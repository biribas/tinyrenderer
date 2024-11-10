#include <geometry.hpp>
#include <gl.hpp>

// Top-left rasterization rule
bool is_top_left(Vec2i edge) {
  bool is_top_edge = edge.value.y == 0 && edge.value.x > 0;
  bool is_left_edge = edge.value.y < 0;
  return is_top_edge || is_left_edge;
}

void triangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color) {
  // Finding the bounding box
  int x_min = std::min(std::min(v0.value.x, v1.value.x), v2.value.x);
  int y_min = std::min(std::min(v0.value.y, v1.value.y), v2.value.y);
  int x_max = std::max(std::max(v0.value.x, v1.value.x), v2.value.x);
  int y_max = std::max(std::max(v0.value.y, v1.value.y), v2.value.y);
  
  int delta_w_col[] = {
    v1.value.y - v2.value.y,
    v2.value.y - v0.value.y,
    v0.value.y - v1.value.y
  };

  int delta_w_row[] = {
    v2.value.x - v1.value.x,
    v0.value.x - v2.value.x,
    v1.value.x - v0.value.x
  };

  // Bias values based on top-left rule
  int bias[3] = {
    is_top_left(v2 - v1) ? 0 : -1,
    is_top_left(v0 - v2) ? 0 : -1,
    is_top_left(v1 - v0) ? 0 : -1
  };
  
  // Initialize starting values for barycentric weights
  Vec2i p0(x_min, y_min);
  int w_row[3] = {
    ((v2 - v1) ^ (p0 - v1)) + bias[0],
    ((v0 - v2) ^ (p0 - v2)) + bias[1],
    ((v1 - v0) ^ (p0 - v0)) + bias[2]
  };
  
  for (int y = y_min; y <= y_max; y++) {
    // Barycentric Weights
    int w[3] = {w_row[0], w_row[1], w_row[2]};

    for (int x = x_min; x <= x_max; x++) {
      if (w[0] >= 0 && w[1] >= 0 && w[2] >= 0) {
        image.set(x, y, color);
      }

      // Update barycentric weights for the next point in the row
      for (int i = 0; i < 3; i++) {
        w[i] += delta_w_col[i];
      }
    }

    // Update barycentric weights for the next row
    for (int i = 0; i < 3; i++) {
      w_row[i] += delta_w_row[i];
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

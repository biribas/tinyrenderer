#include <model.hpp>
#include <tgaimage.hpp>
#include <geometry.hpp>

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);
const int width = 3840;
const int height = 2160;
Model *model = NULL;

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

int main(int argc, char **argv) {
  if (argc == 2) model = new Model(argv[1]);
  else model = new Model("obj/african_head.obj");

  TGAImage image(width, height, TGAImage::RGB);

  for (int i = 0; i < model->nfaces(); i++) { 
    std::vector<int> face = model->face(i); 
    Vec2i screen_coords[3]; 
    for (int j = 0; j < 3; j++) { 
      Vec3f world_coords = model->vert(face[j]); 
      screen_coords[j] = Vec2i((world_coords.value.x + 1.) * width / 2., (world_coords.value.y + 1.) * height / 2.); 
    } 
    triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF, 0xFF)); 
  }

  image.flip_vertically();
  image.write_tga_file("output.tga");
  return 0;
}

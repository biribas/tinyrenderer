#include <model.hpp>
#include <tgaimage.hpp>

#include <utility>

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);
const int width = 200;
const int height = 200;
Model *model = NULL;

void triangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color) {
  if (v0.value.y > v1.value.y) std::swap(v0, v1);
  if (v1.value.y > v2.value.y) std::swap(v1, v2);
  if (v0.value.y > v1.value.y) std::swap(v0, v1);
  
  int first_height = v1.value.y - v0.value.y;
  int second_height = v2.value.y - v1.value.y;
  int total_heigh = first_height + second_height;

  for (int y = v0.value.y; y <= v2.value.y; y++) {
    bool second_half = (y > v1.value.y) || (v1.value.y == v0.value.y);
    int segment_height = second_half ? second_height : first_height;

    float alpha = (float)(y - v0.value.y) / total_heigh;
    float beta = (float)(y - (second_half ? v1.value.y : v0.value.y)) / segment_height;
    
    Vec2i A = v0 + (v2 - v0) * alpha;
    Vec2i B = second_half ? v1 + (v2 - v1) * beta : v0 + (v1 - v0) * beta;
    if (A.value.x > B.value.x) std::swap(A.value.x, B.value.x);
    for (int x = A.value.x; x <= B.value.x; x++) {
      image.set(x, y, color);
    }
  }
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
  bool steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }

  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  int dy = y1 - y0;
  int dx = x1 - x0;
  int derr = std::abs(dy) * 2;
  int error = 0;
  int y = y0;

  for (int x = x0; x <= x1; x++) {
    if (steep) image.set(y, x, color);
    else image.set(x, y, color);

    error += derr;
    if (error > dx) {
      y += (y1 > y0 ? 1 : -1);
      error -= 2 * dx;
    }
  }
}

int main(int argc, char **argv) {
  if (argc == 2) model = new Model(argv[1]);
  else model = new Model("obj/african_head.obj");

  TGAImage image(width, height, TGAImage::RGB);

  Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
  Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
  Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 

  triangle(t0[0], t0[1], t0[2], image, red); 
  triangle(t1[0], t1[1], t1[2], image, blue); 
  triangle(t2[0], t2[1], t2[2], image, white);

  image.flip_vertically();
  image.write_tga_file("output.tga");
  return 0;
}

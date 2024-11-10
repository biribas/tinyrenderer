#include <model.hpp>
#include <tgaimage.hpp>
#include <geometry.hpp>
#include <gl.hpp>

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);
const int width = 3840;
const int height = 2160;
Model *model = NULL;

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

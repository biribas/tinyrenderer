#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <fstream>

struct TGAHeader {
  int8_t idlength;
  int8_t colormaptype;
  int8_t datatypecode;
  int16_t colormaporigin;
  int16_t colormaplength;
  int8_t colormapdepth;
  int16_t x_origin;
  int16_t y_origin;
  int16_t width;
  int16_t height;
  int8_t bitsperpixel;
  int8_t imagedescriptor;
} __attribute__((packed));

struct TGAColor {
  union {
    struct {
      unsigned char r, g, b, a;
    } rgba;
    unsigned char raw[4];
    unsigned int val;
  };
  int bytespp;

  TGAColor() : val(0), bytespp(1) {}

  TGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : rgba{R, G, B, A}, bytespp(4) {}

  TGAColor(int v, int bpp) : val(v), bytespp(bpp) {}

  TGAColor(const TGAColor &c) : val(c.val), bytespp(c.bytespp) {}

  TGAColor(const unsigned char *p, int bpp) : val(0), bytespp(bpp) {
    for (int i = 0; i < bpp; i++) {
      raw[i] = p[i];
    }
  }

  TGAColor &operator=(const TGAColor &c) {
    if (this != &c) {
      bytespp = c.bytespp;
      val = c.val;
    }
    return *this;
  }
};

class TGAImage {
protected:
  unsigned char *data;
  int width;
  int height;
  int bytespp;

  bool load_rle_data(std::ifstream &in);
  bool unload_rle_data(std::ofstream &out);

public:
  enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

  TGAImage();
  TGAImage(int w, int h, int bpp);
  TGAImage(const TGAImage &img);
  bool read_tga_file(const char *filename);
  bool write_tga_file(const char *filename, bool rle = true);
  bool flip_horizontally();
  bool flip_vertically();
  bool scale(int w, int h);
  TGAColor get(int x, int y);
  bool set(int x, int y, TGAColor c);
  ~TGAImage();
  TGAImage &operator=(const TGAImage &img);
  int get_width();
  int get_height();
  int get_bytespp();
  unsigned char *buffer();
  void clear();
};

#endif //__IMAGE_H__
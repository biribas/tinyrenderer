#ifndef __GL_H__
#define __GL_H__

#include <geometry.hpp>
#include <tgaimage.hpp>

void triangle(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color);
void line(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color);

template <class t> bool is_triangle_clockwise(Vec2<t> &v0, Vec2<t> &v1, Vec2<t> &v2) {
  Vec2<t> edge1 = v1 - v0;
  Vec2<t> edge2 = v2 - v0;
  return (edge1 ^ edge2) >= 0;
}

template <class t> bool is_triangle_clockwise(Vec3<t> &v0, Vec3<t> &v1, Vec3<t> &v2) {
  Vec2<t> edge1 = v1 - v0;
  Vec2<t> edge2 = v2 - v0;
  return (edge1 ^ edge2) >= 0;
}

#endif

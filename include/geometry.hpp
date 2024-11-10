#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>
#include <ostream>

template <class t> struct Vec2 {
	union {
		struct { t x, y; } value;
		t raw[2];
	};

  Vec2() : value{0, 0} {}
  Vec2(t _u, t _v) : value{_u, _v} {}
  
  inline t operator^(const Vec2<t> &V) const {
    return value.x * V.value.y - value.y * V.value.x;
  }

  inline Vec2<t> operator+(const Vec2<t> &V) const {
    return Vec2<t>(value.x + V.value.x, value.y + V.value.y);
  }

  inline Vec2<t> operator-(const Vec2<t> &V) const {
    return Vec2<t>(value.x - V.value.x, value.y - V.value.y);
  }

  inline Vec2<t> operator*(float f) const {
    return Vec2<t>(value.x * f, value.y * f);
  }

  template <class> friend std::ostream &operator<<(std::ostream &s, Vec2<t> &v);
};

template <class t> struct Vec3 {
  union {
    struct { t x, y, z; } value;
    struct { t ivert, iuv, inorm; } indices;
    t raw[3];
  };

  Vec3() : value{0, 0, 0} {}
  Vec3(t _x, t _y, t _z) : value{_x, _y, _z} {}
  
  inline Vec3<t> operator^(const Vec3<t> &v) const {
    return Vec3<t>(value.y * v.value.z - value.z * v.value.y,
                   value.z * v.value.x - value.x * v.value.z,
                   value.x * v.value.y - value.y * v.value.x);
  }

  inline Vec3<t> operator+(const Vec3<t> &v) const {
    return Vec3<t>(value.x + v.value.x, value.y + v.value.y, value.z + v.value.z);
  }

  inline Vec3<t> operator-(const Vec3<t> &v) const {
    return Vec3<t>(value.x - v.value.x, value.y - v.value.y, value.z - v.value.z);
  }

  inline Vec3<t> operator*(float f) const {
    return Vec3<t>(value.x * f, value.y * f, value.z * f);
  }

  inline t operator*(const Vec3<t> &v) const {
    return value.x * v.value.x + value.y * v.value.y + value.z * v.value.z;
  }

  float norm() const {
    return std::sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
  }

  Vec3<t> &normalize(t l = 1) {
    *this = (*this) * (l / norm());
    return *this;
  }

  template <class> friend std::ostream &operator<<(std::ostream &s, Vec3<t> &v);
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template <class t> std::ostream &operator<<(std::ostream &s, Vec2<t> &v) {
  s << "(" << v.x << ", " << v.y << ")\n";
  return s;
}

template <class t> std::ostream &operator<<(std::ostream &s, Vec3<t> &v) {
  s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
  return s;
}

#endif //__GEOMETRY_H__
#include "Noise.hh"

#include <cstdlib>

constexpr int Noise::grad3[][3];
Noise::Noise(unsigned int seed) {
  srand(seed);
  unsigned int tableSize = this->permTable.size();

  for (unsigned int i = 0; i < tableSize; ++i) {
    this->permTable[i] = std::rand() & 0xFF;
  }
}

static int fastfloor(float num) { return (int)(num > 0 ? num : (num - 1)); }

static inline float dot2(const int *g, float x, float y) {
  return g[0] * x + g[1] * y;
}

static inline float dot3(const int *g, float x, float y, float z) {
  return g[0] * x + g[1] * y + g[2] * z;
}

float Noise::ridge(float h, float offset) const {
  if (h < 0)
    h = -h;
  h = offset - h;
  return h * h;
}

float Noise::ridgedMf(float x, float y, int octaves, float scale,
                      float lacunarity, float gain, float offset) const {
  return ridge(0.3f + 0.5f * fbm(x, y, octaves, scale, lacunarity, gain),
               offset);
}

float Noise::ridgedMf(float x, float y, float z, int octaves, float scale,
                      float lacunarity, float gain, float offset) const {
  return ridge(0.3f + 0.5f * fbm(x, y, octaves, scale, lacunarity, gain),
               offset);
}

float Noise::fbm(float x, float y, int octaves, float scale, float lacunarity,
                 float gain) const {
  float total = 0.f;
  float amplitude = 1.f;
  float max = 0.f;

  for (int i = 0; i < octaves; ++i) {
    max += amplitude;
    total += raw(x * scale, y * scale) * amplitude;
    scale *= lacunarity;
    amplitude *= gain;
  }
  return total / max;
}

float Noise::fbm(float x, float y, float z, int octaves, float scale,
                 float lacunarity, float gain) const {
  float total = 0.f;
  float amplitude = 1.f;
  float max = 0.f;

  for (int i = 0; i < octaves; ++i) {
    max += amplitude;
    total += raw(x * scale, y * scale, z * scale) * amplitude;
    scale *= lacunarity;
    amplitude *= gain;
  }
  return total / max;
}

float Noise::raw(float x, float y) const {
  float n0, n1, n2;
  float s = (x + y) * F2;
  int i = fastfloor(x + s);
  int j = fastfloor(y + s);

  float t = (i + j) * G2;
  float X0 = i - t;
  float Y0 = j - t;
  float x0 = x - X0;
  float y0 = y - Y0;

  unsigned int i1, j1;
  if (x0 > y0) {
    i1 = 1;
    j1 = 0;
  } else {
    i1 = 0;
    j1 = 1;
  }

  float x1 = x0 - i1 + G2;
  float y1 = y0 - j1 + G2;
  float x2 = x0 - GX2;
  float y2 = y0 - GX2;

  unsigned int ii = i & 255;
  unsigned int jj = j & 255;

  float t0 = 0.5f - x0 * x0 - y0 * y0;
  if (t0 < 0)
    n0 = 0.f;
  else {
    t0 *= t0;
    n0 = t0 * t0 * dot2(grad3[permTable[ii + permTable[jj]] & 0xF], x0, y0);
  }

  float t1 = 0.5f - x1 * x1 - y1 * y1;
  if (t1 < 0)
    n1 = 0.f;
  else {
    t1 *= t1;
    n1 = t1 * t1 *
         dot2(grad3[permTable[ii + i1 + permTable[jj + j1]] & 0xF], x1, y1);
  }

  float t2 = 0.5f - x2 * x2 - y2 * y2;
  if (t2 < 0)
    n2 = 0.f;
  else {
    t2 *= t2;
    n2 = t2 * t2 *
         dot2(grad3[permTable[ii + 1 + permTable[jj + 1]] & 0xF], x2, y2);
  }
  return 70.f * (n0 + n1 + n2);
}

float Noise::raw(float x, float y, float z) const {
  float n0, n1, n2, n3;
  float s = (x + y + z) * F3;
  int i = fastfloor(x + s);
  int j = fastfloor(y + s);
  int k = fastfloor(z + s);

  float t = (i + j + k) * G3;
  float X0 = i - t;
  float Y0 = j - t;
  float Z0 = k - t;
  float x0 = x - X0;
  float y0 = y - Y0;
  float z0 = z - Z0;
  unsigned int i1, j1, k1;
  unsigned int i2, j2, k2;

  if (x0 >= y0) {
    if (y0 >= z0) {
      i1 = i2 = j2 = 1;
      j1 = k1 = k2 = 0;
    } else if (x0 >= z0) {
      i1 = i2 = k2 = 1;
      j1 = k1 = j2 = 0;
    } else {
      k1 = i2 = k2 = 1;
      i1 = j1 = j2 = 0;
    }
  } else {
    if (y0 < z0) {
      k1 = j2 = k2 = 1;
      i1 = j1 = i2 = 0;
    } else if (x0 < z0) {
      j1 = j2 = k2 = 1;
      i1 = k1 = i2 = 0;
    } else {
      j1 = i2 = j2 = 1;
      i1 = k1 = k2 = 0;
    }
  }

  float x1 = x0 - i1 + G3;
  float y1 = y0 - j1 + G3;
  float z1 = z0 - k1 + G3;
  float x2 = x0 - i2 + F3;
  float y2 = y0 - j2 + F3;
  float z2 = z0 - k2 + F3;
  float x3 = x0 - E3;
  float y3 = y0 - E3;
  float z3 = z0 - E3;

  int ii = i & 255;
  int jj = j & 255;
  int kk = k & 255;
  int gi0 = permTable[ii + permTable[jj + permTable[kk]]] & 0xF;
  int gi1 = permTable[ii + i1 + permTable[jj + j1 + permTable[kk + k1]]] & 0xF;
  int gi2 = permTable[ii + i2 + permTable[jj + j2 + permTable[kk + k2]]] & 0xF;
  int gi3 = permTable[ii + 1 + permTable[jj + 1 + permTable[kk + 1]]] & 0xF;

  float t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0;
  if (t0 < 0)
    n0 = 0.f;
  else {
    t0 *= t0;
    n0 = t0 * t0 * dot3(grad3[gi0], x0, y0, z0) * -1;
  }

  float t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1;
  if (t1 < 0)
    n1 = 0.f;
  else {
    t1 *= t1;
    n1 = t1 * t1 * dot3(grad3[gi1], x1, y1, z1) * -1;
  }

  float t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
  if (t2 < 0)
    n2 = 0.f;
  else {
    t2 *= t2;
    n2 = t2 * t2 * dot3(grad3[gi2], x2, y2, z2) * -1;
  }

  float t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
  if (t3 < 0)
    n3 = 0.f;
  else {
    t3 *= t3;
    n3 = t3 * t3 * dot3(grad3[gi3], x3, y3, z3) * -1;
  }
  return 32.f * (n0 + n1 + n2 + n3);
}
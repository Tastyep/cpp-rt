#ifndef NOISE_HH_
#define NOISE_HH_

#include <array>
#include <ctime>

class Noise {
public:
  Noise(unsigned int seed = std::time(0));

  ~Noise() = default;
  Noise(const Noise &other) = default;
  Noise(Noise &&other) = default;
  Noise &operator=(const Noise &other) = default;
  Noise &operator=(Noise &&other) = default;

  float raw(float x, float y) const;
  float raw(float x, float y, float z) const;
  float fbm(float x, float y, int octaves = 2, float scale = 1,
            float lacunarity = 1, float gain = 0.5) const;
  float fbm(float x, float y, float z, int octaves = 2, float scale = 1,
            float lacunarity = 1, float gain = 0.5) const;
  float ridgedMf(float x, float y, int octaves = 2, float scale = 1,
                 float lacunarity = 1, float gain = 0.5,
                 float offset = 1) const;
  float ridgedMf(float x, float y, float z, int octaves = 2, float scale = 1,
                 float lacunarity = 1, float gain = 0.5,
                 float offset = 1) const;

private:
  float ridge(float h, float offset) const;

private:
  static constexpr float F2 = 0.366025403f;  // F2 = 0.5*(sqrt(3.0)-1.0)
  static constexpr float G2 = 0.211324865f;  // G2 = (3.0-Math.sqrt(3.0))/6.0
  static constexpr float GX2 = 0.577350269f; // |2.f * G2 - 1.0|

  static constexpr float F3 = 0.333333333f;
  static constexpr float G3 = 0.166666667f;
  static constexpr float E3 = 0.5f; // 1.f + 3.f * G3

  static constexpr int grad3[16][3] = {
      {1, 0, 1},   {0, 1, 1}, // 12 cube edges
      {-1, 0, 1},  {0, -1, 1},  {1, 0, -1}, {0, 1, -1},
      {-1, 0, -1}, {0, -1, -1}, {1, -1, 0}, {1, 1, 0},
      {-1, 1, 0},  {-1, -1, 0}, {1, 0, 1},  {-1, 0, 1}, // 4 repeats to make 16
      {0, 1, -1},  {0, -1, -1}};

private:
  std::array<int, 512> permTable;
};

#endif /* end of include guard: NOISE_HH_ */

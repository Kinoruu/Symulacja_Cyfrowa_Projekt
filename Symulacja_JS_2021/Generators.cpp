#include "Generators.h"
#include <cmath>
#include "Network.h"

Generators::Generators(int kernel) : kernel_(kernel) { }

Generators::~Generators() { }

double Generators::Rand()
{
  int h = kernel_ / kQ;
  kernel_ = kA * (kernel_ - kQ * h) - kR * h;
  if (kernel_ < 0)
    kernel_ = kernel_ + static_cast<int>(kM);
  return kernel_ / kM;
}

int Generators::Rand(int min, int max)
{
  return Rand() * (max - min) + min;
}
int Generators::RandExp(double lambda)
{
  auto k = Rand();
  return -(1.0 / lambda) * log(k);
}
int Generators::RandZeroOne(double probability)
{
  auto k = Rand();
  if (k < probability) return 1;
  else return 0;
}
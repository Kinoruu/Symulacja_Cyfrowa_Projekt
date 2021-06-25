#ifndef GENERATORS_H_
#define GENERATORS_H_

#include <string>
#include <cmath>
#include <vector>

class Generators
{
public:
  Generators(int kernel);
  ~Generators();

  // Draws number between <0,1>
  double Rand();
  //Rozk³ad jednostajny na zdefiniowanym przedziale <min,max>
  int Rand(int min, int max);
  //Rozk³ad wyk³adniczy
  int RandExp(double lambda);
  //Rozk³ad Bernoulliego 0-1
  int RandZeroOne(double probability);

  int get_kernel() { return kernel_; };
private:
  int kernel_;
  const double kM = 2147483647.0;
  static const int kA = 16807;
  static const int kQ = 127773;
  static const int kR = 2836;
};


#endif /* GENERATORS_H_ */
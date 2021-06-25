//#pragma once
#ifndef RESOURCEBLOCK_H
#define RESOURCEBLOCK_H
#include <vector>

using namespace std;

// klasa, kt�rej obiekty to pojedyncze bloki zasob�w
class ResourceBlock 
{
public:
  ResourceBlock(size_t RB_id, size_t u_id, bool e, size_t rk);
private:
  size_t RB_id_; // numer id bloku
  size_t user_id_; // numer id aktualnego w�a�ciela bloku
  bool error_; // aktualna informacja o wyst�pieniu b��du w danym bloku
  size_t bit_rate_; // aktualna przep�ywno�� danego bloku
};
#endif
//#pragma once
#ifndef RESOURCEBLOCK_H
#define RESOURCEBLOCK_H
#include <vector>

using namespace std;

// klasa, której obiekty to pojedyncze bloki zasobów
class ResourceBlock 
{
public:
  ResourceBlock(size_t RB_id, size_t u_id, bool e, size_t rk);
private:
  size_t RB_id_; // numer id bloku
  size_t user_id_; // numer id aktualnego w³aœciela bloku
  bool error_; // aktualna informacja o wyst¹pieniu b³êdu w danym bloku
  size_t bit_rate_; // aktualna przep³ywnoœæ danego bloku
};
#endif
#pragma once
#include <string>

struct Product {
  int id{0};
  std::string title;
  double price{0.0};
  std::string category;
  std::string img;
  std::string desc;
  int stock{0};
};

#pragma once
#include "Product.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Minimal persistence: write products to a simple JSON-like file and read back.
inline void save_products(const std::string &path, const std::vector<Product>& products){
  std::ofstream f(path);
  if(!f) return;
  f << "[";
  for(size_t i=0;i<products.size();++i){ const auto &p = products[i]; if(i) f << ",\n";
    f << "{\"id\":"<<p.id<<",\"title\":\""<<p.title<<"\",\"price\":"<<p.price<<",\"category\":\""<<p.category<<"\",\"img\":\""<<p.img<<"\",\"desc\":\""<<p.desc<<"\",\"stock\":"<<p.stock<<"}";
  }
  f << "]";
}

// very small parser; only intended for demo data written by save_products
inline std::vector<Product> load_products(const std::string &path){
  std::vector<Product> out;
  std::ifstream f(path);
  if(!f) return out;
  std::stringstream ss; ss << f.rdbuf(); std::string s = ss.str();
  // naive parse: find { ... } blocks
  size_t pos=0;
  while(true){ pos = s.find('{', pos); if(pos==std::string::npos) break; size_t end = s.find('}', pos); if(end==std::string::npos) break; std::string blk = s.substr(pos+1, end-pos-1); pos = end+1;
    Product p; std::stringstream b(blk); std::string token;
    while(std::getline(b, token, ',')){
      auto colon = token.find(':'); if(colon==std::string::npos) continue; std::string key = token.substr(0,colon); std::string val = token.substr(colon+1);
      // trim
      auto trim = [](std::string &str){ while(!str.empty() && isspace((unsigned char)str.front())) str.erase(0,1); while(!str.empty() && isspace((unsigned char)str.back())) str.pop_back(); if(!str.empty() && str.front()=='\"') str.erase(0,1); if(!str.empty() && str.back()=='\"') str.pop_back(); };
      trim(key); trim(val);
      if(key.find("id")!=std::string::npos) p.id = atoi(val.c_str());
      else if(key.find("title")!=std::string::npos) p.title = val;
      else if(key.find("price")!=std::string::npos) p.price = atof(val.c_str());
      else if(key.find("category")!=std::string::npos) p.category = val;
      else if(key.find("img")!=std::string::npos) p.img = val;
      else if(key.find("desc")!=std::string::npos) p.desc = val;
      else if(key.find("stock")!=std::string::npos) p.stock = atoi(val.c_str());
    }
    out.push_back(p);
  }
  return out;
}

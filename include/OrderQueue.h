#pragma once
#include <vector>
#include <algorithm>

class OrderQueue {
  std::vector<int> q;
public:
  int nextId{1};
  int enqueue(){ int id = nextId++; q.push_back(id); return id; }
  bool remove(int id){ auto it = std::find(q.begin(), q.end(), id); if(it==q.end()) return false; q.erase(it); return true; }
  int size() const { return (int)q.size(); }
  std::vector<int> list() const { return q; }
};

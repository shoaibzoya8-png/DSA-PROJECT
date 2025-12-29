#pragma once
#include "Product.h"
#include <vector>
#include <algorithm>

// Simple singly linked list inventory
class Inventory {
  struct Node { Product p; Node* next{nullptr}; Node(const Product& pr):p(pr){} };
  Node* head{nullptr};
public:
  ~Inventory(){ clear(); }
  void add(const Product& p){ Node* n = new Node(p); n->next = head; head = n; }
  void clear(){ while(head){ Node* t=head; head=head->next; delete t; } }
  std::vector<Product> listAll() const { std::vector<Product> out; for(Node* cur=head; cur; cur=cur->next) out.push_back(cur->p); std::reverse(out.begin(), out.end()); return out; }
  Product* findById(int id) const { for(Node* cur=head; cur; cur=cur->next) if(cur->p.id==id) return &cur->p; return nullptr; }
  std::vector<Product> lowStock(int threshold) const { std::vector<Product> out; for(Node* cur=head; cur; cur=cur->next) if(cur->p.stock<=threshold) out.push_back(cur->p); std::reverse(out.begin(), out.end()); return out; }
};

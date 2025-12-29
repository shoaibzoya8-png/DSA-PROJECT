#pragma once
#include <vector>
#include <string>

// Simple stack of actions for undo
class ActionHistory {
  std::vector<std::string> st;
public:
  void push(const std::string &a){ st.push_back(a); }
  bool empty() const { return st.empty(); }
  std::string pop(){ if(st.empty()) return {}; std::string s = st.back(); st.pop_back(); return s; }
  std::string top() const { return st.empty()?std::string():st.back(); }
};

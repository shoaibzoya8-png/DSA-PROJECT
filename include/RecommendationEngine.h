#pragma once
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

// Simple graph-based recommendation engine: adjacency list of product -> related products
class RecommendationEngine {
  std::unordered_map<int, std::vector<int>> adj;
public:
  void addEdge(int a,int b){ adj[a].push_back(b); }
  std::vector<int> suggest(int start, int maxResults=6){
    std::vector<int> out; std::unordered_map<int,bool> seen; std::queue<int> q; q.push(start); seen[start]=true;
    while(!q.empty() && (int)out.size()<maxResults){ int u=q.front(); q.pop(); for(int v: adj[u]) if(!seen[v]){ seen[v]=true; out.push_back(v); q.push(v); if((int)out.size()>=maxResults) break; } }
    return out;
  }
};

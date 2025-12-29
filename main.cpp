// Minimal C++ backend demonstrating core data structures (LinkedList, Stack, Queue)
// Uses single-header httplib (provided in workspace) to serve HTTP JSON endpoints.
// Build (with g++):
//   g++ -std=c++17 -O2 main.cpp -o backend.exe
// Run: ./backend.exe

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <mutex>
#include "..\httplib.h"

using namespace std;
using namespace httplib;

struct Product {
  int id;
  string title;
  double price;
  string category;
  string img;
  string desc;
  int stock;
};

// Simple singly-linked list for inventory
class InventoryList {
  struct Node { Product p; Node* next; Node(const Product& pr):p(pr),next(nullptr){} };
  Node* head = nullptr;
public:
  InventoryList(){}
  ~InventoryList(){ clear(); }
  void clear(){ while(head){ Node* t=head; head=head->next; delete t; } }
  void add(const Product& p){
    Node* n = new Node(p);
    n->next = head; head = n;
  }
  vector<Product> listAll(){
    vector<Product> out; for(Node* cur=head; cur; cur=cur->next) out.push_back(cur->p);
    // return in stable order (reverse linked insertion)
    reverse(out.begin(), out.end());
    return out;
  }
  Product* findById(int id){ for(Node* cur=head; cur; cur=cur->next) if(cur->p.id==id) return &cur->p; return nullptr; }
  vector<Product> lowStock(int threshold){ vector<Product> out; for(Node* cur=head; cur; cur=cur->next) if(cur->p.stock<=threshold) out.push_back(cur->p); reverse(out.begin(), out.end()); return out; }
};

// Simple stack for action history (undo)
class ActionStack {
  vector<string> items;
public:
  void push(const string& s){ items.push_back(s); }
  bool empty() const { return items.empty(); }
  string pop(){ if(items.empty()) return string(); string s = items.back(); items.pop_back(); return s; }
  string top() const { return items.empty()?string():items.back(); }
};

// Simple queue for orders
class OrderQueue {
  vector<int> q; // store order ids
public:
  int nextId = 1;
  int enqueue(){ int id = nextId++; q.push_back(id); return id; }
  bool remove(int id){ auto it = find(q.begin(), q.end(), id); if(it==q.end()) return false; q.erase(it); return true; }
  int size() const { return (int)q.size(); }
  vector<int> list() const { return q; }
};

// Global instances
static InventoryList inventory;
static ActionStack actions;
static OrderQueue orders;
static mutex g_lock;

string to_json(const Product& p){
  ostringstream o;
  o << "{";
  o << "\"id\":" << p.id << ",";
  o << "\"title\":\"" << p.title << "\",";
  o << "\"price\":" << p.price << ",";
  o << "\"category\":\"" << p.category << "\",";
  o << "\"img\":\"" << p.img << "\",";
  o << "\"desc\":\"" << p.desc << "\",";
  o << "\"stock\":" << p.stock;
  o << "}";
  return o.str();
}

string products_json(const vector<Product>& list){
  ostringstream o; o << "[";
  for(size_t i=0;i<list.size();++i){ if(i) o << ","; o << to_json(list[i]); }
  o << "]"; return o.str();
}

// populate inventory with demo products (same as frontend demo)
void seed_products(){
  vector<Product> demo = {
    {1,"Stainless Steel Blender",44.99,"Kitchen Appliances","","High-speed blender",12},
    {2,"Digital Coffee Maker",35.99,"Kitchen Appliances","https://images.unsplash.com/photo-1517668808822-9ebb02ae2a0e?w=600&h=600&fit=crop","Programmable coffee maker",8},
    {3,"Microwave Oven",71.99,"Kitchen Appliances","https://images.unsplash.com/photo-1584622181563-430f63602d4b?w=600&h=600&fit=crop","25L capacity microwave",5},
    {4,"Electric Kettle",22.49,"Kitchen Appliances","https://images.unsplash.com/photo-1578500494198-246f612d03b3?w=600&h=600&fit=crop","Fast boil kettle",20},
    {5,"Modern Sofa Set",269.99,"Furniture","https://images.unsplash.com/photo-1555041469-a586c61ea9bc?w=600&h=600&fit=crop","3-seater leather sofa",3},
    {6,"Office Chair",116.99,"Furniture","https://images.unsplash.com/photo-1527864550417-7fd91fc51a46?w=600&h=600&fit=crop","Ergonomic office chair",15},
    {7,"Dining Table",161.99,"Furniture","https://images.unsplash.com/photo-1552321554-5fefe8c9ef14?w=600&h=600&fit=crop","Wooden dining table",7},
    {8,"Bookshelf Unit",80.99,"Furniture","https://images.unsplash.com/photo-1595428774223-ef52624120d2?w=600&h=600&fit=crop","5-tier bookshelf",9},
    {9,"Wireless Headphones",53.99,"Electronics","https://images.unsplash.com/photo-1505740420928-5e560c06d30e?w=600&h=600&fit=crop","Noise-canceling headphones",6},
    {10,"Smart LED Bulb",13.49,"Electronics","https://images.unsplash.com/photo-1561070791-2526d30994b5?w=600&h=600&fit=crop","WiFi smart bulb",30},
    {11,"Power Bank",31.49,"Electronics","https://images.unsplash.com/photo-1609042231477-d625b3f4f5d5?w=600&h=600&fit=crop","20000mAh portable charger",25},
    {12,"Portable Speaker",40.49,"Electronics","https://images.unsplash.com/photo-1589003077984-894fdbb6e075?w=600&h=600&fit=crop","Waterproof Bluetooth speaker",11},
    {13,"Wall Clock",17.99,"Home Decor","https://images.unsplash.com/photo-1554794821-ddf9857df51d?w=600&h=600&fit=crop","Modern wall clock",14},
    {14,"Floor Lamp",49.49,"Home Decor","https://images.unsplash.com/photo-1565636192335-14c46fa1120d?w=600&h=600&fit=crop","Adjustable floor lamp",4},
    {15,"Door Mat",11.69,"Home Decor","https://images.unsplash.com/photo-1609042231577-4ee2722f97d3?w=600&h=600&fit=crop","Non-slip doormat",18},
    {16,"Pillow Set",26.99,"Home Decor","https://images.unsplash.com/photo-1546487697-1b4e3bbf8b55?w=600&h=600&fit=crop","Set of 2 memory foam pillows",22},
    {17,"Formal Dress Shirt",31.49,"Fashion","https://images.unsplash.com/photo-1602810318383-fd674f17d0e8?w=600&h=600&fit=crop","Premium cotton shirt",16},
    {18,"Designer Jeans",58.49,"Fashion","https://images.unsplash.com/photo-1542272604-787c62d465d1?w=600&h=600&fit=crop","Slim-fit denim jeans",10},
    {19,"Casual T-Shirt",13.49,"Fashion","https://images.unsplash.com/photo-1521572163474-6864f9cf17ab?w=600&h=600&fit=crop","100% cotton t-shirt",28},
    {20,"Winter Jacket",80.99,"Fashion","https://images.unsplash.com/photo-1611312503408-112ab76e7dbf?w=600&h=600&fit=crop","Warm winter jacket",6},
    {21,"Running Sneakers",74.99,"Shoes","https://images.unsplash.com/photo-1542291026-7eec264c27ff?w=600&h=600&fit=crop","Running shoes with cushioning",12},
    {22,"Casual Loafers",54.99,"Shoes","https://images.unsplash.com/photo-1594938298603-c8148c4dae35?w=600&h=600&fit=crop","Comfortable loafers",9},
    {23,"Sports Shoes",69.99,"Shoes","https://images.unsplash.com/photo-1460353581641-37baddab0fa2?w=600&h=600&fit=crop","High-performance sports shoes",7},
    {24,"Formal Shoes",79.99,"Shoes","https://images.unsplash.com/photo-1548293467-a7edc119b908?w=600&h=600&fit=crop","Classic formal shoes",5},
    {25,"Leather Belt",22.49,"Accessories","https://images.unsplash.com/photo-1542332213-5a8539f2a8c0?w=600&h=600&fit=crop","Genuine leather belt",26},
    {26,"Analog Watch",89.99,"Accessories","https://images.unsplash.com/photo-1523170335258-f5ed11844a49?w=600&h=600&fit=crop","Classic analog watch",8},
    {27,"Sunglasses",40.49,"Accessories","https://images.unsplash.com/photo-1516117172878-fd2c41f4a759?w=600&h=600&fit=crop","UV protection sunglasses",20},
    {28,"Handbag",76.49,"Accessories","https://images.unsplash.com/photo-1548036328-c9fa89d128fa?w=600&h=600&fit=crop","Designer handbag",13},
    {29,"Vacuum Cleaner",134.99,"Home Appliances","https://images.unsplash.com/photo-1587413313803-9d2d00c0b76b?w=600&h=600&fit=crop","Cordless vacuum cleaner",4},
    {30,"Washing Machine",359.99,"Home Appliances","https://images.unsplash.com/photo-1581574205388-6b2131f8c5cf?w=600&h=600&fit=crop","Front-load washing machine",2}
  };
  for(const auto &p: demo) inventory.add(p);
}

string escape_js(const string &s){
  string out; out.reserve(s.size()*1.2);
  for(char c: s){
    if(c=='\\') out += "\\\\";
    else if(c=='\"') out += "\\\"";
    else if(c=='\n') out += "\\n";
    else out += c;
  }
  return out;
}

int main(){
  seed_products();
  Server svr;

  svr.Get("/status", [&](const Request&, Response& res){
    res.set_content("{\"status\":\"ok\"}", "application/json");
  });

  svr.Get(R"(/products)", [&](const Request&, Response& res){
    lock_guard<mutex> L(g_lock);
    auto list = inventory.listAll();
    string body = "{\"products\":" + products_json(list) + "}";
    res.set_content(body, "application/json");
  });

  svr.Get(R"(/search)", [&](const Request& req, Response& res){
    string q = "";
    if(req.has_param("q")) q = req.get_param_value("q");
    transform(q.begin(), q.end(), q.begin(), ::tolower);
    lock_guard<mutex> L(g_lock);
    vector<Product> matches;
    for(auto &p: inventory.listAll()){
      string t = p.title + " " + p.category + " " + p.desc;
      string tl = t; transform(tl.begin(), tl.end(), tl.begin(), ::tolower);
      if(q.empty() || tl.find(q) != string::npos) matches.push_back(p);
    }
    string body = "{\"products\":" + products_json(matches) + "}";
    res.set_content(body, "application/json");
  });

  svr.Get(R"(/low_stock)", [&](const Request&, Response& res){
    lock_guard<mutex> L(g_lock);
    auto list = inventory.lowStock(5);
    string body = "{\"low_stock\":" + products_json(list) + "}";
    res.set_content(body, "application/json");
  });

  // POST /order {"product_id": 3, "qty": 2}
  svr.Post(R"(/order)", [&](const Request& req, Response& res){
    lock_guard<mutex> L(g_lock);
    // naive json parsing (no dependency)
    string b = req.body;
    int pid = 0, qty = 1;
    try{
      auto pos = b.find("\"product_id\"");
      if(pos!=string::npos){ pos = b.find_first_of("0123456789", pos); if(pos!=string::npos) pid = stoi(b.substr(pos)); }
      pos = b.find("\"qty\"");
      if(pos!=string::npos){ pos = b.find_first_of("0123456789", pos); if(pos!=string::npos) qty = stoi(b.substr(pos)); }
    }catch(...){ }
    if(pid<=0){ res.status = 400; res.set_content("{\"error\":\"invalid product_id\"}", "application/json"); return; }
    Product* p = inventory.findById(pid);
    if(!p){ res.status = 404; res.set_content("{\"error\":\"product not found\"}", "application/json"); return; }
    if(p->stock < qty){ res.status = 409; res.set_content("{\"error\":\"insufficient stock\"}", "application/json"); return; }
    // decrement stock
    p->stock -= qty;
    int orderId = orders.enqueue();
    // push action for undo (format: order:orderId:productId:qty)
    actions.push("order:" + to_string(orderId) + ":" + to_string(pid) + ":" + to_string(qty));
    ostringstream out; out << "{\"order_id\":" << orderId << ",\"status\":\"placed\"}";
    res.set_content(out.str(), "application/json");
  });

  // POST /undo -> undo last action if possible
  svr.Post(R"(/undo)", [&](const Request&, Response& res){
    lock_guard<mutex> L(g_lock);
    if(actions.empty()){ res.set_content("{\"ok\":false,\"reason\":\"no actions\"}", "application/json"); return; }
    string act = actions.pop();
    // only support undoing orders for now
    if(act.rfind("order:",0)==0){
      // parse order:id:pid:qty
      vector<string> parts; string cur; for(char c:act){ if(c==':'){ parts.push_back(cur); cur.clear(); } else cur.push_back(c); } parts.push_back(cur);
      if(parts.size()==4){ int orderId = stoi(parts[1]); int pid = stoi(parts[2]); int qty = stoi(parts[3]);
        Product* p = inventory.findById(pid);
        if(p) p->stock += qty; // restore stock
        orders.remove(orderId);
        ostringstream out; out << "{\"ok\":true,\"undone\":\"order\",\"order_id\":" << orderId << "}";
        res.set_content(out.str(), "application/json"); return;
      }
    }
    res.set_content("{\"ok\":false,\"reason\":\"unknown action\"}", "application/json");
  });
svr.set_default_headers({
    {"Access-Control-Allow-Origin", "*"},
    {"Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS"},
    {"Access-Control-Allow-Headers", "Content-Type, Authorization"}
});

// Options handler for pre-flight requests
svr.Options(R"(.*)", [](const Request&, Response& res) {
    res.status = 200;
});
  cout << "Starting backend on http://localhost:18080\n";
  svr.listen("0.0.0.0", 18080);
  return 0;
}

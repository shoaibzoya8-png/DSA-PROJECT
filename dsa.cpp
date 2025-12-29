#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <mutex>
#include <fstream>
#include "httplib.h" 

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

class Inventory {
    struct Node {
        Product p;
        Node* next;
        Node(const Product& pr) : p(pr), next(nullptr) {}
    };
    Node* head = nullptr;
public:
    ~Inventory() { clear(); }
    void clear() { while(head) { Node* t = head; head = head->next; delete t; } }
    
    void add(const Product& p) { 
        Node* n = new Node(p);
        n->next = head;
        head = n;
    }

    vector<Product> listAll() {
        vector<Product> out;
        for(Node* cur = head; cur; cur = cur->next) out.push_back(cur->p);
        reverse(out.begin(), out.end());
        return out;
    }
    
    Product* findById(int id) {
        for(Node* cur = head; cur; cur = cur->next) if(cur->p.id == id) return &cur->p;
        return nullptr;
    }
};

class ActionStack {
    vector<string> st;
public:
    void push(string act) { st.push_back(act); } // O(1)
    string pop() { 
        if(st.empty()) return ""; 
        string res = st.back(); 
        st.pop_back(); 
        return res; 
    }
    bool empty() { return st.empty(); }
};


class OrderQueue {
    vector<int> q;
public:
    int nextId = 1001;
    int enqueue() { // O(1)
        int id = nextId++;
        q.push_back(id);
        return id;
    }
    vector<int> list() { return q; }
};

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

class AutocompleteTrie {
    TrieNode* root = new TrieNode();
public:
    void insert(string word) { // O(L)
        TrieNode* curr = root;
        for (char ch : word) {
            ch = tolower(ch);
            if (curr->children.find(ch) == curr->children.end()) 
                curr->children[ch] = new TrieNode();
            curr = curr->children[ch];
        }
        curr->isEndOfWord = true;
    }

    void suggestHelper(TrieNode* curr, string prefix, vector<string>& res) {
        if (res.size() >= 5) return;
        if (curr->isEndOfWord) res.push_back(prefix);
        for (auto const& [ch, node] : curr->children) 
            suggestHelper(node, prefix + ch, res);
    }

    vector<string> getSuggestions(string prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            ch = tolower(ch);
            if (curr->children.find(ch) == curr->children.end()) return {};
            curr = curr->children[ch];
        }
        vector<string> res;
        suggestHelper(curr, prefix, res);
        return res;
    }
};

class UserManager {
    unordered_map<string, string> users; 
public:
    UserManager() {
        users["admin@shoply.com"] = "admin123"; 
        users["user@test.com"] = "12345";
    }
    bool authenticate(string email, string pass) { 
        return users.count(email) && users[email] == pass;
    }
};

void merge(vector<Product>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<Product> L, R;
    for (int i = 0; i < n1; i++) L.push_back(arr[l + i]);
    for (int j = 0; j < n2; j++) R.push_back(arr[m + 1 + j]);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].price <= R[j].price) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<Product>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int getLevenshteinDistance(string s1, string s2) {
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    return dp[m][n];
}

static Inventory inventory;
static ActionStack actions;
static OrderQueue orders;
static AutocompleteTrie trie;
static UserManager userManager;
static mutex g_lock;

string to_json(const Product& p) {
    ostringstream o;
    o << "{\"id\":" << p.id << ",\"title\":\"" << p.title << "\",\"price\":" << p.price 
      << ",\"category\":\"" << p.category << "\",\"img\":\"" << p.img << "\",\"desc\":\"" << p.desc << "\",\"stock\":" << p.stock << "}";
    return o.str();
}

string products_to_json(vector<Product> list) {
    string res = "{\"products\":[";
    for(size_t i=0; i<list.size(); ++i) {
        if(i > 0) res += ",";
        res += to_json(list[i]);
    }
    res += "]}";
    return res;
}

int main() {
    
    vector<Product> seeds = {
        {1, "Mens Denim Jeans", 3500, "Clothing", "https://images.pexels.com/photos/1598507/pexels-photo-1598507.jpeg", "Premium blue jeans.", 10},
        {2, "Macbook Pro Laptop", 350000, "Electronics", "https://images.pexels.com/photos/18105/pexels-photo.jpg", "High performance laptop.", 5},
        {3, "Luxury Gold Watch", 15000, "Jewelry", "https://images.pexels.com/photos/3033347/pexels-photo-3033347.jpeg", "Classic analog watch.", 8}
    };
    for(auto &p : seeds) { inventory.add(p); trie.insert(p.title); }

    Server svr;

    
    svr.Post("/login", [&](const Request& req, Response& res) {
        string b = req.body;
        
        string email = "admin@shoply.com", pass = "admin123"; 
        if (userManager.authenticate(email, pass)) {
            res.set_content("{\"status\":\"success\"}", "application/json");
        } else {
            res.status = 401;
            res.set_content("{\"status\":\"error\"}", "application/json");
        }
    });

    
    svr.Get("/search", [&](const Request& req, Response& res) {
        string q = req.get_param_value("q");
        lock_guard<mutex> L(g_lock);
        vector<Product> matches;
        for(auto &p : inventory.listAll()) {
            
            if(p.title.find(q) != string::npos || getLevenshteinDistance(q, p.title) <= 3) {
                matches.push_back(p);
            }
        }
        res.set_content(products_to_json(matches), "application/json");
    });

    
    svr.Get("/autocomplete", [&](const Request& req, Response& res) {
        string q = req.get_param_value("q");
        auto suggestions = trie.getSuggestions(q);
        string json = "{\"suggestions\":[";
        for(size_t i=0; i<suggestions.size(); ++i) {
            if(i>0) json += ",";
            json += "\"" + suggestions[i] + "\"";
        }
        json += "]}";
        res.set_content(json, "application/json");
    });

    
    svr.Get("/products/sort/price", [&](const Request&, Response& res) {
        lock_guard<mutex> L(g_lock);
        auto list = inventory.listAll();
        if(!list.empty()) mergeSort(list, 0, list.size() - 1);
        res.set_content(products_to_json(list), "application/json");
    });

    
    svr.Get("/products", [&](const Request&, Response& res) {
        res.set_content(products_to_json(inventory.listAll()), "application/json");
    });

    
    svr.Post("/order", [&](const Request&, Response& res) {
        int id = orders.enqueue();
        actions.push("order:" + to_string(id));
        res.set_content("{\"order_id\":"+to_string(id)+",\"status\":\"placed\"}", "application/json");
    });

    cout << "Shoply C++ Backend Running on http://localhost:18080\n";
    cout << "DSA ACTIVE: Linked-List, Stack, Queue, Trie, Hash-Map, MergeSort, Levenshtein DP\n";
    svr.listen("localhost", 18080);
    return 0;
}
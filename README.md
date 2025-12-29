# 🛒 Shoply - DSA Driven E-commerce System

**Shoply** is a high-performance e-commerce platform built to demonstrate the practical applications of **Data Structures and Algorithms (DSA)** in a real-world web environment. It features a robust C++ backend and a modern, minimalist frontend inspired by global luxury brands.

---

## 🚀 Key Features

- **Smart Search:** Handles spelling mistakes using Fuzzy Search logic.
- **Instant Suggestions:** Lightning-fast autocomplete as you type.
- **Dynamic Inventory:** Efficient management of product stocks.
- **Order Processing:** Sequential order handling using priority queues.
- **Secure Authentication:** Fast login verification.
- **Clean UI:** Professional, responsive, and minimalist design.

---

## 🧠 Data Structures & Algorithms (The Core)

This project is built around fundamental computer science concepts:

### 1. Singly Linked List (Inventory Management)
- **Use Case:** Storing and managing the product catalog.
- **Why:** Allows dynamic memory allocation for adding products without pre-defining array sizes.
- **Complexity:** $O(1)$ for insertion.

### 2. Trie - Prefix Tree (Autocomplete Suggestions)
- **Use Case:** Powering the search bar suggestions.
- **Why:** Provides $O(L)$ search time (where L is word length), making it significantly faster than searching through a full list.

### 3. Stack (Action History / Undo)
- **Use Case:** Tracking user actions to allow "Undo" functionality.
- **Why:** Implements **LIFO (Last-In-First-Out)** to reverse the most recent action first.

### 4. Queue (Order Management)
- **Use Case:** Processing incoming customer orders.
- **Why:** Implements **FIFO (First-In-First-Out)** to ensure orders are handled in the sequence they were received.

### 5. Hash Table / Unordered Map (Authentication)
- **Use Case:** User login and password verification.
- **Why:** Provides near-instant $O(1)$ lookup time for verifying credentials.

### 6. Merge Sort (Price Indexing)
- **Use Case:** Sorting products by price (Low to High).
- **Why:** A stable $O(n \log n)$ algorithm that is highly efficient for sorting large datasets.

### 7. Levenshtein Distance - Dynamic Programming (Fuzzy Search)
- **Use Case:** Search error correction (e.g., matching "Macbok" to "Macbook").
- **Why:** Uses a DP table to calculate the minimum edits between strings for smart matching.

---

## 🛠️ Technology Stack

- **Backend:** C++ (using `httplib` for REST API)
- **Frontend:** HTML5, CSS3 (Modern Flexbox/Grid), JavaScript (ES6+)
- **Database:** JSON Persistence / Memory-based DSA Structures
- **Protocol:** HTTP/REST

---

## ⚙️ Setup Instructions

### 1. Run the Backend
- Open the backend folder in your C++ IDE (like VS Code or Dev-C++).
- Ensure `httplib.h` is in the same directory.
- Compile and Run `main.cpp`.
- The server will start at `http://localhost:18080`.

### 2. Open the Frontend
- Open `index.html` in any modern web browser (Chrome, Edge, Firefox).
- Ensure your internet is connected to load product images from Pexels/Unsplash.

---

## 📂 Project Structure

```text
ecom_project/
├── backend/
│   ├── main.cpp          # Main Server & DSA Logic
│   ├── httplib.h         # HTTP Library
│   └── data/             # Persistent JSON storage
├── frontend/
│   ├── index.html        # Main Layout
│   ├── styles.css        # Professional Styling
│   └── app.js            # Frontend Logic & API Mapping
└── README.md             # Project Documentation
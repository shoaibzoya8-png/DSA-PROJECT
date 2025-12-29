const API_BASE = 'http://localhost:18080';
let USD_TO_PKR = 280;
const USD_RATE = 280; // 1 USD = 280 PKR

const state = {
    products: [
        { id: 1, title: "Mens Denim Jeans", price: 3500, category: "Clothing", img: "https://images.pexels.com/photos/1598507/pexels-photo-1598507.jpeg?auto=compress&cs=tinysrgb&w=600", desc: "Premium quality blue denim jeans with a comfortable slim fit." },
        { id: 2, title: "Silk Summer Dress", price: 4500, category: "Clothing", img: "https://images.pexels.com/photos/985635/pexels-photo-985635.jpeg?auto=compress&cs=tinysrgb&w=600", desc: "Elegant floral silk dress." },
        { id: 3, title: "Macbook Pro Laptop", price: 350000, category: "Electronics", img: "https://images.pexels.com/photos/18105/pexels-photo.jpg?auto=compress&cs=tinysrgb&w=600", desc: "High performance laptop for professional use." },
        { id: 4, title: "Wireless Headphones", price: 12000, category: "Electronics", img: "https://images.pexels.com/photos/3394651/pexels-photo-3394651.jpeg?auto=compress&cs=tinysrgb&w=600", desc: "Noise cancelling Bluetooth tech." },
        { id: 5, title: "Modern Sofa Set", price: 85000, category: "Furniture", img: "https://images.pexels.com/photos/1866149/pexels-photo-1866149.jpeg?auto=compress&cs=tinysrgb&w=600", desc: "Luxury green velvet sofa." },
        { id: 6, title: "Luxury Gold Watch", price: 15000, category: "Jewelry & Watches", img: "https://images.pexels.com/photos/3033347/pexels-photo-3033347.jpeg?auto=compress&cs=tinysrgb&w=600", desc: "Classic analog watch." },
        { id: 7, title: "Makeup Palette", price: 2800, category: "Makeup & Beauty", img: "https://images.pexels.com/photos/208052/pexels-photo-208052.jpeg?auto=compress&cs=tinysrgb&w=600", desc: "Professional beauty palette." },
        { id: 8, title: "Kitchen Table Set", price: 15000, category: "Kitchen & Dining", img: "https://images.pexels.com/photos/279648/pexels-photo-279648.jpeg?auto=compress&cs=tinysrgb&w=600", desc: "Ceramic dining set." }
    ],
    categories: [
        { name: 'Clothing', img: 'https://images.pexels.com/photos/996329/pexels-photo-996329.jpeg?auto=compress&cs=tinysrgb&w=500' },
        { name: 'Electronics', img: 'https://images.pexels.com/photos/356056/pexels-photo-356056.jpeg?auto=compress&cs=tinysrgb&w=500' },
        { name: 'Furniture', img: 'https://images.pexels.com/photos/1350789/pexels-photo-1350789.jpeg?auto=compress&cs=tinysrgb&w=500' },
        { name: 'Jewelry & Watches', img: 'https://images.pexels.com/photos/190819/pexels-photo-190819.jpeg?auto=compress&cs=tinysrgb&w=500' }
    ],
    cart: [],
    currency: 'PKR'
};

// --- Format Price Logic ---
function formatPrice(val) {
    if (state.currency === 'USD') return '$' + (val / USD_RATE).toFixed(2);
    return 'Rs ' + val.toLocaleString();
}

// --- Page Rendering Functions ---
function renderHome() {
    const view = document.getElementById('view');
    view.innerHTML = `
        <section class="hero-banner"><div class="hero-overlay"></div><div class="hero-content"><h1>Shop With Us</h1><p>Premium lifestyle collections delivered home.</p><a href="#/products" class="btn-hero">SHOP NOW</a></div></section>
        <div class="container">
            <h2 style="margin-top:40px">Top Categories</h2>
            <div class="categories-grid" id="catGrid"></div>
            <h2 style="margin-top:40px">Featured Collection</h2>
            <div class="grid" id="homeGrid"></div>
        </div>
    `;

    const catGrid = document.getElementById('catGrid');
    state.categories.forEach(cat => {
        const a = document.createElement('a');
        a.className = 'category-card';
        a.href = `#/category/${encodeURIComponent(cat.name)}`;
        a.innerHTML = `<img src="${cat.img}" onerror="this.src='https://placehold.co/400x200?text=Category'"><div class="cat-overlay"><span>${cat.name}</span></div>`;
        catGrid.appendChild(a);
    });

    renderProductList('homeGrid', state.products.slice(0, 4));
}

function renderProductList(containerId, items) {
    const grid = document.getElementById(containerId);
    if (!grid) return;
    grid.innerHTML = items.map(p => `
        <div class="card" onclick="location.hash='#/product/${p.id}'">
            <img src="${p.img}" onerror="this.src='https://placehold.co/300x300?text=Image+Not+Found'">
            <div style="margin-top:10px; font-weight:bold;">${p.title}</div>
            <div class="price">${formatPrice(p.price)}</div>
            <button class="btn-blue-submit" style="padding:8px" onclick="event.stopPropagation(); addToBag(${p.id})">Add to Bag</button>
        </div>
    `).join('');
}

function renderProductDetail(id) {
    const p = state.products.find(i => i.id === id);
    if (!p) return;
    document.getElementById('view').innerHTML = `
        <div class="container" style="padding:50px 0; display:flex; gap:50px; flex-wrap:wrap;">
            <img src="${p.img}" style="width:400px; border-radius:15px; box-shadow:0 10px 30px rgba(0,0,0,0.1)">
            <div style="flex:1">
                <h1>${p.title}</h1>
                <p style="color:#0081C9; font-weight:bold">${p.category}</p>
                <h2 style="font-size:32px">${formatPrice(p.price)}</h2>
                <p style="font-size:18px; color:#666; line-height:1.6">${p.desc}</p>
                <button class="btn-blue-submit" style="width:250px; margin-top:20px" onclick="addToBag(${p.id})">Add to Bag</button>
            </div>
        </div>
    `;
}

// --- Cart Logic ---
function addToBag(id) {
    const p = state.products.find(x => x.id === id);
    const existing = state.cart.find(c => c.id === id);
    if (existing) existing.qty++;
    else state.cart.push({ ...p, qty: 1 });
    updateBagUI();
    alert("Added to Bag!");
}

function updateBagUI() {
    const itemsDiv = document.getElementById('cartItems');
    let total = 0;
    itemsDiv.innerHTML = state.cart.map(c => {
        total += (c.price * c.qty);
        return `
            <div style="display:flex; justify-content:space-between; padding:10px 0; border-bottom:1px solid #eee;">
                <div><b>${c.title}</b><br>${formatPrice(c.price)} x ${c.qty}</div>
                <button onclick="removeItem(${c.id})" style="border:none; background:none; cursor:pointer; color:red">🗑️</button>
            </div>
        `;
    }).join('');
    document.getElementById('cartTotal').innerText = formatPrice(total);
    document.getElementById('cartCount').innerText = state.cart.length;
}

window.removeItem = (id) => {
    state.cart = state.cart.filter(i => i.id !== id);
    updateBagUI();
};

// --- Advanced Search & Sort Logic ---
async function doSearch() {
    const q = document.getElementById('searchInput').value.trim();
    // This calls the Levenshtein (Fuzzy Search) logic in C++
    const res = await fetch(`${API_BASE}/search?q=${q}`);
    const data = await res.json();
    state.products = data.products; 
    onHashChange();
}

window.fillSearch = (val) => {
    document.getElementById('searchInput').value = val;
    document.getElementById('suggestionsBox').classList.add('hidden');
    doSearch(); 
};

// --- Routing ---
function onHashChange() {
    const h = location.hash || '#/';
    if (h === '#/') renderHome();
    else if (h === '#/products') {
        document.getElementById('view').innerHTML = `<div class="container" style="padding-top:40px"><h2>Our Collection</h2><div class="grid" id="allGrid"></div></div>`;
        renderProductList('allGrid', state.products);
    }
    else if (h === '#/about') document.getElementById('view').innerHTML = `<div class="container info-box"><h1>About Us</h1><p>We provide the highest quality items at competitive prices in Pakistan.</p></div>`;
    else if (h === '#/contact') document.getElementById('view').innerHTML = `<div class="container info-box"><h1>Contact Us</h1><p>Dolmen Mall, Karachi. | Phone: +92 21 35871234</p></div>`;
    else if (h.startsWith('#/category/')) {
        const cat = decodeURIComponent(h.split('/')[2]);
        const filtered = state.products.filter(p => p.category === cat);
        document.getElementById('view').innerHTML = `<div class="container" style="padding-top:40px"><h2>Collection: ${cat}</h2><div class="grid" id="catGrid"></div></div>`;
        renderProductList('catGrid', filtered);
    }
    else if (h.startsWith('#/product/')) renderProductDetail(parseInt(h.split('/')[2]));
}

// --- Initialization ---
function init() {
    // 1. Basic UI Handlers
    document.getElementById('loginBtn').onclick = () => document.getElementById('loginModal').classList.remove('hidden');
    document.getElementById('closeLogin').onclick = () => document.getElementById('loginModal').classList.add('hidden');
    document.getElementById('cartBtn').onclick = () => document.getElementById('cartPanel').classList.toggle('hidden');
    document.getElementById('closeCart').onclick = () => document.getElementById('cartPanel').classList.add('hidden');
    document.getElementById('searchBtn').onclick = doSearch;
    document.getElementById('currencySelect').onchange = (e) => { state.currency = e.target.value; onHashChange(); };

    // 2. Logic for Merge Sort (Calling the C++ Merge Sort Endpoint)
    document.getElementById('sortSelect').addEventListener('change', async (e) => {
        if (e.target.value === 'price') {
            const res = await fetch(`${API_BASE}/products/sort/price`);
            const data = await res.json();
            state.products = data.products; 
            onHashChange();
        }
    });

    // 3. Logic for Autocomplete (Calling the C++ Trie Endpoint)
    document.getElementById('searchInput').addEventListener('input', async (e) => {
        const q = e.target.value;
        const box = document.getElementById('suggestionsBox');
        if (q.length < 2) { box.classList.add('hidden'); return; }

        const res = await fetch(`${API_BASE}/autocomplete?q=${q}`);
        const data = await res.json();
        
        if (data.suggestions && data.suggestions.length > 0) {
            box.classList.remove('hidden');
            box.innerHTML = data.suggestions.map(s => `<div style="padding:10px; cursor:pointer;" onclick="fillSearch('${s}')">${s}</div>`).join('');
        } else {
            box.classList.add('hidden');
        }
    });

    window.onhashchange = onHashChange;
    onHashChange();
}

window.onload = init;
const API_BASE = 'http://localhost:18080';

const state = {
    products: [],
    cart: [],
    categories: [
        { name: "Clothing", img: "https://images.pexels.com/photos/996329/pexels-photo-996329.jpeg?auto=compress&cs=tinysrgb&w=500" },
        { name: "Home Goods", img: "https://images.pexels.com/photos/1090638/pexels-photo-1090638.jpeg?auto=compress&cs=tinysrgb&w=500" },
        { name: "Makeup & Beauty", img: "https://images.pexels.com/photos/208052/pexels-photo-208052.jpeg?auto=compress&cs=tinysrgb&w=500" },
        { name: "Bathroom Products", img: "https://images.pexels.com/photos/4239013/pexels-photo-4239013.jpeg?auto=compress&cs=tinysrgb&w=500" },
        { name: "Furniture", img: "https://images.pexels.com/photos/1866149/pexels-photo-1866149.jpeg?auto=compress&cs=tinysrgb&w=500" },
        { name: "Electronics", img: "https://images.pexels.com/photos/2047905/pexels-photo-2047905.jpeg?auto=compress&cs=tinysrgb&w=500" },
        { name: "Jewelry & Watches", img: "https://images.pexels.com/photos/190819/pexels-photo-190819.jpeg?auto=compress&cs=tinysrgb&w=500" },
        { name: "Kitchen & Dining", img: "https://images.pexels.com/photos/279648/pexels-photo-279648.jpeg?auto=compress&cs=tinysrgb&w=500" }
    ],
    backup: [
        // --- CLOTHING (3 Items) ---
        { id: 1, title: "Modern Denim Pants", price: 4500, category: "Clothing", img: "https://images.pexels.com/photos/1598507/pexels-photo-1598507.jpeg?auto=compress&w=600" },
        { id: 2, title: "Classic Black T-Shirt", price: 1500, category: "Clothing", img: "https://images.pexels.com/photos/4066293/pexels-photo-4066293.jpeg?auto=compress&w=600" },
        

        // --- HOME GOODS (3 Items) ---
        { id: 4, title: "Rough register", price: 1200, category: "Home Goods", img: "https://images.pexels.com/photos/6710158/pexels-photo-6710158.jpeg?auto=compress&w=600" },
        { id: 6, title: "Minimalist Clock", price: 2800, category: "Home Goods", img: "https://images.pexels.com/photos/210528/pexels-photo-210528.jpeg?auto=compress&w=600" },

        // --- MAKEUP & BEAUTY (3 Items) ---
        { id: 7, title: "Matte Lipstick Set", price: 2500, category: "Makeup & Beauty", img: "https://images.pexels.com/photos/2533266/pexels-photo-2533266.jpeg?auto=compress&w=600" },
        { id: 8, title: "Pro Eyeshadow Palette", price: 4500, category: "Makeup & Beauty", img: "https://images.pexels.com/photos/208052/pexels-photo-208052.jpeg?auto=compress&w=600" },
        { id: 9, title: "Organic Skin Serum", price: 3200, category: "Makeup & Beauty", img: "https://images.pexels.com/photos/3373736/pexels-photo-3373736.jpeg?auto=compress&w=600" },

        { id: 10, title: "Cotton Towel Set", price: 2200, category: "Bathroom Products", img: "https://images.pexels.com/photos/4210339/pexels-photo-4210339.jpeg?auto=compress&cs=tinysrgb&w=600" },
        { id: 11, title: "Luxury Soap Dispenser", price: 1800, category: "Bathroom Products", img: "https://images.pexels.com/photos/4239013/pexels-photo-4239013.jpeg?auto=compress&cs=tinysrgb&w=600" },
        { id: 12, title: "Organic Shampoo Set", price: 2500, category: "Bathroom Products", img: "https://images.pexels.com/photos/3735657/pexels-photo-3735657.jpeg?auto=compress&cs=tinysrgb&w=600" },
        // --- FURNITURE (3 Items) ---
        { id: 13, title: "Modern Armchair", price: 25000, category: "Furniture", img: "https://images.pexels.com/photos/1866149/pexels-photo-1866149.jpeg?auto=compress&w=600" },
        { id: 14, title: "Wooden Coffee Table", price: 15000, category: "Furniture", img: "https://images.pexels.com/photos/890669/pexels-photo-890669.jpeg?auto=compress&w=600" },
        { id: 15, title: "Minimalist Bookshelf", price: 18000, category: "Furniture", img: "https://images.pexels.com/photos/2067561/pexels-photo-2067561.jpeg?auto=compress&w=600" },

        // --- ELECTRONICS (3 Items) ---
        { id: 16, title: "Wireless Bluetooth Headphones", price: 8500, category: "Electronics", img: "https://images.pexels.com/photos/3394651/pexels-photo-3394651.jpeg?auto=compress&w=600" },
        { id: 17, title: "Professional DSLR Camera", price: 150000, category: "Electronics", img: "https://images.pexels.com/photos/51383/photo-camera-subject-photographer-51383.jpeg?auto=compress&w=600" },
        { id: 18, title: "Smart Gaming Laptop", price: 280000, category: "Electronics", img: "https://images.pexels.com/photos/18105/pexels-photo.jpg?auto=compress&w=600" },

        // --- JEWELRY & WATCHES (3 Items) ---
        { id: 19, title: "Luxury Gold Watch", price: 45000, category: "Jewelry & Watches", img: "https://images.pexels.com/photos/380782/pexels-photo-380782.jpeg?auto=compress&w=600" },
        { id: 20, title: "Diamond Pendant Necklace", price: 85000, category: "Jewelry & Watches", img: "https://images.pexels.com/photos/190819/pexels-photo-190819.jpeg?auto=compress&w=600" },
        { id: 21, title: "Silver Minimalist Bracelet", price: 12000, category: "Jewelry & Watches", img: "https://images.pexels.com/photos/691046/pexels-photo-691046.jpeg?auto=compress&w=600" },

        // --- KITCHEN & DINING (3 Items) ---
        { id: 22, title: "Ceramic Dinner Set", price: 9500, category: "Kitchen & Dining", img: "https://images.pexels.com/photos/279648/pexels-photo-279648.jpeg?auto=compress&w=600" },
        { id: 23, title: "Electric Espresso Maker", price: 25000, category: "Kitchen & Dining", img: "https://images.pexels.com/photos/302899/pexels-photo-302899.jpeg?auto=compress&w=600" },
        { id: 24, title: "Stainless Steel Cookware", price: 18000, category: "Kitchen & Dining", img: "https://images.pexels.com/photos/4552129/pexels-photo-4552129.jpeg?auto=compress&w=600" }
    ]
};

// --- SYNC & SEARCH ---
async function syncProducts() {
    try {
        const res = await fetch(`${API_BASE}/products`);
        const data = await res.json();
        state.products = data.products.length ? data.products : state.backup;
    } catch (e) { state.products = state.backup; }
    onHashChange();
}

async function runSearch() {
    const q = document.getElementById('searchInput').value;
    if(!q) return syncProducts();
    try {
        const res = await fetch(`${API_BASE}/search?q=${encodeURIComponent(q)}`);
        const data = await res.json();
        state.products = data.products;
    } catch (e) {
        state.products = state.backup.filter(p => p.title.toLowerCase().includes(q.toLowerCase()) || p.category.toLowerCase().includes(q.toLowerCase()));
    }
    location.hash = '#/products';
    onHashChange();
}

// TRIE Autocomplete
document.getElementById('searchInput').addEventListener('input', async (e) => {
    const q = e.target.value;
    const box = document.getElementById('suggestionsBox');
    if (q.length < 2) { box.classList.add('hidden'); return; }
    try {
        const res = await fetch(`${API_BASE}/autocomplete?q=${q}`);
        const data = await res.json();
        if (data.suggestions.length) {
            box.classList.remove('hidden');
            box.innerHTML = data.suggestions.map(s => `<div onclick="fillSearch('${s}')">${s}</div>`).join('');
        } else { box.classList.add('hidden'); }
    } catch (err) { box.classList.add('hidden'); }
});

function fillSearch(val) {
    document.getElementById('searchInput').value = val;
    document.getElementById('suggestionsBox').classList.add('hidden');
    runSearch();
}

// --- CART LOGIC (MATCHES SCREENSHOT #4) ---
function addToBag(id) {
    const product = state.products.find(p => p.id === id) || state.backup.find(p => p.id === id);
    if(product) {
        state.cart.push({...product, cartId: Date.now()});
        updateCartUI();
        document.getElementById('cartPanel').classList.remove('hidden');
    }
}

function updateCartUI() {
    const cartItems = document.getElementById('cartItems');
    const cartTotal = document.getElementById('cartTotal');
    const cartCount = document.getElementById('cartCount');
    const cartHeaderTitle = document.getElementById('cartHeaderTitle');
    const footer = document.getElementById('cartFooter');
    
    cartCount.innerText = state.cart.length;
    cartHeaderTitle.innerText = `My Cart (${state.cart.length})`;
    
    if(state.cart.length === 0) {
        footer.classList.add('hidden');
        cartItems.innerHTML = `
            <div class="empty-cart-view">
                <div class="empty-cart-icon">🛒</div>
                <div class="empty-cart-text">Your cart is empty</div>
                <button class="btn-primary" onclick="toggleCart()" style="width:200px">Continue Shopping</button>
            </div>`;
    } else {
        footer.classList.remove('hidden');
        let total = 0;
        cartItems.innerHTML = state.cart.map(item => {
            total += item.price;
            return `
                <div class="cart-item">
                    <img src="${item.img}">
                    <div class="cart-item-info">
                        <h4>${item.title}</h4>
                        <p>Rs ${item.price.toLocaleString()}</p>
                        <button class="remove-btn" onclick="removeFromCart(${item.cartId})">Remove</button>
                    </div>
                </div>`;
        }).join('');
        cartTotal.innerText = `Rs ${total.toLocaleString()}`;
    }
}

window.removeFromCart = (cartId) => {
    state.cart = state.cart.filter(item => item.cartId !== cartId);
    updateCartUI();
};

function toggleCart() {
    document.getElementById('cartPanel').classList.toggle('hidden');
}

// --- RENDERING ---
function renderHome() {
    const view = document.getElementById('view');
    view.innerHTML = `
        <section class="hero-banner">
            <div class="hero-content"><h1>Shoply<span>.</span></h1><p>Curated for you.</p></div>
        </section>
        <div class="container">
            <h2>Top Categories</h2>
            <div class="cat-grid" id="catGrid"></div>
            <h2 style="margin-top:40px;">Featured Collection</h2>
            <div class="grid" id="mainGrid"></div>
        </div>`;

    document.getElementById('catGrid').innerHTML = state.categories.map(c => `
        <div class="cat-card" style="cursor:pointer" onclick="filterByCategory('${c.name}')">
            <img src="${c.img}">
            <div class="cat-overlay"><span>${c.name}</span></div>
        </div>
    `).join('');

    renderList('mainGrid', state.products.slice(0, 4));
}

window.filterByCategory = (catName) => {
    state.products = state.backup.filter(p => p.category === catName);
    location.hash = '#/products';
    onHashChange();
};

function renderList(targetId, items) {
    const grid = document.getElementById(targetId);
    if (!grid) return;
    grid.innerHTML = items.map(p => `
        <div class="card">
            <div class="img-container"><img src="${p.img}"></div>
            <div class="card-body">
                <h3>${p.title}</h3>
                <p style="color:var(--primary); font-weight:800; margin:10px 0;">Rs ${p.price.toLocaleString()}</p>
                <button class="btn-primary" onclick="addToBag(${p.id})">Add to Bag</button>
            </div>
        </div>`).join('');
}

function onHashChange() {
    const h = location.hash || '#/';
    if (h === '#/') renderHome();
    else if (h === '#/products') {
        document.getElementById('view').innerHTML = '<div class="container"><h2 style="margin-top:30px;">Products</h2><div class="grid" id="allGrid"></div></div>';
        renderList('allGrid', state.products);
    }
}

function init() {
    document.getElementById('searchBtn').onclick = runSearch;
    document.getElementById('loginBtn').onclick = () => document.getElementById('loginModal').classList.remove('hidden');
    document.getElementById('closeLogin').onclick = () => document.getElementById('loginModal').classList.add('hidden');
    document.getElementById('cartBtn').onclick = toggleCart;
    document.getElementById('closeCart').onclick = toggleCart;
    window.onhashchange = onHashChange;
    syncProducts();
    updateCartUI();
}

window.onload = init;
window.fillSearch = fillSearch;
window.addToBag = addToBag;
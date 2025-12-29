# Frontend — Shoply Demo

Overview
- This folder contains a single-page demo storefront (HTML/CSS/JS) that mimics an online fashion store UI.

Key files
- `index.html`: SPA entry with header, nav, modal and cart.
- `styles.css`: Styling for homepage, product grid, modal and cart.
- `app.js`: Frontend logic, routing, product rendering, cart state and client-side PKR conversion.

Run locally
1. Open `index.html` directly in a browser (file://) for a quick preview.
2. Or serve via a simple static server (recommended):

```powershell
cd frontend
python -m http.server 8000
# open http://localhost:8000
```

Backend integration
- The frontend attempts to call `http://localhost:18080` for API endpoints. If no backend is running, the app falls back to built-in demo products.

PKR pricing
- Prices are authored in USD in the demo data and converted client-side to PKR using the `USD_TO_PKR` constant in `app.js`.
- To change the conversion, edit `USD_TO_PKR` in `app.js`.

Development
- Edit `app.js` to add more product fields, integrate real APIs, or change routing.
- Use the browser console to debug and inspect localStorage keys: `shoply_cart`, `shoply_wish`, `shoply_currency`.

License
- Demo code — use and adapt freely for learning and prototyping.

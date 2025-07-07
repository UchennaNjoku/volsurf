# volsurf-cpp
volsurf‑cpp





High‑Performance Volatility Surface Engine with C++ backend and Python front‑end. Provides fast implied‑volatility inversion, arbitrage‑free surface fitting, animation, and exotic option pricing in a single pipeline.

🚀 Features

C++ Core: Implements Newton–Raphson + bisection IV solver, constrained spline interpolation, and multi‑threaded grid evaluation with C++17 & OpenMP.

Python Bindings: Exposes high‑performance routines via pybind11 for seamless integration in Jupyter, Streamlit, or other Python apps.

Data Ingestion: Fetches and cleans real options chains from public APIs (Yahoo Finance, Polygon.io) into Parquet/CSV for reproducible analysis.

Interactive Visualization: 3D surface plots and animations via Matplotlib and Plotly; live exploration in Streamlit dashboard.

Exotic Pricing: Uses fitted surface to price barrier and digital options; compares results with QuantLib benchmarks.

CI & Testing: Automated builds and tests via GitHub Actions; C++ unit tests (Catch2), Python smoke tests, and coverage reporting.

📐 Architecture

├── CMakeLists.txt         # Build configuration for C++ core & bindings
├── setup.py               # Editable pip install integration
├── include/               # C++ headers (IVSolver, SplineFit, etc.)
├── src/                   # C++ implementation files
├── bindings/              # pybind11 bindings definitions
├── tests/                 # C++ unit tests (test_iv, test_spline)
├── python/                # Python modules & helper scripts
├── notebooks/             # Jupyter notebooks for exploration & demos
├── app/                   # Streamlit dashboard code
├── data/                  # Sample option‑chain datasets
└── README.md              # This file

⚙️ Prerequisites

C++17 compiler (AppleClang, GCC, or Clang)

CMake ≥ 3.21

Eigen3 (header‑only)

pybind11

libomp (for OpenMP support)

Python 3.7+ and virtual environment (venv or conda)

🛠 Installation

1. Clone the repository

git clone https://github.com/your-username/volsurf-cpp.git
cd volsurf-cpp

2. Create & activate Python environment

python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip

3. Install in editable mode

pip install -e .

This runs CMake under the hood, builds the C++ library, and installs the volsurf_bindings module into your environment.

🔨 Building from Source

If you prefer manual CMake steps:

mkdir build && cd build
cmake ..
make -j$(nproc)
ctest --output-on-failure    # run C++ unit tests
cd ..

💻 Usage

Implied Volatility Grid

import volsurf_bindings as vb
# Example inputs
decoded_prices = [...]       # list of mid‑prices
strikes =  [...]             # matching list of strikes
expiries = [...]             # list of T in years
iv_grid = vb.compute_iv_grid(decoded_prices, spot, strikes, expiries, r, q)

Surface Fitting & Animation

from volsurf_bindings import fit_surface
surface = fit_surface(iv_grid, strikes, expiries)
# Plot using Plotly
surface.plot_3d()
# Animate
surface.animate("surface_evolution.gif")

Streamlit Dashboard

cd app
streamlit run app.py

Opens an interactive UI to select dates, view the 3D surface, and export animations.

📈 Performance

Implementation

Grid Size

Time (mean)

Speedup

Python only

50×50

1.2 s

1×

C++ + OpenMP

50×50

0.25 s

4.8×

🧪 Testing & CI

C++ Tests: Run with ctest in build/.

Python Tests: Simple pytest suite (smoke tests for import & core functions).

GitHub Actions: Automatically builds, tests, and reports coverage on push & PR.

🔗 Related Projects & References

Jim Gatheral, The Volatility Surface (2006)

QuantLib – reference implementation of derivatives pricers

py_vollib – Python wrapper for Bid‑Ask Black–Scholes IV

🤝 Contributing

Contributions are welcome! Please:

Fork the repo and create a feature branch

Run existing tests & add new ones

Submit a Pull Request with clear description and tests


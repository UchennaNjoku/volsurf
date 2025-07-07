#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "IVSolver.hpp"

namespace py = pybind11;

PYBIND11_MODULE(volsurf_bindings, m) {
    m.doc() = "High-performance volsurf C++ backend";

    m.def("solve_iv", &solveIV,
          "Solve implied vol given market price and params",
          py::arg("price"), py::arg("S"),
          py::arg("K"), py::arg("T"),
          py::arg("r"), py::arg("q"));

    m.def("compute_iv_grid", &computeIVGrid,
          "Compute IVs over arrays",
          py::arg("prices"), py::arg("S"),
          py::arg("strikes"), py::arg("expiries"),
          py::arg("r"), py::arg("q"));
}

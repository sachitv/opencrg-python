#include <pybind11/pybind11.h>

#include "opencrg.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;
using opencrg::OpenCRG;

PYBIND11_MODULE(opencrg, m) {
    m.doc() = R"pbdoc(
        Pybind11 bindings for OpenCRG
        -----------------------

        .. currentmodule:: opencrg

        .. autosummary::
           :toctree: _generate

           OpenCRG
    )pbdoc";

    py::class_<OpenCRG>(m, "OpenCRG")
        .def(py::init<const std::string &>())
        .def("convert_xy_to_uv", &OpenCRG::ConvertXYtoUV, R"doc(
            Convert positions from (x,y) coordinates to (u,v) coordinates

            Args:
            x (float): x coordinate (meters) of the point we need to convert.
            y (float): y coordinate (meters) of the point we need to convert.

            Returns:
            Tuple[float, float]: A tuple of (u,v) values of the corresponding (x,y) points.
        )doc")
        .def("convert_uv_to_xy", &OpenCRG::ConvertUVtoXY, R"doc(
            Convert positions from (u,v) coordinates to (x,y) coordinates

            Args:
            u (float): u coordinate (meters) of the point we need to convert.
            v (float): v coordinate (meters) of the point we need to convert.

            Returns:
            Tuple[float, float]: A tuple of (x,y) values of the corresponding (u,v) points.
        )doc")
        .def("get_heading_and_curvature_at_xy", &OpenCRG::GetHeadingAndCurvatureAtXY, R"doc(
            Get track heading angle (radians) and curvature (1/meter) at a (x,y) position.
            Note: Heading and curvature are commonly referred to as p and k.

            Args:
            x (float): x coordinate (meters) of the point we consider.
            y (float): y coordinate (meters) of the point we consider.

            Returns:
            Tuple[float, float]: A tuple of (heading, curvature) values at the corresponding (x,y) points.
        )doc")
        .def("get_heading_and_curvature_at_uv", &OpenCRG::GetHeadingAndCurvatureAtUV, R"doc(
            Get track heading angle (radians) and curvature (1/meter) at a (u,v) position.
            Note: Heading and curvature are commonly referred to as p and k.

            Args:
            x (float): x coordinate (meters) of the point we consider.
            y (float): y coordinate (meters) of the point we consider.

            Returns:
            Tuple[float, float]: A tuple of (heading, curvature) values at the corresponding (u,v) points.
        )doc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}

# setup.py
import os
import re
import sys
import subprocess
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        super().__init__(name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)

class CMakeBuild(build_ext):
    def run(self):
        # ensure CMake is available
        try:
            subprocess.check_output(["cmake", "--version"])
        except OSError:
            raise RuntimeError("CMake must be installed to build extensions")
        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        cfg = "Debug" if self.debug else "Release"
        # configure arguments
        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            f"-DCMAKE_BUILD_TYPE={cfg}",
        ]
        build_args = ["--config", cfg]

        build_temp = self.build_temp
        os.makedirs(build_temp, exist_ok=True)
        # run CMake configure
        subprocess.check_call(["cmake", ext.sourcedir] + cmake_args, cwd=build_temp)
        # run CMake build
        subprocess.check_call(["cmake", "--build", "."] + build_args, cwd=build_temp)

setup(
    name="volsurf_cpp",
    version="0.1.0",
    author="Uchenna Njoku",
    description="High-performance Vol Surface Engine (C++/Python)",
    long_description="C++ core for IV solving & surface fitting, exposed via pybind11",
    ext_modules=[CMakeExtension("volsurf_bindings")],
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False,
    install_requires=[
        "numpy",
        "pandas",
        "scipy",
        "matplotlib",
        "streamlit",
        "py_vollib",
        "pybind11",
    ],
)

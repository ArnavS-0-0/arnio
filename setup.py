# Minimal setup.py fallback for editable installs
from scikit_build_core.setuptools.build_cmake import build_cmake
from setuptools import setup

setup(
    cmake_source_dir=".",
)

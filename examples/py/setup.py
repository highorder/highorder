#!/usr/bin/env python

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

setup(name='basic_usage',
      ext_modules=[Extension(
          "basic_usage",
          ["basic_usage.pyx",
           "doublify.cpp"],
          include_dirs=['../../include', '../..'], # ../.. is crucial for Cython
          extra_compile_args=['-std=c++0x'],
          language="c++")],
      cmdclass={'build_ext': build_ext})

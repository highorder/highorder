#!/usr/bin/env python

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

extensions = [
    Extension('highorder.arrays',
              ['highorder/arrays.pyx'],
              include_dirs = ['include'],
              extra_compile_args = ['-O3', '-std=c++0x'],
              language='c++')
    ]

setup(name='highorder',
      url='http://highorder.berkeley.edu/',
      packages=['highorder'],
      headers=['include/highorder/array.h',
               'include/highorder/pybridge.hpp'],
      package_data={'highorder': ['*.pxd']},
      ext_modules=extensions,
      cmdclass={'build_ext': build_ext})

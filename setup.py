#!/usr/bin/env python

from distutils.core import setup

setup(name='Distutils',
      version='RotaGenerator',
      description='Generate a rota',
      author='Mike Pyne',
      author_email='mike@pyne.me.uk',
      url='https://github.com/mikepyne/RotaGenerator',
      packages=['rota', 'spiders'],
      package_dir={'': 'src'},
     )

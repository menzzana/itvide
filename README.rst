
ItVide
======

Authors: Henric Zazzi

ItVide software for visualizing big data.

This software visualizes big data similarly to softwares as many Business Intelligence Platforms and
this kind of approach is also viable for the scientific or big data area.
At the moment the software can only import csv files.

BUILDING (from source bundle)
-----------------------------

*** READ THIS CAREFULLY: you MUST install the required libraries! ***

DEPENDENCIES
------------

============== ========================================================================================================
Dependency     Version/source
============== ========================================================================================================
C++ compiler   version 5+
qmake          version 5+
QCustomPlot    The QCustomPlot can be downloaded from http://www.qcustomplot.com
============== ========================================================================================================

In order to build just run...::

  cd [SOURCE DIR]
  qmake -makefile EXTERNAL_PATH="<QCUSTOMPLOT FOLDER>"
  make

The Makefile is created in the source dir whereas the executable
and object files reside in build/[release/debug]

If you are using Qt Creator goto Projects->Build&Run->Build->Build Steps
Open *Details* and add as *additional arguments*
::

  EXTERNAL_PATH="<QCUSTOMPLOT FOLDER>"

LICENSE
-------

ItVide
Copyright (C) 2017  Henric Zazzi <henric@zazzi.se>

ItVide is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

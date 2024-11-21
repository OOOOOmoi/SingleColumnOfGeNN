#!/bin/bash
genn-buildmodel.sh SingleColumn.cc -d
genn-create-user-project.sh SingleColumn SingleColumnSim.cc
# make
# ./SingleColumn
# python plot.py
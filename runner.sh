#!/bin/bash
genn-buildmodel.sh SingleColumn.cc
genn-create-user-project-record.sh SingleColumn SingleColumnSim.cc RecordFunc.cc
make
./SingleColumn
# python plot.py
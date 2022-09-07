#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR
mkdir -p ~/.local/share/jupyter/kernels/
cp -r TAPIA_OPENMP ~/.local/share/jupyter/kernels/
cp -r TAPIA_MPI ~/.local/share/jupyter/kernels/

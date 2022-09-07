#!/bin/bash
module purge
module load cgpu
module use /project/projectdirs/m1759/csdaley/Modules/cgpu/modulefiles
module load PrgEnv-llvm/14.0.0-git_20211104b
module load python
exec "$@"
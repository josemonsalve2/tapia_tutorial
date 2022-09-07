#!/bin/bash
module purge
module load cgpu
module load openmpi
module load python
exec "$@"
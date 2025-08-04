#!/bin/bash

PYTHON_DIR="csv/venv"

# First run the simulation and wait for an exit code
obj/program > /dev/null
exit_status=$?

if [ ${exit_status} -eq 0 ]; then
    echo "Simulation has finished successfully. Calling Python to generate plot analyzes"
    cd "csv"
    python3 req.py
    echo "Python has finished analyzing the data."
else
    echo "Something went wrong and the simulation was finished with an error"
fi
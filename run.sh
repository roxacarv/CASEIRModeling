#!/bin/bash

# First run the simulation and wait for an exit code
obj/program > /dev/null
exit_status=$?

check_python_libraries() {
    pip check >/dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "Dependencies missing or broken, installing requirements..."
        pip install --r requirements.txt
        if [ $? -ne 0 ]; then
            echo "pip install failed. Exiting program as it will not be able to correctly run analysis_plt.py file"
            exit 1
        fi
    else
        echo "All requirements already satisfied."
    fi
}

if [ ${exit_status} -eq 0 ]; then
    echo "Simulation has finished successfully. Calling Python to generate plot analyzes"
    cd "csv"
    if ! -d "venv"; then
        python3 -m venv "${PYTHON_DIR}"
        echo "Python venv was created at ${PYTHON_DIR}"
    fi
    source "venv/bin/activate"
    check_python_libraries # Check if Python libraries are installed before proceeding
    python3 analysis_plt.py
    echo "Python has finished analyzing the data."
else
    echo "Something went wrong and the simulation was finished with an error"
fi
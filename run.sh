#!/bin/bash

PYTHON_DIR="csv/venv"

# -- REQUIRED PACKAGES TO RUN SIMULATION --
PACKAGES=(
    "build-essential"
    "libsdl2-dev"
    "libsdl2-ttf-dev"
)

install_packages() {
    echo "Checking and installing required packages: ${PACKAGES[*]}"
    for package in "${PACKAGES[@]}"; do
        if dpkg-query -l "${package}" &>/dev/null; then
            echo "${package} is already installed."
        else
            echo "${package} is not installed. Installing..."
            sudo apt-get update
            sudo apt-get -y install "${package}"
        fi
    done
}

do_main_setup() {
    install_packages
    # First run the simulation and wait for an exit code
    obj/program >> /dev/null
    exit_status=$?
    if [ ${exit_status} -eq 0 ]; then
        echo "Simulation has finished successfully. Calling Python to generate plot analyzes"
        cd "csv"
        python3 req.py
        echo "Python has finished analyzing the data."
    else
        echo "Something went wrong and the simulation was finished with an error"
    fi
}

echo "Initializing project..."

do_main_setup

echo "Initilization finished"


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
    echo "Creating virtual Python environment"
    python3 -m venv "${PYTHON_DIR}"
    echo "Python venv was created at ${PYTHON_DIR}"
    echo "To activate it manually, run: . ${PYTHON_DIR}/bin/activate from $(dirname "${PYTHON_DIR}")"
    
    # Activate and install requirements in this subshell
    source "${PYTHON_DIR}/bin/activate"
    echo "Installing necessary requirements to run analysis"
    cat requirements.txt
    pip install -r requirements.txt
    deactivate
}

echo "Initializing project..."

do_main_setup

echo "Initilization finished"
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
    echo "Creating virtual Python envinronment"
    python3 -m venv ${PYTHON_DIR}
    echo "Python venv was created at ${PYTHON_DIR}, to run it, call the command: . venv/bin/activate while inside $(dirname ${PYTHON)_DIR})"
}

echo "Initializing project..."

do_main_setup

echo "Initilization finished"
import os
import subprocess
import sys
import venv

# Step 1: Setup venv path
venv_dir = os.path.join(os.getcwd(), "venv")

# Step 2: Create venv if missing
if not os.path.isdir(venv_dir):
    print("Creating virtual environment...")
    venv.create(venv_dir, with_pip=True)

# Step 3: Detect correct pip and python paths
if os.name == "nt":
    pip_executable = os.path.join(venv_dir, "Scripts", "pip.exe")
    python_executable = os.path.join(venv_dir, "Scripts", "python.exe")
else:
    pip_executable = os.path.join(venv_dir, "bin", "pip")
    python_executable = os.path.join(venv_dir, "bin", "python")

# Step 4: Upgrade pip
subprocess.run([pip_executable, "install", "--upgrade", "pip"])

# Step 5: Requirements list
requirements = [
    "contourpy==1.3.3",
    "cycler==0.12.1",
    "fonttools==4.59.0",
    "kiwisolver==1.4.8",
    "matplotlib==3.10.5",
    "numpy==2.3.2",
    "packaging==25.0",
    "pandas==2.3.1",
    "pillow==11.3.0",
    "pyparsing==3.2.3",
    "python-dateutil==2.9.0.post0",
    "pytz==2025.2",
    "scipy==1.16.1",
    "seaborn==0.13.2",
    "six==1.17.0",
    "tzdata==2025.2"
]

# Step 6: Check installed packages
installed = subprocess.check_output([pip_executable, "freeze"], text=True).splitlines()
installed_pkgs = {pkg.split("==")[0].lower(): pkg for pkg in installed}

# Step 7: Install missing ones
for req in requirements:
    pkg, ver = req.split("==")
    current = installed_pkgs.get(pkg.lower())
    if current != req:
        print(f"Installing {req}...")
        subprocess.run([pip_executable, "install", req])

print("Virtual environment ready. All packages installed.")

# Step 8: Run target script using venv Python
target_script = os.path.join(os.getcwd(), "analysis_plt.py")  # change if needed
if os.path.isfile(target_script):
    print(f"Running {target_script} using venv Python...\n")
    subprocess.run([python_executable, target_script])
else:
    print(f"Target script not found: {target_script}")
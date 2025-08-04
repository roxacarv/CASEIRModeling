# CASEIRModeling
### Cellular Automata & Epidemiology Computing
Modeling infectious diseases using the SEIR model struct and a celullar automata in C.

#### Study Resources
##### Epidemiology and Celullar Automata
  - Celullar Automata, A Discrete View of the World, Joel L. Schiff
  - [Modeling Infectious Diseases in Humans and Animals](https://dokumen.pub/modeling-infectious-diseases-in-humans-and-animals-9781400841035.html), Matt J. Keeling and Pejman Rohani
##### Real-world data
  - [The Incubation Period of Coronavirus Disease 2019 (COVID-19) From Publicly Reported Confirmed Cases](https://doi.org/10.7326/M20-05040), Lauer et al.
  - [Temporal dynamics in viral shedding and transmissibility of COVID-19](https://doi.org/10.1038/s41591-020-0869-5), He et al.

#### Tools
  - C: for simulation
  - SDL2 for GUI real-time visualiation of the simulation
  - Main Python libraries used for visualization: pandas, numpy, scipy, seaborn, matplotlib

#### Reused Code
  - [Conway's Game of Life in C++](https://github.com/roxacarv/roxacs_code_cellar/tree/master/Algorithms/Conway's%20Game%20of%20Life/C%2B%2B) that I've implemented a few years ago. Mainly used to guide a reimplementation of a Celullar Automata in C
  - Basic [code](https://github.com/roxacarv/CASEIRModeling/blob/master/usage_examples/sdl2_usage.c) for SDL2 video initialization and rendering. Used ChatGPT to get an example

#### Installation
  - Run `run.sh` to run the simulation and gather data to generate plot maps. It assumes that the C binary is already compiled. It can be safely run without running setup.
  - If any error occurred regarding libraries, use `run_hard_req.sh` instead, as it install the default Linux libraries needed.

# JPIC1d: Particle-in-Cell Simulation

----

One-Dimensional Laser Plasma Particle-In-Cell Simualtion Code.
2011-02-07, authored by Hui-Chun Wu, email:huichunwu1@gmail.com

## Installation

First check the folder structure and confirm that no files are missing.

```bash
./
├── data
│   ├── input.inp
├── README.md
└── src
    ├── creator.c
    ├── diagnosis.c
    ├── field.c
    ├── history.c
    ├── jpic.c
    ├── jpic.h
    ├── mover.c
    ├── nrutil.c
    ├── pulse.c
    ├── readfile.c
    ├── setrho.c
    └── start.c
```

You should be at this folder before continuing to the next step.

Compile:
`gcc ./src/jpic.c -o jpic`

If all things go well, a executable `jpic.exe` should appear under the same folder.

Run:
`./jpic.exe ./data/input.inp`

Data would be written into `./data/` folder.

## Usage

Open `./data/input.inp` to modify the settings, note that the `path` argument would set the folder where the diagnosis would be generated.
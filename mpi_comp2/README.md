## Prerequisite

* **MSMPI** (Not MPICH!) correctly installed

Type in cmd to check.

```cmd
set MSMPI
```
if MSMPI is installed correctly, you should be able to see these messages.

```cmd
MSMPI_BENCHMARKS=...
MSMPI_BIN=...
MSMPI_INC=...
MSMPI_LIB32=...
MSMPI_LIB64=...
```

## Build

1. open the solution `2dppicv1_s1.sln` and select configuration to **Debug-x86**
> Do select x86 to avoid possible errors, even if your OS is x64.
2. Build in Visual Studio.(Ctrl+Shift+B)
3. If compiled successfully, there shoud be `2dppicv1_s1.exe` in folder `./Debug`.
4. Open a terminal and change directory to `Debug`
```bash
cd ./Debug
```
5. run `./2dppicv1_s1.exe` in `mpiexec.exe` environment, make sure to **set the number of processes to 8**.

```bash
mpiexec.exe -n 8 ./2dppicv1_s1.exe
```
6. After all the data files have been generated in `./data/`, run `./data/Wave_MV.m` in MATLAB to check the wave.
# X-CUBE-VERTICES

The X-CUBE-VERTICES is an expansion software package for STM32Cube.
The software runs on the STM32 and includes includes the middleware 
for enabling IoT devices to connect to the Algorand Blockchain using the Vertices SDK.
The expansion is built on STM32Cube software technology to ease portability across 
different STM32 microcontrollers. The software comes with sample 
implementations on how to use the Vertices middleware on the STM32 based 
boards.

The simplest way to start using this expansion software is to run the
[vertices-client](Projects/B-L4S5I-IOT01A/Applications/vertices-client) sample application.

## Getting started

### Setting up the environment

A [Conda environment file](utils/env/environment.yml) is available. 

In order to install the environment:

```shell
# create
conda env create -f utils/env/environment.yml

# activate
conda activate vertices
```

### Custom configuration

The [readme](Projects/B-L4S5I-IOT01A/Applications/vertices-client/README.md) 
included in sample application provides instructions about setting your Wi-Fi 
credentials.

### Compile

It's now time to compile the example:

```shell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../utils/cmake/arm-gcc-toolchain.cmake
make vertices-example
```


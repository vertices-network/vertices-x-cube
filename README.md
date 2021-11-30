# X-CUBE-VERTICES

The X-CUBE-VERTICES is an expansion software package for STM32Cube.
The software runs on the STM32 and includes includes the middleware 
for enabling IoT devices to connect to the Algorand Blockchain using the Vertices SDK.
The expansion is built on STM32Cube software technology to ease portability across 
different STM32 microcontrollers. The software comes with sample 
implementations on how to use the Vertices middleware on the STM32 based 
boards.

The project is based on the [IOTA implementation](https://www.st.com/en/embedded-software/x-cube-iota1.html). The implementation has been kept into this project.

The simplest way to start using this expansion software is to run the
[vertices-client](Projects/B-L4S5I-IOT01A/Applications/vertices-client) sample application.

> ⚠️ This project is a demo to show the capabilities of the Vertices SDK on STM32 microcontrollers. It shouldn't be used in production without major modifications.

## Getting started

### Get the source

Make sure to pull the submodules when cloning the repository as the Vertices SDK is included
in the project using a git submodule:

```
git clone --recurse-submodules git@github.com:vertices-network/vertices-x-cube.git
```

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

#### Wi-Fi credentials

The [readme](Projects/B-L4S5I-IOT01A/Applications/vertices-client/README.md) 
included in sample application provides instructions about setting your Wi-Fi 
credentials.

#### Algorand account

The project example uses an account to send money to another one. You will need to copy two files corresponding to the private and public key of the sending account into `Projects/B-L4S5I-IOT01A/Applications/vertices-client/` to have this account used. You can use Vertices Unix example to create a new account or Algokey, both of them can be used to obtain the two files containing the keys. Check-out [Vertices' documentation](https://docs.vertices.network/vertices-sdk/quickstart/unix/new-account).

### Compile

It's now time to compile the example:

```shell
# from the root directory
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../utils/cmake/arm-gcc-toolchain.cmake

# build the example
# the ELF file to be loaded on the board will be located in 
# build/Projects/B-L4S5I-IOT01A/Applications/vertices-client/vertices-example.elf
make vertices-example
```

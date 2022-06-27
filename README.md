![Project Name](https://img.shields.io/badge/gameboy-emulator-success?logo=nintendo)
[![License: MIT](https://img.shields.io/badge/License-MIT-success.svg)](https://opensource.org/licenses/MIT)
[![Tests](https://github.com/raulpy271/gameboy-emulator/actions/workflows/cmake.yml/badge.svg)](https://github.com/raulpy271/gameboy-emulator/actions/workflows/cmake.yml)
[![Build Artifacts](https://github.com/raulpy271/gameboy-emulator/actions/workflows/build_artifacts.yml/badge.svg)](https://github.com/raulpy271/gameboy-emulator/actions/workflows/build_artifacts.yml)
[![My followers](https://img.shields.io/github/followers/raulpy271?style=social)](https://github.com/raulpy271)

# gameboy-emulator

A gameboy emulator written in C++ using [GTK+](https://www.gtk.org/) gui interface, and using Test Driven Development methodology. 

# Screenshoots

![Hello World screenshot](/assets/hello-world.png)

![Tetris screenshot](/assets/tetris.png)

# How to setup

## Compiling the binary

First of all, install the dependencies executing the script:

```sh
apt-get update

apt-get -y install g++ 

apt-get -y install cmake libgtk-3-dev libgtkmm-3.0-dev
```

After that, run the following commands to compile the binary:

```sh
export COMPILE_GUI=true 

make generate-buildsystem

make build-cmake
```

Now, the executable is ready, the following command starts the emulation:

```sh
./build/main <path_of_a_rom_file>
```

## Using a pre-compiled binary

> In progress(feel free to add this method of setup)

# References

See the list of useful resources:

- [Game Boy CPU Manual (pdf)](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
- [Game Boy Development community](https://gbdev.io/)
- [RGBDS - toolchain for developing Game Boy programs](https://rgbds.gbdev.io/)
- [PyBoy - Emulator](https://github.com/Baekalfen/PyBoy)
- [GTKmm Tutorial](https://developer-old.gnome.org/gtkmm-tutorial/3.24/sec-gtkmm.html.en)

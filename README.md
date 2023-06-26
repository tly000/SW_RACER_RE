# Star Wars Episode 1 Racer Decompilation Project

The goal of this repository is to document and re-implement functions of the original game for modding purposes.
The project is heavily influenced by the [OpenJKDF2]() project

This makes use of DLL injection through a simple loader located at `./loader/loader.cpp`
The code for the DLL to inject is at `./swr_reimpl`


# Usage
Run `compile.bat` script. The loader and the replacement dll should be generated in the `./build` directory. Copy these two files WITHOUT renaming them into the same directory as `SWEP1RCR.EXE`. Run the loader.

TODO (compilation with CMake)

This is based on the repository located [here](https://github.com/OpenSWE1R/swe1r-re.git), included as a submodule

The freshly installed GOG version of the game (`SWEP1RCR.EXE`) has the following md5: e1fcf50c8de2dbef70e6ad8e09371322
Other versions are not yet tested

[Wine](https://www.winehq.org/) will be used to run Visual C++ 5.0, the original compiler for the project. Through WSL, file transfer is much easier in both directions and Wine is much faster than a VM like Qemu or VirtualBox (and much simpler to setup as well)

Download the vcpp5 iso for initial compiler configuration here: https://winworldpc.com/product/visual-c/5x

See NOTES.md for more infos


# Copyright Disclaimer
The original game (Star Wars Episode 1 Racer) is a property of the LucasArts Entertainment Company LLC.

# Fair Use Disclaimer
The content provided on this repository is for informational and educational purposes only. It is not intended to infringe upon any copyrighted material.

If you believe that any content on this repository violates your copyright or intellectual property rights, please contact us immediately to seek resolution.

I am not liable for any loss or damage, including but not limited to indirect or consequential loss or damage, arising from the use of or reliance on any content found on this repository.

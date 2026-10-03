# Exo firmware onboarding

This is the STM32H753ZITx onboarding firmware. CMake builds an ELF, HEX and BIN in `build/` (or `build/windows/` on Windows). Flashing uses an ST-LINK connected to the board's SWD header.

## Dev container

Open the repository in VS Code and choose **Dev Containers: Reopen in Container**. The Ubuntu container installs CMake, Ninja, the GNU Arm compiler, Newlib and OpenOCD. In the container, run `./upload --build` to build and flash when the Linux host passes the ST-LINK USB device into Docker. Linux USB permissions may need a udev rule for ST-LINK. To build only:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

On macOS and Windows, build with the commands above in the dev container, then run the upload command on the host to access the ST-LINK USB device. The mounted checkout shares `build/exo-firmware-onboarding.bin` with the host. Uploading without a build flag only reads that binary and does not use the container's CMake cache. Do not run host builds against a container-created cache.

## Linux and macOS host

For upload-only use, install either STM32CubeProgrammer (`STM32_Programmer_CLI`) or OpenOCD. Put the programmer on `PATH`, connect the ST-LINK, then run:

```sh
./upload
```

The script flashes the existing `build/exo-firmware-onboarding.bin` at `0x08000000`, verifies and resets the board. It prefers STM32CubeProgrammer when both flash tools are installed. On Linux, configure ST-LINK USB permissions if the programmer cannot open the probe.

To build on the host before uploading, also install CMake (3.22 or newer), Ninja and GNU Arm Embedded (`arm-none-eabi-gcc`, `arm-none-eabi-objcopy`, `arm-none-eabi-size`), then run:

```sh
./upload --build
```

Bash also accepts `-Build` as an alias for the PowerShell spelling. Rebuild after source changes before uploading an existing binary.

## Windows host

For upload-only use, install STM32CubeProgrammer and the ST-LINK USB driver. Add STM32CubeProgrammer's `bin` directory to `PATH`; reopen the terminal so it picks up changes. Windows does not need CMake, Ninja, or an ARM compiler when the container builds the binary. In native PowerShell or Command Prompt, run:

```powershell
.\upload.cmd
```

Or run `powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\upload.ps1`. This programs, verifies and resets the board using the container-built binary. It can be launched from another working directory.

For an optional native Windows build, also install CMake (3.22 or newer), Ninja and STM32CubeCLT's GNU Arm tools, and add their executable directories to `PATH`. Then run:

```powershell
.\upload.cmd -Build
```

With `-Build`, Windows builds and flashes from `build/windows/`, keeping its CMake cache separate from the container's `build/` directory.

The CMake source list follows the STM32CubeIDE project. Add newly generated `.c` files to `CMakeLists.txt` if the Cube project changes.

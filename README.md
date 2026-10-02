# Exo firmware onboarding

This is the STM32H753ZITx onboarding firmware. CMake builds an ELF, HEX and BIN in `build/` (or `build/windows/` on Windows). Flashing uses an ST-LINK connected to the board's SWD header.

## Dev container

Open the repository in VS Code and choose **Dev Containers: Reopen in Container**. The Ubuntu container installs CMake, Ninja, the GNU Arm compiler, Newlib and OpenOCD. In the container, run `./upload` to build and flash when the Linux host passes the ST-LINK USB device into Docker. Linux USB permissions may need a udev rule for ST-LINK. You can also build only:

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

On macOS and Windows, run the upload command on the host, outside the dev container, to access the ST-LINK USB device. You can still use the container to edit and build. Do not share a CMake build directory between operating systems.

## Linux and macOS host

Install CMake (3.22 or newer), Ninja, GNU Arm Embedded (`arm-none-eabi-gcc`, `arm-none-eabi-objcopy`, `arm-none-eabi-size`) and either STM32CubeProgrammer (`STM32_Programmer_CLI`) or OpenOCD. Put the tools on `PATH`, connect the ST-LINK, then run:

```sh
./upload
```

The script configures a Debug build and flashes `build/exo-firmware-onboarding.bin` at `0x08000000`, verifies and resets the board. It prefers STM32CubeProgrammer when both flash tools are installed. On Linux, configure ST-LINK USB permissions if the programmer cannot open the probe.

## Windows host

Install CMake (3.22 or newer), Ninja, STM32CubeCLT (GNU Arm tools and STM32CubeProgrammer), and the ST-LINK USB driver. Add CMake, Ninja, the STM32CubeCLT GNU-tools-for-STM32 `bin` directory and STM32CubeProgrammer `bin` directory to `PATH`; reopen the terminal so it picks up changes. In native PowerShell or Command Prompt, run:

```powershell
.\upload.cmd
```

Or run `powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\upload.ps1`. The script checks the required commands before building in `build/windows/`, then programs, verifies and resets the board. It can be launched from another working directory.

The CMake source list follows the STM32CubeIDE project. Add newly generated `.c` files to `CMakeLists.txt` if the Cube project changes.

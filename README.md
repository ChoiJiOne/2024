# FoxDash
- `FoxDash` is a project for developing a simple Tetris game without using a game engine.

## Support Platform
- Windows 10/11 Home/Pro

## Dependencies
- [Git](https://git-scm.com/)
- [Visual Studio 2022](https://visualstudio.microsoft.com/ko/)
- [CMake 3.27 or later](https://cmake.org/)
- [Python 3.x](https://www.python.org/)
- [NSIS](https://nsis.sourceforge.io/Download)

## How to get repository clone?

You can obtain a copy of the repository using the following command.

```
git clone https://github.com/ChoiJiOne/FoxDash.git
```

## How to generate Visual Studio solution?

You can generate a Visual Studio solution using the `GenerateProjectFiles.bat` or `HotReload.bat` batch scripts.  

If you want to run Visual Studio after generating the Visual Studio solution, execute the batch script below. 
```
GenerateProjectFiles.bat 
```
Otherwise, run the following batch script.
```
HotReload.bat
```

## How to build solution?

This project supports building without running Visual Studio. The build script supports the following build modes: `Debug`, `Release`, `RelWithDebInfo`, and `MinSizeRel`, each with the following characteristics.

| mode | description |
|:---:|:---|
| Debug | No optimization is performed during the build process, and a debug information file (.pdb) is generated. |
| Release | Optimization is performed during the build process, and no debug information file (.pdb) is generated. |
| RelWithDebInfo | Optimization is performed during the build process, and a debug information file (.pdb) is generated. |
| MinSizeRel | Optimization is performed during the build process, with a focus on minimizing size, and no debug information file (.pdb) is generated. |

Therefore, you can perform the build for each mode by executing the following batch script.
- `Debug`
  ```
  Build_Debug.bat
  ```
- `Release`
  ```
  Build_Release.bat
  ```
- `RelWithDebInfo`
  ```
  Build_RelWithDebInfo.bat
  ```
- `MinSizeRel`
  ```
  Build_MinSizeRel.bat
  ```

## How to run game?

This project supports the ability to run the game without Visual Studio. The game execution script supports the following build modes: `Debug`, `Release`, `RelWithDebInfo`, and `MinSizeRel`, each with the following characteristics.

| mode | description |
|:---:|:---|
| Debug | Runs the project executable without optimization. |
| Release | Runs the project executable with optimization. |
| RelWithDebInfo | Runs the project executable with optimization and includes debug information files. |
| MinSizeRel | Runs the project executable with maximum optimization. |

Therefore, you can perform the build for each mode by executing the following batch script.
- `Debug`
  ```
  Run_Debug.bat
  ```
- `Release`
  ```
  Run_Release.bat
  ```
- `RelWithDebInfo`
  ```
  Run_RelWithDebInfo.bat
  ```
- `MinSizeRel`
  ```
  Run_MinSizeRel.bat
  ```

## How to package project?

This project supports generating an exe file that allows the project to be installed on the user's machine. To use this feature, NSIS (Nullsoft Scriptable Install System) must be installed, and its installation path must be registered in the environment variables. The packaging script supports the same modes as the build modes: Debug, Release, RelWithDebInfo, and MinSizeRel. Therefore, by running the following commands in CMD or PowerShell, you can obtain the package file for each mode.

> However, the solution must be built for this to work. Please refer to [this section](#how-to-build-solution) for the build process.

> You will not be able to use this feature if the NSIS path is not registered in the environment variables.

- `Debug`
  ```
  Package_Debug.bat
  ```
- `Release`
  ```
  Package_Release.bat
  ```
- `RelWithDebInfo`
  ```
  Package_RelWithDebInfo.bat
  ```
- `MinSizeRel`
  ```
  Package_MinSizeRel.bat
  ```

## Document

The documentation for this project can be found [here](https://choijione.github.io/FoxDash/).

## License

```
Copyright (c) 2024 ChoiJiOne

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

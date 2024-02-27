WarioSave
===============================================

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/savaughn/wariosave/blob/master/LICENSE.txt) [![GitHub release (latest by date)](https://img.shields.io/github/v/release/savaughn/wariosave)](https://github.com/savaughn/wariosave/releases) [![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/savaughn/wariosave/build-macos.yml?branch=master)](https://github.com/savaughn/wariosave/actions) [![GitHub issues](https://img.shields.io/github/issues/savaughn/wariosave)](https://github.com/savaughn/wariosave/issues) [![GitHub](https://img.shields.io/github/license/savaughn/wariosave)](https://github.com/savaughn/wariosave/blob/main/LICENSE) [![GitHub all releases](https://img.shields.io/github/downloads/savaughn/wariosave/total)](https://github.com/savaughn/wariosave/releases)

The WarioSave library is a C library designed to read the player's save data in Super Mario Land 3: Wario Land. It provides functions to initialize player save data and calculate the completion rate for each level in the game.

## Building the Library

The library can be built using the provided Makefile. The Makefile is set up to use the GCC compiler, but this can be changed by modifying the `CC` variable in the Makefile.

To build the library, navigate to the directory containing the Makefile and run the `make` command.

```bash
make
```

This will compile the source files in the `src` directory and output the resulting object files to the `build/release` directory.

## Using the Library

To use the library, include the header files in your C source files and link against the `libwariosave.a` library during the linking stage of your build process.

```c
#include "wariosave.h"
```

## Building the Example

The WarioSave library includes an example application that demonstrates how to use the library. The example application can be built using the provided Makefile in the root directory of the project.

### Prerequisites

- GCC compiler
- Make build automation tool

### Build Steps

1. Navigate to the root directory of the project where the Makefile is located.

2. Run the `make` command:

```bash
make
```

This command will compile the source files located in the `src` directory and output the resulting object files to the `build` directory. It will also generate dependency files in the `deps` directory.

The Makefile uses the GCC compiler (`gcc`) by default, but this can be changed by modifying the `CC` variable in the Makefile.

The `INCLUDES` variable in the Makefile specifies the directories where the compiler should look for header files. By default, it is set to look in the `include/` directory in the root of the project, and the `include/` directory in the `lib/` directory.

The resulting application will be named `wario-save`, as specified by the `APP_NAME` variable in the Makefile.

## Usage

Once the `wario-save` application is built, you can run it from the command line. The application takes a single argument, which is the path to the Wario game save file you want to analyze.

Here's an example of how to use the `wario-save` application:

```bash
./wario-save /path/to/your/savefile.sav
```

This command will load the specified save file, analyze the data, and print out the player's lives, hearts, total coins, game completion status, and the completion rate for each level.

## Acknowledgements

- [Wario Land Disassembly (wl)](https://github.com/Kak2X/wl): This project provided valuable insights and code that helped me understand the structure of Wario game save files.

## License

The WarioSave library is distributed under the MIT License. See the accompanying `LICENSE.txt` file for more details, or visit [http://opensource.org/licenses/MIT](http://opensource.org/licenses/MIT).
# DeepC

![DeepCAnglerfish](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/anglerfish_icon_medium_black.png)

Welcome to the DeepC, a suite of Deep compositing plugins for Foundry's Nuke. While I'm sure large studios have something similar to these tools, this open-source project makes them available to small and mid-size studios.

## TOC

- [Plugins](https://github.com/charlesangus/DeepC#plugins)
- [Why DeepC?](https://github.com/charlesangus/DeepC#why-deepc)
- [Get Them!](https://github.com/charlesangus/DeepC#get-them)
- [Build](https://github.com/charlesangus/DeepC#build)
- [Contributing](https://github.com/charlesangus/DeepC#contributing)

## Plugins

What are the tools offered in the DeepC toolkit? The [Wiki](https://github.com/charlesangus/DeepC/wiki) has a description for each and an overview of all available [plugins](https://github.com/charlesangus/DeepC/wiki#nodes). 

Also, head over to the [Examples](https://github.com/charlesangus/DeepC/wiki/Examples) page for some visuals.

You can read a quick description of some below.


- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCAdd.png)  [DeepCAdd](https://github.com/charlesangus/DeepC/wiki/DeepCAdd)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCAddChannels.png)  [DeepCAddChannels](https://github.com/charlesangus/DeepC/wiki/DeepCAddChannels)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCAdjustBBox.png)  [DeepCAdjustBBox](https://github.com/charlesangus/DeepC/wiki/DeepCAdjustBBox)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCClamp.png)  [DeepCClamp](https://github.com/charlesangus/DeepC/wiki/DeepCClamp)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCColorLookup.png)  [DeepCColorlookup](https://github.com/charlesangus/DeepC/wiki/DeepCColorlookup)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCConstant.png)  [DeepCConstant](https://github.com/charlesangus/DeepC/wiki/DeepCConstant)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCCopyBBox.png)  [DeepCCopyBBox](https://github.com/charlesangus/DeepC/wiki/DeepCCopyBBox)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCGamma.png)  [DeepCGamma](https://github.com/charlesangus/DeepC/wiki/DeepCGamma)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCGrade.png)  [DeepCGrade](https://github.com/charlesangus/DeepC/wiki/DeepCGrade)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCID.png)  [DeepCID](https://github.com/charlesangus/DeepC/wiki/DeepCID)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCHueShift.png)  [DeepCHueShift](https://github.com/charlesangus/DeepC/wiki/DeepCHueShift)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCInvert.png)  [DeepCInvert](https://github.com/charlesangus/DeepC/wiki/DeepCInvert)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCKeymix.png)  [DeepCKeymix](https://github.com/charlesangus/DeepC/wiki/DeepCKeymix)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCMatrix.png)  [DeepCMatrix](https://github.com/charlesangus/DeepC/wiki/DeepCMatrix)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCMultiply.png)  [DeepCMultiply](https://github.com/charlesangus/DeepC/wiki/DeepCMultiply)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCPMatte.png)  [DeepCPMatte](https://github.com/charlesangus/DeepC/wiki/DeepCPMatte)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCPNoise.png)  [DeepCPNoise](https://github.com/charlesangus/DeepC/wiki/DeepCPNoise)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCPosterize.png)  [DeepCPosterize](https://github.com/charlesangus/DeepC/wiki/DeepCPosterize)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCRemoveChannels.png)  [DeepCRemoveChannels](https://github.com/charlesangus/DeepC/wiki/DeepCRemoveChannels)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCSaturation.png)  [DeepCSaturation](https://github.com/charlesangus/DeepC/wiki/DeepCSaturation)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCShuffle.png)  [DeepCShuffle](https://github.com/charlesangus/DeepC/wiki/DeepCShuffle)
- ![](https://raw.githubusercontent.com/charlesangus/DeepC/master/icons/DeepCWorld.png)  [DeepCworld](https://github.com/charlesangus/DeepC/wiki/DeepCworld)

### DeepCBlink

Just a toy at the moment which performs a gain on the image, but demonstrates an approach to getting Blink working on Deep images. This approach works for kernels which need only the current pixel to operate. Experimental proof-of-concept, not really "useful" as a node.

## Why DeepC?

DeepC has several advantages over DeepExpression-based solutions to working with Deep data.

### Unique Features

World-position noise in Nuke has always been limited by Nuke's 3D noise algorithm. It's fine for a 2D image, but when working with 3D noise, your really need that fourth dimension so the noise can change over time. DeepCPNoise brings 4D noise to Nuke for the first time, by including and extending the open-source FastNoise library. 4D simplex noise in Nuke!

### Familiar Tools, Familiar Power

DeepCGrade works just like the regular Grade node. You can mask it with rotos from the side input (incredibly, this is not available in the standard toolset, or with the DeepExpression node). You can use Deep masks coming in from the top. You can easily configure the channels to process and those to use as masks, just as you normally would.

### Endlessly Extensible

The power of DeepC is limited only by the power of the NDK. Features like DeepCAddChannels and DeepCShuffle are only possible using the NDK.

### Speed

Now that basic functionality is implemented, the focus will be on accelerating the speed of the toolset.

## Get Them!

[Check the releases page for this repo](https://github.com/charlesangus/DeepC/releases) to get the compiled versions of the plugins. You can find builds for Windows, Linux and Mac. 
Currently the Mac build is not tested by us. If you face any issues please create a github issue provided as much information as possible for us to fix the problem.
For information about installing Nuke Plugins please refer to  [NDK Building & Installing Plug-ins](https://learn.foundry.com/nuke/developers/13.2/ndkdevguide/intro/pluginbuildinginstallation.html)

## Future Plans

### DeepCompress

Coming soon...

Much like how samples can be compressed in the renderer by merging samples closer than a certain threshold, this node will allow merging of samples in the Deep stream to cut down on processing time when the render is too heavy.

## Build

Thanks to Nathan Rusch (https://github.com/nrusch?tab=repositories) for contributing the CMake build setup which will form the basis for building DeepC going forward.

### Linux

To build compile DeepC you need the gcc (6) compiler and OpenGL/GLU libs installed. 

(On Cent OS/Redhat) Install prerequisites:

```bash
sudo yum install centos-release-scl
sudo yum install devtoolset-6
sudo yum install mesa-libGLU-devel
```

(On Ubuntu) Install prerequisites: 
```
apt-get install build-essential libgl1-mesa-dev libglu1-mesa-dev
```

Clone:

```bash
git clone --recurse-submodules https://github.com/charlesangus/DeepC
```

(On Cent OS/Redhat) Add to .bashrc on dev machine, or run before each build:

```bash
# enable devtoolset-6
source /opt/rh/devtoolset-6/enable
```

Then, from the DeepC dir:

```bash
mkdir build; cd build
cmake -D CMAKE_INSTALL_PREFIX="`pwd`/../install" ..
make -j X install
```

Where ```X``` is the number of cores you have available, so make can run parallelized. And, of course, update CMAKE_INSTALL_PREFIX to your preferred install location.


Note: additionally you can adjust the Nuke Version via -D Nuke_ROOT="<PATH_TO_NUKE_ROOT_FOLDER>"
Where ```<PATH_TO_NUKE_ROOT_FOLDER>``` is the path to the prefered nuke root like C:/Programs/Nuke12.2v2 or /usr/local/Nuke12.2v2

e.g.
```
cmake -D CMAKE_INSTALL_PREFIX="`pwd`/../install" -D Nuke_ROOT="/usr/local/Nuke13.1v1"
```

### Windows

On Windows you need Visual Studio (15) 2017 to compile the plugins.
You can use cmake (gui application-recommended) to create the project files for Visual Studio.
Note: make sure to use the x64 platform to compile the plugin. 

If you want to build the tool via command line (or us a batch script) use:
```
mkdir build
cd build
cmake -G "Visual Studio 15 2017" -A x64 .. -DCMAKE_INSTALL_PREFIX=install -B build
cmake --build build --config Release
cmake --install build
```

Note: additionally you can adjust the Nuke Version via -D Nuke_ROOT="<PATH_TO_NUKE_ROOT_FOLDER>"
Where ```<PATH_TO_NUKE_ROOT_FOLDER>``` is the path to the prefered nuke root like C:/Programs/Nuke12.2v2 or /usr/local/Nuke12.2v2

e.g.
```
mkdir build
cd build
cmake -G "Visual Studio 15 2017" -A x64 .. -D CMAKE_INSTALL_PREFIX=install -D Nuke_ROOT="C:/Program Files/Nuke13.1v1" -B build
cmake --build build --config Release
cmake --install build
```
### Mac

We provide binaries for MacOS build on macOS 11.7.1 using the AppleClang 13.0 compiler.
Unfortunatly we couldn't test the binaries as we used a build server to create them.
If you face any issues please let us know in the comments.

e.g.
```
mkdir build
cd build
cmake .. -D CMAKE_INSTALL_PREFIX=install -D Nuke_ROOT="/Applications/Nuke14.1v1/Nuke14.1v1.app/Contents/MacOS" -B build
cmake --build build --config Release
cmake --install build
```

## Batch Install
We provide an install batch script to compile DeepC for multiple versions of Nuke which works on linux and windows and 
creates the compiled plugins in the choosen install folder for every version. 
The script can be executed running batchInstall.sh, you can then enter the path to search for Nuke Versions e.g. /usr/local/ or C:/Program Files
Optionally an install path can be entered aswell. The script then runs and compiles the plugins (as far as the dependencies like compilers can be found).
Note: this is not tested on macOS yet.

## Examples
We created a repository which includes some example deep render scenes to try/test/use this plugin.<br>
In futur we will add nuke project files to show how the plugins work.<br>
https://github.com/charlesangus/DeepCExamples

## Contributing

Currently, DeepC is maintained by [me](https://github.com/charlesangus), [Jonas Sorgenfrei](https://github.com/jonassorgenfrei) and [Falk Hofmann](https://github.com/falkhofmann). I'd love your contributions, though!

If you'd like to contribute, please fork the project make a new feature branch for your contribution. Ideally, also let me know what you're up to so we don't duplicate efforts!

Once you're happy with your work, submit a pull request so I can merge your work back in.


### Conventions

- 4-space hard tabs
- private/protected variable names start with '_' (one underscore)
- variable/function names use lowerCamelCase

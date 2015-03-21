# The tool-chain #

Considering that the project is still in it's early stages of development, we decided not to design a robust make system for compiling the libraries.  This is because we may change the overall architecture of the frameworks source-tree and package structure as more shared systems are developed.  With that said, compiling the Ngen Framework is very simple, and can be accomplished in a matter of a few minutes.

## IDE ##
To begin, you will need two things, the CodeBlocks IDE and a supported C++ compiler.  The reason we choose CodeBlocks for development is because of it being cross-platform (Linux, Windows, and Mac), and because it can easily integrate almost all modern compilers into it's build system.

To download CodeBlocks, please see their download page [here](http://www.codeblocks.org/downloads) and download the package for your platform (without MingW if using Windows).

## GCC ##
While that is downloading or installing, you will need to download a supported compiler, which is simple because we currently only support GCC version 4.8 or higher.

### Windows ###
If your using Windows, you will need to download the latest TDM-GCC package for your processor architecture from [here](http://tdm-gcc.tdragon.net/download) and install it.

Make sure the TDM-GCC binaries are in your PATH environment variable after installation.

### Linux ###
If you are using Linux, `gcc` should be installed.  You may check the version by running:
```
~$: gcc --version
```
If version 4.8 or higher is not installed, please refer to your distributions package manager to acquire the latest version or upgrade the current `gcc` package.

## Subversion ##
We are using SVN for our code repositories, so you will need to download the latest subversion package for your platform.

### Windows ###
If using Windows, we suggest downloading TortoiseSVN from [here](http://tortoisesvn.net/downloads.html).  Its very clean and simple to use.

### Linux ###
Please refer to your distributions package manager to acquire the latest version or upgrade the current `svn` package.

### Checking out ###
To check out the latest stable sources, use the following command inside a new folder of your choosing (for Windows, I use `C:\\ngen\` and for Linux, I use `\home\ngen`):
```
svn checkout http://ngen.googlecode.com/svn/develop/v0.2 ngenframework/v0.2
```

# Build Instructions #

  1. Navigate to the top-level directory of the Ngen Framework source tree and open the `codeblocks.workspace` file.
  1. After the workspace is loaded, make sure the current `Build Target` says `Debug`, and click on `Build->Build Workspace`.
  1. After the compiler is finished (ignore any warnings for now), repeat step 2 using the `Release` build target.
  1. Change the active project by double clicking `UnitTest.Ngen` in the project navigation pane.
  1. Click `Build->Run` to execute the unit test program and evaluate the results.
  1. If all tests have passed, the framework was successfully constructed.

## Working Directory Instructions ##

  1. First create a new folder separate from the build folders.
  1. For each project in the workspace (except UnitTest projects), create a folder using a name of that project.  For instance, the `Ngen` project will have a `\Ngen\` folder and the `Ngen.Diagnostics` project will have an `\Ngen.Diagnostics\` folder.
  1. Now naviagate to each project you created a folder for, and copy the contents of the `\include\` folder (not the folder, its contents).  Paste the copied files into the new folder you created for the project.
  1. Finally, copy the `bin\` directory into the same location where you created the folders.

This will be the working directory, and directly resembles the folder structure of pre-built packages.

#### Finished ####

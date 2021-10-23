# Environment setup guide
This project was initially coded using CLion on Windows using the Mingw-w64 environment. However, during the development, the environment was switched to WSL. The code _probably_ is multiplatform and it should be possible to compile it under Windows. However, I do not give any warranties for that. Because of that, I will explain how to set up your environment using WSL under Windows and how to work with it using CLion and manual terminal compilation.

## WSL setup
The first step needed to do is installing and configuring the WSL under Windows. The configuration for WSL is similar to the config needed for native Linux env.

### Installing WSL2
To install WSL2 you need to first download desired Linux distro from the [Windows Store](https://aka.ms/wslstore) (there is not much of a choice sadly, however it is possible to run a custom distro if you want). I will assume that you have chosen Ubuntu as this is the most common distro and arguably most user-friendly (if you choose a different one then you probably know what you're doing).

After installing the Ubuntu "app" from MS Store you need to activate the WSL component for Windows. To do that open the "Turn Windows features on or off" and select the "Windows Subsystem for Linux" option. After that, the system restart is needed.

### Configuring the WSL
After the restart, you should be able to open the Ubuntu app from the menu start. During the first run, you will be asked to create a UNIX account. The username and password may be different than your Windows account. However, you need to remember it as your password will also be a `sudo` password.

After the account creation, update the system using the following command:
```
sudo apt update && sudo apt upgrade
```

After the upgrade you need to install the following things:
* cmake
* ninja-build
* gcc
* clang
* gdb
* valgrind
* build-essential.

Additionally, you need to set up an `sshd` server to allow CLion connection. _This is only needed if you plan to use CLion._

Both things can be done using the script provided by JetBrains. You can find it [here](https://github.com/JetBrains/clion-wsl/blob/master/ubuntu_setup_env.sh). To download and run it just run the following command:
```
wget https://raw.githubusercontent.com/JetBrains/clion-wsl/master/ubuntu_setup_env.sh && bash ubuntu_setup_env.sh
```

The `ssh` config done by this script is not the most secure one that's why by default only localhost connections are allowed (so the connections from Windows to WSL as well). If you plan to use `ssh` in the WSL more widely remember to check the `sshd` settings.

After the configuration, remember to restart the WSL. It may be done using the following command from `cmd` (**not the WSL terminal!**):
```
wsl.exe -t Ubuntu
```

## CLion setup
_You may skip this part if you prefer to compile the project from a terminal._

### Installing CLion
Installing the CLion is as easy as downloading the software from the [JetBrains site](https://www.JetBrains.com/clion/). Remember that students are eligible for a [free JetBrains license](https://www.JetBrains.com/community/education/#students) for all their products (but it can't be used for commercial purposes). You may also use the [JetBrains Toolbox](https://www.JetBrains.com/toolbox-app/) to install, manage and auto-update all your JetBrains IDEs.

### Configuring CLion
During the first time, the CLion starts it will ask for the license. Just log in with your JB account and you should be good to go. On the welcome screen select "Get from VCS" and clone the GitHub repo to the desired folder. If you don't have git installed on your Windows machine CLion will inform you and let you install it with just one press. You may clone the repo by providing the URL or by logging into your GitHub account and selecting the repo from the list.

### Configuring the project
When the project is ready and opened you will be asked if you trust the CMake file where you need to select that you trust it. After that, you will be asked to create a profile. You don't need to edit anything there.

If there is a problem with cmake just restart WSL and/or Windows machine and rebuild the CMake project.

The correct run/debug config should be created automatically and you should be able to compile and run the app using the run icon (or by pressing `Shift`+`F10`).

## Manual compilation
If you prefer to not use the IDE and stick to your favorite text editor here are the steps you need to do to compile the project under WSL (or any other Linux env).

The first step is to clone the project into the desired directory. You can do it using the following command:
```
git clone https://github.com/baatochan/TSPAlgorithmsComparison.git
```

_If the command is not working or you're set to use the SSH key in GitHub the correct path is available on the main site of the project on GitHub under the Code button._

Now you need to `cd` into the download directory and create a temporary directory for the build files. I suggest using the name `cmake-<SOMETHING>` as this type of directory is set to be ignored by `git`. So to create this dir just use `mkdir -p cmake-debug`.

Using the CMake is very easy and consists of two steps.

First, you need to load a project. To do that `cd` into the temporary directory and run `cmake ..`. The argument `..` is the parent directory (so the project's main directory) and it needs to be a directory with CMakeLists.txt file.

The second step is running a compiler and to do that you just run `cmake --build .`. This will try to compile the project. If you configured the env correctly (and installed all needed packages) everything should work smoothly. After the compilation, you need to run the created binary which name is the project name so in our case it's `./TSPAlgorithmsComparison`. Right now there is no fast way to compile and run the project with a single command so you may just use:
```
cmake --build . && ./TSPAlgorithmsComparison
```

## Local Windows compilation setup
This section is not yet done. I would be very grateful if you could provide here all the necessary steps for setting up the local Windows compilation (under CLion or not).

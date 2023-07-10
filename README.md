# Trova-Git

## Why?

We have all been there, we find a video or read an article about a cool
new technology or concept. Burning with passion we begin a project and spend the weekend on it
but after a while we forget about as either life or our motivation to finish it gets in the way.

## How it works

This tool will go through a file path specified by the user and will then print out
the name, path and the git status for every directory that is a git repository with uncommitted changes.

## Installation

To install and use this program clone the repo in your desired location. In the `src` folder make a `config.txt`, in it put the path where you would like the program to search for git repositories.
The path should be in a single line like this: `/home/user/Documents`  
Make sure to not use the `~` to specify the root directory as this will not be parsed correctly in the program.

The project uses Cmake to manage the build, you can run the `build.sh` file in the build directory and it will run cmake and make to build the executatble,
you can then run the executable `./trova` to run the program. However, I reccomend creating an alias in your
shell config, this would let you run the program from anywhere without needing to be in the project directory.  
Just specify the path where you have cloned the repo and replace the example path below while keeping the rest of the code the same.
In `zsh` it is done like this:

```shell
alias trova="cd ~/path/trova-git/build && ./trova && cd -"
```

I have plans in the future to make a binary you can add to your path to run it globally more easily.

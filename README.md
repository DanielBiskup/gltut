# Rubik's Cube
The code is based on an older version of [Chapter 3. OpenGL's Moving Triangle](https://paroj.github.io/gltut/Positioning/Tutorial%2003.html) of the [Learning Modern 3D Graphics Programming](https://paroj.github.io/gltut/index.html) by Jason L. McKesson. Originally I didn't use Git for this project, and only now (2018) decided to upload the code to GitHub. Before doing so, I removed most of the tutorials code which was not important tomy project.

Most (but not all) of the code in `rubiks-cube/src` was written by me. All the other code was not.

## How to build it
How to build the original tutorials is explained [here](https://paroj.github.io/gltut/Building%20the%20Tutorials.html). I will give the commands needed to compile what's important to the Rubik's Cube project.

You need [premake4](https://premake.github.io/) to build.
Download [premake4](https://premake.github.io/) for your operating system, which is a standalone executable. Add it to your path. [One way](https://askubuntu.com/a/60221/163596) to do this is to create a private bin directory for the user e.g. `/home/username/bin`, paste the premake4 executable into it. Then add the directory to the path by adding the following to your `~/.profile`:
```bash
#set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
PATH="$HOME/bin:$PATH"
fi
```

If you'd like to be able to execute `premake` instead `premake4` create a link:
```bash
ln -s /home/username/bin/premake4 /home/username/bin/premake
```
I added the [glsdk](https://bitbucket.org/alfonse/gltut/downloads/) which was mentioned in the original [build guide](https://paroj.github.io/gltut/Building%20the%20Tutorials.html) to the repository, because it makes the setup easier. In McKessons's tutorials, there was a Lua script to download those files.

Furthermore, I replaced the framework folder with an older version from my hard drive.

Clone the repository.

Assuming the current working directory is `rubiks-cube/glsdk/` run:
```bash
premake4 gmake
make
```

Then change directories to `rubiks-cube/glsdk/` and run the same two commands.
If the compilation was successful you can now run the program with:
`./RubicsCube/src/RubiksCubeD`

Since I'm not aware of a way to do out-of-tree builds with premake4 using the provided lua scripts, the working copy becomes a bit dirty after compilation. As a workaround I saved the output of `git status` to a `.gitignore` after running premake and make.

## Trivia
This project meant as a mere prototype, while the actual goal was to implement a Rubik's Cube on Sony's PlayStationVita. Unfortunately, due to copyright restrictions, I can't share the code for the PlayStationVita version. Furthermore sadly no footage of the far more elaborate PlayStationVita version does exists.

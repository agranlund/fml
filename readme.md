# FixMintLib
Removes FPU check from Atari 68020+ programs which were compiled with MintLib.

This program does not help if an application actually use floating point. It only removes the check for one which Mintlib automatically builds into 68020+ programs whether they need one or not.

This patcher can build for linux/macos and can be useful as part of the buildstep when compiling 68020-60 programs.

** Use it at your own risk and backup the original file if in doubt **

### Usage: "fml \<filename\>"
or just drag-and-drop a program onto fml.tos if running on Atari.


### Compile for Linux/MacOS:
Run "make" in the src folder

### Compile for Atari:
Run "make tos" in the src folder

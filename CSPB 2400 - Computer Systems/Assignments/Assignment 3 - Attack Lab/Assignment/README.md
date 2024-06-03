# lab3-attacklab

## Goals
This assignment involves generating a total of five attacks on two programs having different security vulnerabilities.  The directions for this lab are detailed but not difficult to follow. We give a brief overview of the lab below, but you should:

* [View the AttackLab tutorial video](https://www.youtube.com/watch?v=ogqpJj_YQGQ)
* Download the enclosed PDF and use it as you step through the lab

## Details

To get started on this lab:

> **Note:** It takes a few seconds to build and download your target, so please be patient.
* Edit file [./identikey](./identikey) with your University of Colorado identikey.
* Run `make` -- this should download an attack target and extract it into your directory.
* It that fails, talk to your TA and/or you can obtain your files by pointing your Web browser [the attack server](http://cs2400-applied.cs.colorado.edu:15513/). The server will build your files and return them to your browser in a tar file called `targetk.tar`, where *k* is the unique number of your target programs; save this in your git repo and then give the command `tar -xvf targetk.tar` to unpack it.

The files in `targetk` include:
* `README.txt`: A file describing the contents of the directory
* `ctarget`: An executable program vulnerable to code-injection attacks
* `rtarget`: An executable program vulnerable to return-oriented-programming attacks
* `cookie.txt`: An 8-digit hex code that you will use as a unique identifier in your attacks.
* `farm.c`: The source code of your target’s “gadget farm,” which you will use in generating return-oriented programming attacks.
* `hex2raw`: A utility to generate attack strings.

Make certain you add the files to your git repo using
* `git add targetk`
* `git commit -a -m'adding files'`
* `git push`

If you're still rusty with Git, ask the TA in your recitation.

## Important: your solution files

This lab has a [detailed writeup](attacklab.pdf). You need to produce five input files for the five phases shown in Figure 1 of the writeup. These files **must** be in your "target directory" and must be named
* ctarget.l1.txt
* ctarget.l2.txt
* ctarget.l3.txt
* **r**target.l2.txt
* **r**target.l3.txt

For example, if your target directory is `target4`, your solution
files should be named `target4/ctarget.l1.txt` and so on.

You need to follow this naming for us to correctly record that you completed
the first two phases by the mid-lab checkpoint date.

## Now what?

You should read the [full attacklab writeup](attacklab.pdf) and get going!

You can monitor the progress of the class by [looking at the attacklab scoreboard](http://cs2400-applied.cs.colorado.edu:15513/scoreboard).

# bvm
<b>NOTE: This repository is only for 1.1.2 to 1.1.9(I don't know if I can go reach this to 1.1.9) development as the 1.2 update will basically be different</b><br>
Basic Virtual Machine(BVM) is a Bytecode Virtual Machine Implementation
<br>
WIP (Development on Linux)

## Installation

**Install using the repo**
<br>
bash:
```
git clone https://github.com/GalaxianMonster/bvm.git
cd bvm
. ./install
cd ..
rm -r bvm
```

**Install from the release**
<br>
bash using the installer(needs internet) for bvm:
```
curl -L https://raw.githubusercontent.com/GalaxianMonster/bvm/master/installer.sh -o installer.sh
bash installer.sh <version here>
```
You can also download the release manually and
<br>
put it to /usr/local/include/bvmlib(Linux) or just add the directory to 
<br>
your compiler includes

## Download the repo
You can either download the source code
<br>
or use git
```bash
git clone https://github.com/GalaxianMonster/bvm.git
```

## Getting Started
**NOTE**: Download the repo first before following the instructions
<br>
Making a new session with the BVM example program:
```bash
cd <path for bvm>
. session
```

After creating a new session, run some testing:
```bash
bvm-example test/hello_world.txt.bbc
```

If you wanna debug:
```bash
export BVMDEBUG=1
```
then if you wanna turn it off
```bash
unset BVMDEBUG
```

## Other
<a href="RELEASE_INFO.md">Info for all releases</a>
<br>
<a href="RELEASE_DOWNLOAD.md">Release Downloads</a>
<br>
<a href="tutorials/Introduction.md">Tutorials</a>
<br>
<a href="LICENSE">License</a>

# bvm
Basic Virtual Machine(BVM) is a Bytecode Virtual Machine Implementation
<br>
Still in development(Linux)

## Installation
```
git clone https://github.com/GalaxianMonster/bvm.git
. bvm/install
rm -r bvm
```

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

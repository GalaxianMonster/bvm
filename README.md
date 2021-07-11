# Basic Virtual Machine
Basic Virtual Machine(BVM) is a Bytecode Virtual Machine Implementation

## Download
You can either sdownload the source code
<br>
or use git
```bash
cd <path for bvm here>
git clone https://github.com/GalaxianMonster/bvm.git
```

## Getting Started
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
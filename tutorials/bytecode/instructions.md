# Constructing Instructions
Now we know how the definitions of magic, opcodes, registers and immediate values
<br>
we can encode all of it into an Instruction

## Making a simple instruction
So the first half byte(4 bits) represents it's type either its an opcode or an operand

If it's an opcode then it will be **0000**
<br>
But if it's an operand then it will be **0001**

We will use the **0000** since we will gonna encode the opcode first

Now we move on to the 8 bits(1 byte)
<br>
So basically it represents the opcode no.
<br>
For now will use the exit opcode which is **00000001**
<br>

Next we have the 3 4 bits(3 half bytes)
So the 1st 4 bits represent the register 1 of the opcode
<br>
While the 2nd 4 bits represent the register 2 and the 3rd 4 bits represent the register 3
<br>
But the exit opcode doesn't require registers so we will leave them 0s
<br><br>
And finally we have our 1st Instruction
which is 
<br>
**000000000001000000000000**(binary)
<br>
**001000**(hex)
<br>
which is 3 bytes long
<br>
to execute this,
<br>
we need to pass it into the BVM example program
<br>
but first we need to put the magic(which is in <a href="magic.md">here</a>)
so get your hex/binary editors there and right both the magic and instruction we made
<br><br>
and finally we can run it:
```bash
. session
bvm <your bytecode file here>
```
<br>
and done :D
<br>
You could study the interface to learn how the BVM example program was made and how to execute the bytecode directly
<br>
If you wanna study how BVM executes the bytecode you can study it's internals

## The BVM instruction format
The opcode format:
<pre>
0000 00000000 0000 0000 0000
^    ^        ^    ^    ^
type opcode   reg1 reg2 reg3
     no.
</pre>
the type in the opcode is always **0000**
<br><br>
The operand/immval format:
<pre>
0001 00000000 0000
^    ^        ^
type immval   none
</pre>
The "none" in the operand/immval format is required since each memory address requires 8 bits or 1 byte in most computers.
<br>
Also, the "type" in the operand/immval format is
**0001**.
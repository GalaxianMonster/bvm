#!/bin/env python3
import os
CC = "gcc"
CFILES = """lib
internal/bytecode
internal/debug
internal/disasm
internal/eval
internal/instruction
internal/op
internal/program
internal/stack
internal/syscall
internal/vm
internal/vmem
internal/types"""
def remove_dir(str):
    splitted_str = str.split("/")
    splitted_str_len = splitted_str.__len__()
    return splitted_str[splitted_str_len-1]

def build_so():
    CFLAGS = "-shared -fPIC -Wall -O2"
    SO_FILE = "libbvm.so"
    CMD1 = CC +" "+ CFLAGS +" "+ "-o" +" "+ SO_FILE + " "
    CFILES_ARRAY = CFILES.split("\n")
    for i in range(CFILES_ARRAY.__len__()):
        CMD1 = CMD1 + CFILES_ARRAY[i] + ".c" + " "
    os.system(CMD1)
def build_a():
    CFLAGS = "-O2 -Wall"
    A_FILE = "libbvm.a"
    CMD1 = CC + " " + CFLAGS + " " + "-c "
    CFILES_ARRAY = CFILES.split("\n")
    for i in range(CFILES_ARRAY.__len__()):
        CMD1 = CMD1 + CFILES_ARRAY[i] + ".c" + " "
    CMD2 = "ar" +" "+ "rcs" +" "+ A_FILE +" "
    for i in range(CFILES_ARRAY.__len__()):
        CMD2 = CMD2 + remove_dir(CFILES_ARRAY[i]) + ".o" + " "
    os.system(CMD1)
    os.system(CMD2)
    CMD3 = "rm" +" "
    for i in range(CFILES_ARRAY.__len__()):
        CMD3 = CMD3 + remove_dir(CFILES_ARRAY[i]) + ".o" + " "
    os.system(CMD3)

build_so()
build_a()
#!/bin/bash

# Este script crea las multiples imagenes de prueba a partir de unas
# pocas imagenes base.

clear
make clean
make && bochs -q -rc bochsdbg

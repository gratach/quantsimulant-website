#!/bin/bash
emcc *.c -s ENVIRONMENT=web -s EXIT_RUNTIME=0 -s EXPORTED_FUNCTIONS='["_malloc","_main","_halli","_euler_2D_pot_vorbereiten","_iteration"]' -s 'EXPORTED_RUNTIME_METHODS=["HEAPU8", "HEAPF32", "cwrap","ccall"]' -s 'ALLOW_MEMORY_GROWTH'=1 -o main.js

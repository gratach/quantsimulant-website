#!/bin/bash
emcc *.c -s ENVIRONMENT=web -s EXIT_RUNTIME=0 -s EXPORTED_FUNCTIONS='["_malloc","_main","_iteration","_vorbereiten"]' -s 'EXPORTED_RUNTIME_METHODS=["HEAPU8", "HEAPF32", "cwrap","ccall"]' -o main.js

#!/bin/bash
emcc *.c -s ENVIRONMENT=web -s EXIT_RUNTIME=0 -s EXPORTED_FUNCTIONS='["_malloc","_main","_halli","_euler_1D_doppel_vorbereiten","_zeitschritt_aendern","_laplace_gewichtung_aendern","_iteration"]' -s 'EXPORTED_RUNTIME_METHODS=["HEAPU8", "HEAPF32", "cwrap","ccall"]' -o main.js

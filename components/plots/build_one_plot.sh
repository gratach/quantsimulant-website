#!/bin/bash
pwd
gnuplot -e "dateiname='${1}.tex'" "${1}.gnuplot"
pdflatex ${1}.tex
rm *inc-eps-converted-to.pdf
rm *.eps
rm *.log
rm *.tex
rm *.aux

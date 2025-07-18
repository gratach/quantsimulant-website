# The quantsimulant website

This website is hosted on [quantsimulant.debablo.de](https://quantsimulant.debablo.de).

## Build website

```bash
git clone https://github.com/gratach/quantsimulant-website.git
```

```bash
git clone https://github.com/gratach/quantsimulant.git
```

```bash
apt install gnuplot
```

 install pdflatex

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest # Tested with version 4.0.10
./emsdk activate latest
source ./emsdk_env.sh
cd ..
```

```bash
 python3 quantsimulant-website/create_website.py
```

 The website is then build in the dist directory (quantsimulant-website/dist)
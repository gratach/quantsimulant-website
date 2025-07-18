from pathlib import Path
from subprocess import Popen

plotpath = Path(__file__).resolve().parent
build_one_plot_path = plotpath / "build_one_plot.sh"

def buildPlotsRecursive(path):
    for child in path.iterdir():
        if child.is_dir():
            buildPlotsRecursive(child)
        elif child.is_file() and child.suffix == ".gnuplot":
            pass
            Popen(f"cd {path} && bash {build_one_plot_path} {child.stem}", shell = True).wait()

buildPlotsRecursive(plotpath)
            

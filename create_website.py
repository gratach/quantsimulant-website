from pathlib import Path
from shutil import rmtree, copytree, copyfile
from subprocess import Popen
rootpath = Path(__file__).parent.resolve()
rootrootpath = rootpath.parent.resolve()
wwwpath = rootpath / "www"
distpath = rootpath / "dist"
quantsimpath = rootrootpath / "quantsimulant"
quantsimwwwpath = quantsimpath / "www"
componentspath = rootpath / "components"
demospath = componentspath / "demos"
distdemospath = distpath / "demos"
plotspath = componentspath / "plots"
buildAllPlotsPath = plotspath / "build_all_plots.py"
referatPath = componentspath / "presentation"
referatPdfPath = referatPath / "referat.pdf"
distPresentationPath = distpath / "presentation"
distReferatPdfPath = distPresentationPath / "referat.pdf"

assert quantsimpath.is_dir()

wwwpath.mkdir(exist_ok=True)
if distpath.is_dir():
    rmtree(str(distpath))
distpath.mkdir(exist_ok=True)

Popen(f"python3 {buildAllPlotsPath}", shell=True).wait()
Popen(f"cd {referatPath} && pdflatex referat.tex", shell=True).wait()
distPresentationPath.mkdir(exist_ok=True)
copyfile(str(referatPdfPath), str(distReferatPdfPath))

for demoFile in demospath.iterdir():
    if demoFile.is_dir():
        print(f"Build {demoFile.name}")
        Popen(f"cd {demoFile} && bash makefile", shell=True).wait()
Popen(f"cd {quantsimpath} && bash erstelle", shell = True).wait()
copytree(str(quantsimwwwpath), str(distpath), dirs_exist_ok=True)
copytree(str(wwwpath), str(distpath), dirs_exist_ok=True)
copytree(str(demospath), str(distdemospath), dirs_exist_ok=True)

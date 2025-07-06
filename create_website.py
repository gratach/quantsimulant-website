from pathlib import Path
from shutil import rmtree, copytree
from subprocess import Popen
rootpath = Path(__file__).parent.resolve()
rootrootpath = rootpath.parent.resolve()
wwwpath = rootpath / "www"
distpath = rootpath / "dist"
quantsimpath = rootrootpath / "quantsimulant"
quantsimwwwpath = quantsimpath / "www"
demospath = wwwpath / "demos"

assert quantsimpath.is_dir()

wwwpath.mkdir(exist_ok=True)
if distpath.is_dir():
    rmtree(str(distpath))
distpath.mkdir(exist_ok=True)

for demoFile in demospath.iterdir():
    if demoFile.is_dir():
        print(f"Build {demoFile.name}")
        Popen(f"cd {demoFile} && bash makefile", shell=True).wait()
Popen(f"cd {quantsimpath} && bash erstelle", shell = True).wait()
copytree(str(quantsimwwwpath), str(distpath), dirs_exist_ok=True)
copytree(str(wwwpath), str(distpath), dirs_exist_ok=True)

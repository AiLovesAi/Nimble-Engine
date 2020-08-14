"""

 ReleaseBuilder.py
 Nimble Game Engine

 Created by Avery Aaron on 2020-08-10.
 Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>

 This program builds each program and library incrementally, then builds
 the installers for Windows, MacOSX, and Linux, which are ready to be
 distributed to github as a release.

"""


import os, sys
import platform
import glob
import shutil
from os import path

def main():
    system = platform.system()
    print("Building release for " + system + "\n\n")
    for folder in glob.glob("Nimble*/"):
        if ("Installer" in folder):
            continue
        os.system("py Builder.py " + folder)
        folder += "products/"
        #for file in os.listdir(folder);
            #shutil.copyfile(folder + file, "Nimble Game Engine Installer/src/" + system + "/assets/")
            # TODO Take product files and put them in the installer build directories; build installer?
    
    print("\n\nDone building release for " + platform.system())

if __name__ == "__main__":
    main()

# ReleaseBuilder.py

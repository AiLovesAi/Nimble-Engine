"""

 Builder.py
 Nimble Game Engine

 Created by Avery Aaron on 2020-08-11.
 Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>

 This program builds the CMakeLists.txt for the directory specified.

"""


import os, sys
import platform
import shutil
import glob
from os import path

def find_nth(haystack, needle, n):
    start = haystack.find(needle)
    while start >= 0 and n > 1:
        start = haystack.find(needle, start+len(needle))
        n -= 1
    return start

def main():
    # Setup
    sys.argv.pop(0)
    if (not sys.argv):
        print("Invalid arguments. Please specificy a directory to build")
        exit(1)
    
    originalDirectory = os.getcwd()
    directory = " ".join(sys.argv).replace('"', '')
    if (not directory.endswith("/")):
        directory += "/"
    if (not path.exists(directory)):
        print("Specified directory not found: " + directory)
        exit(1)
    
    directory += "build/"
    if (not path.exists(directory)):
        os.mkdir(directory)
        if (not path.exists(directory)):
            print("Could not create the directory " + directory)
            exit(1)
    os.chdir(directory)
    
    # Build by system
    system = platform.system()
    if (system == "Windows"):
        print("Building for Windows to " + directory)
        os.system("cmake -G \"MinGW Makefiles\" ..")
        os.system("mingw32-make.exe")
    elif (system == "Darwin"):
        print("Building for Mac OS X to " + directory)
        os.system("cmake -G \"Unix Makefiles\" ..")
        os.system("make")
    elif (system == "Linux"):
        print("Building for Linux to " + directory)
        os.system("cmake -G \"Unix Makefiles\" ..")
        os.system("make")
    else:
        print("OS not supported.")
        exit(1)
    
    print("Done building CMake for " + directory)
    os.chdir("..")
    
    # Organize
    if (not path.exists("products/")):
        os.mkdir("products/")
        if (not path.exists("products/")):
            print("Could not make directory products/. You will need to organize the output files yourself.")
            exit(1)
    
    for file in glob.glob("build/*Nimble*"):
        fileIsLibrary = (file.endswith(".dll") or file.endswith(".lib") or file.endswith(".so") or file.endswith(".a"))
        # If library, move
        if (fileIsLibrary):
            if (not path.exists(originalDirectory + "/lib/Nimble/")):
                os.mkdir(originalDirectory + "/lib/Nimble/")
                if (not path.exists(originalDirectory + "/lib/Nimble/")):
                    print("Could not make directory lib/Nimble/. You will need to organize the output files yourself.")
                    exit(1)
            
            fileNoVersion = file[len("build/"):]
            if ("_" in fileNoVersion):
                version = fileNoVersion[fileNoVersion.rindex("_"):find_nth(fileNoVersion, ".", 3)]
                fileNoVersion = fileNoVersion.replace(version, "")
            shutil.copy(file, originalDirectory + "/lib/Nimble/" + fileNoVersion)
        else:
            if (not path.exists(originalDirectory + "/products/")):
                os.mkdir(originalDirectory + "/products/")
                if (not path.exists(originalDirectory + "/products/")):
                    print("Could not make directory products/. You will need to organize the output files yourself.")
                    exit(1)
            
            fileNoVersion = file[len("build/"):]
            if ("_" in fileNoVersion):
                version = fileNoVersion[fileNoVersion.rindex("_"):find_nth(fileNoVersion, ".", 3)]
                fileNoVersion = fileNoVersion.replace(version, "")
            shutil.copy(file, originalDirectory + "/products/" + fileNoVersion)
        
        shutil.move(file, "products/" + file[len("build/"):])
    print("Moved all output files to " + directory[:-len("build/")] + "products/ and lib/Nimble/")
    
    os.chdir(originalDirectory)

if __name__ == "__main__":
    main()

# Builder.py

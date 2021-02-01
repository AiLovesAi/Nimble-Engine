"""

 Builder.py
 Nimble Engine

 Created by Avery Aaron on 2020-08-11.
 Copyright (C) 2020-2021 Avery Aaron <business.AiLovesAi@gmail.com>

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
        print("Invalid arguments. Please specificy a directory to build.")
        exit(1)
    
    originalDirectory = os.getcwd().replace("\\", "/")
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
    else:
        print("Building for Linux to " + directory)
        os.system("cmake -G \"Unix Makefiles\" ..")
        os.system("make")
    
    print("Done building CMake for " + directory)
    os.chdir("..")
    
    # Organize
    if (not path.exists("products/")):
        os.mkdir("products/")
        if (not path.exists("products/")):
            print("Could not make directory products/. You will need to organize the output files yourself.")
            exit(1)
    
    for file in glob.glob("build/*Nimble*"):
        file = file.replace("\\", "/")
        fileIsLibrary = (file.endswith(".dll") or file.endswith(".lib") or file.endswith(".so") or file.endswith(".a") or file.endswith(".dylib"))
        fileIsSharedLibrary = (file.endswith(".dll") or file.endswith(".so") or file.endswith(".dylib"))
        # If library, move
        if (not path.exists(originalDirectory + "/products/")):
            os.mkdir(originalDirectory + "/products/")
            if (not path.exists(originalDirectory + "/products/")):
                print("Could not make directory products/. You will need to organize the output files yourself.")
                exit(1)
        if (not path.exists(originalDirectory + "/lib/Nimble/")):
            os.makedirs(originalDirectory + "/lib/Nimble/", exist_ok=True)
            if (not path.exists(originalDirectory + "/lib/Nimble/")):
                print("Could not make directory lib/Nimble/. You will need to organize the output files yourself.")
                exit(1)
        if (fileIsLibrary):
            fileNoVersion = file[len("build/"):]
            if ("_" in fileNoVersion):
                version = fileNoVersion[fileNoVersion.rindex("_"):find_nth(fileNoVersion, ".", 3)]
                fileNoVersion = fileNoVersion.replace(version, "")
            shutil.copy(file, originalDirectory + "/lib/Nimble/" + fileNoVersion)
            if (fileIsSharedLibrary):
                shutil.copy(file, originalDirectory + "/products/" + fileNoVersion)
        else:
            
            fileNoVersion = file[len("build/"):]
            if ("_" in fileNoVersion):
                version = fileNoVersion[fileNoVersion.rindex("_"):find_nth(fileNoVersion, ".", 3)]
                fileNoVersion = fileNoVersion.replace(version, "")
            shutil.copy(file, originalDirectory + "/products/" + fileNoVersion)
        
        shutil.copy(file, "products/" + file[len("build/"):])
    print("Copied all output files to " + directory[:-len("build/")] + "products/ and lib/Nimble/")

    # Move include files
    for file in glob.glob("include/**/*.h", recursive=True):
        file = file.replace("\\", "/")
        if (not path.exists(originalDirectory + "/lib/Nimble/include/")):
            os.makedirs(originalDirectory + "/lib/Nimble/include/", exist_ok=True)
            if (not path.exists(originalDirectory + "/lib/Nimble/include/")):
                print("Could not make directory lib/Nimble/include/. You will need to organize the include files yourself.")
                exit(1)
        
        if ("/" in file[len("include/"):]):
            fileDir = originalDirectory + "/lib/Nimble/include/" + file[len("include/"):-(len(file) - file.rindex("/"))] + "/"
            if (not path.exists(fileDir)):
                os.makedirs(fileDir, exist_ok=True)
                if (not path.exists(fileDir)):
                    print("Could not make directory " + fileDir + ". You will need to organize the include files yourself.")
                    exit(1)
                
        shutil.copy(file, originalDirectory + "/lib/Nimble/include/" + file[len("include/"):])
    print("Copied all include files to lib/Nimble/include/")
    
    os.chdir(originalDirectory)

if __name__ == "__main__":
    main()

# Builder.py

"""

  LicenseGenerator.py
  Nimble Game Engine

  Created by Avery Aaron on 2020-08-08.
  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>

  This program makes the NimbleLicense.c file from LICENSE.md that gets
  included in every header file, and therefor all compiled executables in plain text.

"""


import os, sys
from os import path
from datetime import datetime

def main():
    print("Generating license file from LICENSE.md...")
    licenseData = "/*\n\
*  NimbleLicense.c\n\
*  Nimble Game Engine\n\
*\n\
*  Created automatically by LicenseGenerator.py on " + str(datetime.date(datetime.now())) + ".\n\
*  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>\n\
*\n\
*/\n\n\
const char LICENSE_md[] = \"\\n\\\n"
    with open("LICENSE.md", 'r') as fp:
        if (not fp):
            print("Could not open LICENSE.md")
            exit(1)
        line = str(fp.readline()).replace('"', '\\"')
        while line:
            licenseData += line[:-1] + "\\n\\\n"
            line = str(fp.readline()).replace('"', '\\"')
    
    licenseData += "\";\n\n\n// NimbleLicense.c\n"
    
    if (not path.exists("License/")):
        os.mkdir("License/")
        if (not path.exists("License/")):
            print("Could not create directory License/")
            exit(1)
    
    with open("License/NimbleLicense.c", 'w') as fp:
        if (not fp):
            print("Could not open License/NimbleLicense.c")
            exit(1)
        fp.write(licenseData)
    
    print("Successfully generated License/NimbleLicense.c")
    exit(0)

if __name__ == "__main__":
    main()

# LicenseGenerator.py

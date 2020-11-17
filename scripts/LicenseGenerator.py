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
    date = str(datetime.date(datetime.now()))
    directory = os.getcwd()
    if (directory.endswith("scripts")):
        directory = directory[:len(directory) - len("scripts")]
    if ((not directory.endswith("/")) or (not directory.endswith("\\"))):
        directory += "/"
    print(directory)
    licenseData = "/*\n\
 * NimbleLicense.c\n\
 * Nimble Game Engine\n\
 *\n\
 * Created automatically by LicenseGenerator.py on " + date + ".\n\
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>\n\
 *\n\
 */\n\n\
/**\n\
 * @file NimbleLicense.c\n\
 * @author Avery Aaron\n\
 * @copyright\n\
 * @parblock\n\
 * The MIT License (MIT)\n\
 * Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>\n\
 *\n\
 * Permission is hereby granted, free of charge, to any person obtaining a copy\n\
 * of this software and associated documentation files (the \"Software\"), to deal\n\
 * in the Software without restriction, including without limitation the rights\n\
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n\
 * copies of the Software, and to permit persons to whom the Software is\n\
 * furnished to do so, subject to the following conditions:\n\
 *\n\
 * The above copyright notice and this permission notice shall be included in\n\
 * all copies or substantial portions of the Software.\n\
 *\n\
 * THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n\
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n\
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n\
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n\
 * SOFTWARE.\n\
 * @endparblock\n\
 * @date 2020-01-30\n\
 * \n\
 * @brief Defines the value of #LICENSE_md, which gets compiled into the binaries.\n\
 */\n\n\n\
/**\n\
 * @brief The license that gets compiled into the binaries.\n\
 */\n\
const char LICENSE_md[] = \"\\nNimble Game Engine License:\"\\\n\""
    with open(directory + "LICENSE.md", 'r') as fp:
        if (not fp):
            print("Could not open LICENSE.md")
            exit(1)
        line = str(fp.readline()).replace('"', '\\"')
        while line:
            licenseData += line[:-1] + "\\n\"\\\n\""
            line = str(fp.readline()).replace('"', '\\"')
    
    licenseData += "\";\n\n\n// NimbleLicense.c\n"
    
    if (not path.exists(directory + "Nimble Game Engine Library/src/")):
        os.mkdir(directory + "Nimble Game Engine Library/src/")
        if (not path.exists(directory + "Nimble Game Engine Library/src/")):
            print("Could not create directory Nimble Game Engine Library/src/")
            exit(1)
    
    with open(directory + "Nimble Game Engine Library/src/NimbleLicense.c", 'w') as fp:
        if (not fp):
            print("Could not open Nimble Game Engine Library/src/NimbleLicense.c")
            exit(1)
        fp.write(licenseData)
    
    print("Successfully generated Nimble Game Engine Library/src/NimbleLicense.c")
    exit(0)

if __name__ == "__main__":
    main()

# LicenseGenerator.py

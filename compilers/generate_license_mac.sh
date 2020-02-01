#!/bin/sh

ls | grep "compilers" > /dev/null
exitCode=$?

case $exitCode in
  0)
    cd "compilers/"
  ;;
  1)
  ;;
  2)
    echo "Grep failed to run, unable to generate NimbleLicense.c file."
    exit
  ;;
esac

echo "/*\n\
*  NimbleLicense.c\n\
*  Nimble Game Engine\n\
*\n\
*  Created by Avery Aaron on 1/30/20.\n\
*  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>\n\
*\n\
*  This program is free software: you can redistribute it and/or modify\n\
*  it under the terms of the GNU General Public License as published by\n\
*  the Free Software Foundation, either version 3 of the License, or\n\
*  (at your option) any later version.\n\
*\n\
*  This program is distributed in the hope that it will be useful,\n\
*  but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
*  GNU General Public License for more details.\n\
*\n\
*  You should have received a copy of the GNU General Public License\n\
*  along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\
*\n\
*/\n\n\
const char LICENSE_md[] = \"\\\\n\\" > ../src/NimbleLicense.c

cat ../LICENSE.md | sed 's/"/\\"/g; s/$/\\n\\/g' >> ../src/NimbleLicense.c

echo "\";\n\n\n// NimbleLicense.c" >> ../src/NimbleLicense.c

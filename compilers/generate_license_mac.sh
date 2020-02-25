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
*/\n\n\
const char LICENSE_md[] = \"\\\\n\\" > ../src/NimbleLicense.c

cat ../LICENSE.md | sed 's/"/\\"/g; s/$/\\n\\/g' >> ../src/NimbleLicense.c

echo "\";\n\n\n// NimbleLicense.c" >> ../src/NimbleLicense.c

#!/bin/sh

PRODUCT_NAME="Nimble Example Mac"


gcc-9 -v \
-march=x86-64 -mtune=intel \
-Ofast -Os \
\
-Wall \
-Wno-deprecated \
\
-I/usr/local/include \
-L/usr/local/Cellar \
\
-framework OpenAL \
-framework OpenGL \
/usr/local/Cellar/glew/2.1.0/lib/libGLEW.dylib \
/usr/local/Cellar/glfw/3.3/lib/libglfw.dylib \
/usr/local/Cellar/cglm/0.5.4/lib/libcglm.a \
-lm \
\
../*.c -o "../products/$PRODUCT_NAME" \
2>&1 \
| grep --color "\^|warning:\|error:"

exitCode=$?
case $exitCode in
  0)
    echo "Compile had warnings and/or errors."
  ;;
  1)
    echo "Compile succeeded."
  ;;
  2)
    echo "Grep failed to run, compilation status unknown."
  ;;
esac

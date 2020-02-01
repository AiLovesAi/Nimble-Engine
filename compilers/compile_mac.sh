#!/bin/sh

PRODUCT_NAME="Nimble Example Mac"



ls | grep "compilers" > /dev/null
exitCode=$?

case $exitCode in
  0)
    cd "compilers/"
  ;;
  1)
  ;;
  2)
    echo "Grep failed to run, compiler not able to run."
    exit
  ;;
esac

./generate_license_mac.sh

gcc-9 -v \
-march=x86-64 -mtune=intel \
-Ofast -Os \
\
-Wall \
\
-I/usr/local/include \
-L/usr/local/Cellar \
\
-framework OpenGL \
/usr/local/Cellar/glew/2.1.0_1/lib/libglew.dylib \
/usr/local/Cellar/glfw/3.3.1/lib/libglfw.dylib \
/usr/local/Cellar/vulkan/libvulkan.dylib \
/usr/local/Cellar/cglm/0.6.2/lib/libcglm.a \
/usr/local/Cellar/libsoundio/2.0.0/lib/libsoundio.a \
-lm \
\
../src/*.c -o "../products/$PRODUCT_NAME" \
2>&1 \
| grep -B 10 --color "\^|warning:\|error:"

exitCode=$?
case $exitCode in
  0)
    echo "Compile had warnings and/or errors."
    exit
  ;;
  1)
    echo "Compile succeeded."
  ;;
  2)
    echo "Grep failed to run, compilation status unknown."
    exit
  ;;
esac

codesign -f -s "Mac Developer: averyaaron@me.com" "../products/$PRODUCT_NAME"

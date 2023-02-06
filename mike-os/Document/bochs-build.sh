export CC=gcc
export CXX="g++"
export CFLAGS="-Wall -O2 -fomit-frame-pointer -pipe"
export CXXFLAGS="$CFLAGS"

(./configure --enable-smp \
              --enable-cpu-level=6 \
              --enable-all-optimizations \
              --enable-x86-64 \
              --enable-pci \
              --enable-vmx \
              --enable-debugger \
              --enable-disasm \
              --enable-debugger-gui \
              --enable-logging \
              --enable-fpu \
              --enable-3dnow \
              --enable-sb16=dummy \
              --enable-cdrom \
              --enable-x86-debugger \
              --enable-iodebug \
              --disable-plugins \
              --disable-docbook \
              --with-x --with-x11 --with-term --with-sdl2) || exit

make && make install

# website: https://bochs.sourceforge.io/getcurrent.html
# https://sourceforge.net/projects/bochs/files/bochs/2.7
# https://sourceforge.net/projects/bochs/files/bochs
# Download source code your self
# mabey install sdl2 error 

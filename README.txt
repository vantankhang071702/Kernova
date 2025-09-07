🛠 Building an i686-elf Cross Compiler (for OS Dev)

This guide explains how to build a freestanding cross compiler (i686-elf-gcc) and run your OS inside QEMU.
We’ll use Ubuntu (e.g., WSL) as the build environment.

📦 Requirements

Install the required packages:

sudo apt update
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo wget \
                 qemu-system-x86 mtools xorriso -y


Compiler toolchain → build-essential, bison, flex, gmp, mpc, mpfr, texinfo

Download tool → wget

Emulator → qemu-system-x86 (to test your OS)

ISO tools → mtools, xorriso (for creating bootable ISOs)

🔧 1. Build the cross compiler

Follow these steps once to install i686-elf-gcc into /usr/local/i686elf.

<details> <summary>Full steps</summary>
Create workspace
mkdir -p ~/cross/src
cd ~/cross/src

Download sources
wget https://ftp.gnu.org/gnu/binutils/binutils-2.40.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz

tar -xvzf binutils-2.40.tar.gz
tar -xvzf gcc-13.2.0.tar.gz

Set environment
export PREFIX="/usr/local/i686elf"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"


👉 Add export PATH="$PREFIX/bin:$PATH" to your ~/.bashrc for persistence.

Build Binutils
mkdir build-binutils
cd build-binutils
../binutils-2.40/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
sudo make install
cd ..

Build GCC
mkdir build-gcc
cd build-gcc
../gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
sudo make install-gcc
sudo make install-target-libgcc
cd ..

Verify
which i686-elf-gcc
i686-elf-gcc --version

</details>
🚀 2. Build & Run the OS

Your project uses three scripts to automate the process:

🔨 build.sh

Compiles the kernel into object files and binaries using i686-elf-gcc and i686-elf-ld.

📦 iso.sh

Packages the compiled kernel into a bootable ISO using grub-mkrescue (requires xorriso and mtools).

▶️ qemu.sh

Runs the ISO in QEMU to emulate the OS.

Usage

Run the scripts in order:

./build.sh   # 1. Build the kernel
./iso.sh     # 2. Create bootable ISO
./qemu.sh    # 3. Run OS in QEMU

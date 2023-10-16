#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/rockos.kernel isodir/boot/rockos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "rockos" {
	multiboot /boot/rockos.kernel
}
EOF
grub-mkrescue -o rockos.iso isodir

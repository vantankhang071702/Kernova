#!/bin/bash

echo "[1/3] Building kernel..."
sh build.sh

echo "[2/3] Creating ISO..."
sh iso.sh

echo "[3/3] Running in QEMU..."
sh qemu.sh

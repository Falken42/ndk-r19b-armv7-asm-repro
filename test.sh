#!/bin/bash
set -e

NDK=$HOME/dev/android-ndk-r19b

$NDK/ndk-build -B -j8 V=1

#! /usr/bin/env bash
set -e

BUILD_DIR=$(dirname "$(readlink -f "$0")")

cd "$BUILD_DIR"
make APP=brewblox PLATFORM=gcc

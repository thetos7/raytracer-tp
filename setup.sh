#!/bin/sh
BUILD_DIR='build'

rm -rf "$BUILD_DIR" \
    && cmake -B "$BUILD_DIR" 1>&2 \
    && echo "$BUILD_DIR"

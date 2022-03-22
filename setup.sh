#!/bin/sh
BUILD_DIR='build'

rm -rf "$BUILD_DIR" \
    && cmake -B "$BUILD_DIR" \
    && echo "$BUILD_DIR"

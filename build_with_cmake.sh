#!/bin/bash

cd /code

make clean

make generate-buildsystem

make build-cmake

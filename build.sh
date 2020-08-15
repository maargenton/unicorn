#! /bin/bash

make clean
make

if [[ ! -z "${CROSS_TRIPLE}" ]]; then
    mkdir -p build/lib/${CROSS_TRIPLE}
    cp libunicorn.a build/lib/${CROSS_TRIPLE}

else
    mkdir -p build/lib
    cp libunicorn.a build/lib
fi

if [[ ! -d build/include/unicorn ]]; then
    mkdir -p build/include
    cp -r include/unicorn build/include
fi

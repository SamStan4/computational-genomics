#!/usr/bin/env bash
set -e

executable="./bin/app"

cd ./..

make clean
make

if [ -x "$executable" ]; then
    ./bin/app
else
    echo "cannot run app"
fi

exit 0
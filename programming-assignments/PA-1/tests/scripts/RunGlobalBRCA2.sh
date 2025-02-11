#!/usr/bin/env bash
set -e

cd "$(dirname "$0")/../.."

# Define paths
executablePath="./bin/app"
fastaPath="./tests/input/Human-Mouse-BRCA2-cds.fasta"
alignmentFlag="0"
configPath="./tests/config/parameters.config"

make clean
make

if [ -x "$executablePath" ]; then
    "$executablePath" "$fastaPath" "$alignmentFlag" "$configPath"
else
    echo "cannot run app"
fi

exit 0
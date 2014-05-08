#!/bin/bash

echo "[gengine:tests] Running all tests ..."

for dir in `ls`;
do
    test -d "$dir" || continue
    cd $dir
    echo "[gengine:tests] Running <$dir> ..."
    gengine-run -d
    cd ..
done

#! /usr/bin/env bash

MY_DIR=$(dirname "$(readlink -f "$0")")
shopt -s globstar

if python -m compiledb make $MAKE_ARGS $@; then
    rm -f "$MY_DIR/compile_commands.json"
    pushd "$MY_DIR" > /dev/null
    cat ./**/compile_commands.json > compile_commands.json
    sed -i -e ':a;N;$!ba;s/\]\n\n\[/,/g' compile_commands.json
    chmod 777 compile_commands.json
    popd > /dev/null
    rm -f "compile_commands.json"
fi
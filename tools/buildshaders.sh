#!/bin/bash

# note: if you don't want to install the whole vulkan sdk, just download
# the latest glslangValidator build and place it in the directory where
# the script is, then run the script: it should work like a champ.
# https://github.com/KhronosGroup/glslang/releases/tag/master-tot
PATH=$PATH:"$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

shift $((OPTIND - 1))
work_dir="$@"
build_dir="build/shaders"

if [[ -z "$work_dir" ]] || [[ ! -d "$work_dir" ]]
then
    echo "$0: fatal: invalid directory $work_dir"
    exit 1
fi

sources=$(find "$work_dir" -name *.hlsl)
if [[ -z "$sources" ]]
then
    echo "$0: fatal: no shaders found in $work_dir/src/"
    exit 1
fi

mkdir -p "$build_dir"

for src in $sources
do
    xspv=$(basename "$src" .hlsl)
    glslangValidator -V --hlsl-dx9-compatible -e main -o "$build_dir/$xspv.spv" "$src"
    spirv-cross "$build_dir/$xspv.spv" > "$build_dir/$xspv.glsl"
    glslangValidator --quiet -G -e main -o "$work_dir/$xspv.spv" "$build_dir/$xspv.glsl"
done
exit 0

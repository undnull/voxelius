#!/bin/bash

# note: if you don't want to install the whole vulkan sdk, just download
# the latest glslangValidator build and place it in the directory where
# the script is, then run the script: it should work like a champ.
# https://github.com/KhronosGroup/glslang/releases/tag/master-tot
PATH=$PATH:"$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

shift $((OPTIND - 1))
work_dir="$@"

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

for src in $sources
do
    xspv=$(basename "$src" .hlsl)
    glslangValidator -G4.5 --hlsl-dx9-compatible -e main -o "$work_dir/$xspv.spv" "$src"
done
exit 0

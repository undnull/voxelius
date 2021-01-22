#!/bin/bash

# note: if you don't want to install the whole vulkan sdk, just download
# the latest glslc build and place it in the directory where
# the script is, then run the script: it should work like a champ.
# https://github.com/google/shaderc/blob/main/downloads.md
PATH=$PATH:"$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

shift $((OPTIND - 1))
work_dir="$@"

if [[ -z "$work_dir" ]] || [[ ! -d "$work_dir" ]]
then
    echo "$0: fatal: invalid directory $work_dir"
    exit 1
fi

sources=$(find "$work_dir/src" -name *.glsl)
if [[ -z "$sources" ]]
then
    echo "$0: fatal: no shaders found in $work_dir/src/"
    exit 1
fi

for src in $sources
do
    xspv=$(basename "$src" .glsl)
    if [[ "$xspv" == *"_vs" ]]
    then
        stage="vert"
        ext="vspv"
    elif [[ "$xspv" == *"_fs" ]]
    then
        stage="frag"
        ext="fspv"
    else
        echo "$0: warning: ignoring $xspv"
        continue
    fi
    glslc -o "$work_dir/${xspv%_*}.$ext" --target-env=opengl -fshader-stage="$stage" "$src"
done
exit 0

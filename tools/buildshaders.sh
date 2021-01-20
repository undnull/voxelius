#!/bin/bash
# buildshaders.sh
# Created: 2021-01-20, 13:10:00.
# Copyright (C) 2021, Kirill GPRB.
#

# This is optional, you may manually download a newer GLSLC build there.
PATH=$PATH:"$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../tools/"

target_env="opengl4.5"
output_dir="./out"
run_linker=false

while getopts "E:o:h" option
do
    if [[ "$option" = "E" ]]
    then
        target_env="$OPTARG"
        continue
    fi

    if [[ "$option" = "o" ]]
    then
        output_dir="$OPTARG"
        continue
    fi

    >&2 echo "usage: $0 [options] <input_dir>"
    >&2 echo "options:"
    >&2 echo "    -E <env>    : set the target environment [default: opengl4.5]"
    >&2 echo "    -o <output> : set the output directory [default: ./out]"
    >&2 echo "    -h          : print this message and exit"
    exit 1
done

shift $((OPTIND - 1))
input_dir="$@"

if [[ -z "$input_dir" ]]
then
    >&2 echo "$0: input directory name required."
    exit 1
fi

if [[ -z "$output_dir" ]]
then
    >&2 echo "$0: invalid output directory name."
    exit 1
fi

if [[ ! -d "$input_dir" ]]
then
    >&2 echo "$0: $input_dir is not a directory or doesn't exist."
    exit 1
fi

mkdir -p "$output_dir"

vert_srcs=$(find "$input_dir" -maxdepth 1 -iname *.vert)
if [[ -z "$vert_srcs" ]]
then
    >&2 echo ">> No vertex shaders found in $input_dir"
else
    >&2 echo ">> Building vertex shaders"
    for vert_src in $vert_srcs
    do
        filename="$(basename $vert_src)"
        vert_spv="$output_dir/${filename%.*}.vspv"
        >&2 echo ">>> $vert_src -> $vert_spv"
        glslc "--target-env=$target_env" "-fshader-stage=vert" "-o" "$vert_spv" "$vert_src"
    done
fi

frag_srcs=$(find "$input_dir" -maxdepth 1 -iname *.frag)
if [[ -z "$frag_srcs" ]]
then
    >&2 echo ">> No fragment shaders found in $input_dir"
else
    >&2 echo ">> Building fragment shaders"
    for frag_src in $frag_srcs
    do
        filename="$(basename $frag_src)"
        frag_spv="$output_dir/${filename%.*}.fspv"
        >&2 echo ">>> $frag_src -> $frag_spv"
        glslc "--target-env=$target_env" "-fshader-stage=frag" "-o" "$frag_spv" "$frag_src"
    done
fi

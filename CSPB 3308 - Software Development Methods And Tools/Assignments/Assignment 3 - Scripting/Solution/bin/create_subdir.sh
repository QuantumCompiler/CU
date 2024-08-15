#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <year> <game_id>"
    exit 1
fi

year=$1
game_id=$2

if ! [[ "$year" =~ ^[0-9]{4}$ ]] || ! [[ "$game_id" =~ ^[0-9]+$ ]]; then
    echo "Error: Year and game ID must be numeric. Year must be 4 digits."
    exit 1
fi

current_year=$(date +%Y)

if (( year < 1984 || year > current_year )); then
    echo "Error: Year must be between 1984 and $current_year."
    exit 1
fi

cwd=$(pwd)
base_dir="${cwd%/bin}"

if [ ! -d "$base_dir/Data" ]; then
    echo "Error: Data directory does not exist in the current working directory."
    exit 1
fi

subdir="$base_dir/Data/$year/$game_id"

if [ ! -d "$subdir" ]; then
    mkdir -p "$subdir"
    echo "Created directory: $subdir"
else
    echo "Directory already exists: $subdir"
fi
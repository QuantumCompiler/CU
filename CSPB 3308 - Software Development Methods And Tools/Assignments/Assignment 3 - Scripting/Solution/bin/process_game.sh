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

./create_subdir.sh "$year" "$game_id"
if [ $? -ne 0 ]; then
    echo "Error: Failed to create subdirectories."
    exit 1
fi

cwd=$(pwd)
base_dir="${cwd%/bin}"

subdir="$base_dir/Data/$year/$game_id"
url="http://www.j-archive.com/showgame.php?game_id=$game_id"
html_file="$subdir/game_$game_id.html"

if ! wget -q -O "$html_file" "$url"; then
    echo "Error: Failed to download HTML file from $url"
    exit 1
fi

echo "Downloaded HTML file to $html_file"

extract_data.sh "$html_file"

mv "categories.txt" "$subdir"
mv "clues_DJ.txt" "$subdir"
mv "clues_FJ.txt" "$subdir"
mv "clues_J.txt" "$subdir"
mv "clues.txt" "$subdir"

if [ $? -ne 0 ]; then
    echo "Error: Failed to extract data from $html_file"
    exit 1
fi

echo "Data processed completely."
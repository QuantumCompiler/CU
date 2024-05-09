cd ..

find . -type f -name '*.atfi' -exec rm {} +
find . -type f -name '*.aux' -exec rm {} +
find . -type f -name '*.log' -exec rm {} +
find . -type f -name '*.out' -exec rm {} +
find . -type f -name '*.ptc' -exec rm {} +

echo
echo "LaTeX excess deleted successfully from all directories."
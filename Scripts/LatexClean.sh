cd ..

find . -type f -name '*.atfi' -exec rm {} +
find . -type f -name '*.aux' -exec rm {} +
find . -type f -name '*.log' -exec rm {} +
find . -type f -name '*.out' -exec rm {} +
find . -type f -name '*.ptc' -exec rm {} +
find . -type f -name '*.toc' -exec rm {} +

echo "LaTeX excess deleted successfully from all directories."
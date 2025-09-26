echo "---------- running clang-format ----------"
find . -type d \( -path ./.cache -o -path ./.git -o -path ./third_party -o -path ./external -o -path ./build -o -path ./models \) -prune -o \( -name '*.h' -o -name '*.hh' -o -name '*.cpp' -o -name '*.cc' \) -print | xargs clang-format -i

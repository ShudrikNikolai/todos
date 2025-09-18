fuser -k 4000/tcp
rm -rf build
mkdir build
cd ./build
cmake ..
make
./todo_backend
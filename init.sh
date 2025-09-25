git submodule update --init
sudo apt-get install clang-format #install form code
#sudo apt-get install libyaml-cpp-dev #init for yaml config
clang-format -style=file -i src/*.cpp include/*.h # check format
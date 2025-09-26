git submodule update --init
sudo apt-get install clang-format #install form code
clang-format -style=file -i src/*.cpp include/*.h # check format
# sudo apt-get install postgresql-all
# sudo apt install libsqlite3-dev
# sudo apt install libpq-dev
# sudo apt install libyaml-cpp-dev

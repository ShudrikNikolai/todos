## API

<span color="#fff">git submodule add https://github.com/drogonframework/drogon external/drogon
git submodule add https://github.com/open-source-parsers/jsoncpp external/jsoncpp
git submodule add https://github.com/Thalhammer/jwt-cpp external/jwt-cpp
git submodule add https://github.com/trusch/libbcrypt external/libbcrypt
git submodule update --init
sudo apt-get install clang-format #install form code
clang-format -style=file -i src/*.cpp include/*.h # check format
# sudo apt-get install postgresql-all
# sudo apt install libsqlite3-dev
# sudo apt install libpq-dev
# sudo apt install libyaml-cpp-dev
#             sudo apt-get install build-essential libssl-dev
dg_ctl create model models</span>
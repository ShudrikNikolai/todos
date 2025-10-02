🚀 Todo Backend API на Drogon Framework

Технологический стек:

Backend: C++ + Drogon Framework

База данных: PostgreSQL

Аутентификация: JWT токены

Контейнеризация: Docker + Docker Compose

Сборка: CMake

🎯 Основные возможности

✅ Управление пользователями - регистрация и аутентификация

✅ CRUD операции с задачами (создание, чтение, обновление, удаление)

✅ Безопасность - JWT токены, хеширование паролей

✅ RESTful API - HTTP endpoints

✅ База данных - реляционная схема

🚀 Быстрый старт, но лучше по старинке))
bash
# Запуск в Docker
docker-compose up -d

# API будет доступно на 

http://localhost:4000

<!-- <span color="#fff">git submodule add https://github.com/drogonframework/drogon external/drogon
git submodule add https://github.com/open-source-parsers/jsoncpp external/jsoncpp
git submodule add https://github.com/Thalhammer/jwt-cpp external/jwt-cpp
git submodule add https://github.com/trusch/libbcrypt external/libbcrypt
git submodule update --init
sudo apt-get install clang-format 
clang-format -style=file -i src/*.cpp include/*.h 
sudo apt-get install postgresql-all
sudo apt install libsqlite3-dev
sudo apt install libpq-dev
 sudo apt install libyaml-cpp-dev
             sudo apt-get install build-essential libssl-dev
dg_ctl create model models</span> 

docker exec -it drogon-db psql -U lstfng -d postgres -f /docker-entrypoint-initdb.d/init.sql
docker exec drogon-app nc -zv drogon-db 5432
docker exec -it drogon-app psql -h drogon-db -U lstfng -d postgres
docker exec -it drogon-db psql -U lstfng -d postgres
\i /docker-entrypoint-initdb.d/init.sql

-->

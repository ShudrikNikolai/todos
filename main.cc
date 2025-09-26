#include <drogon/drogon.h>
using namespace drogon;
using namespace drogon::orm;
// schema/db postgres
// log root
// pas root
int main()
{
    // Инициализация базы данных
    // app().getLoop()->queueInLoop([]() {
    //     auto dbClient = app().getDbClient();

    //     // Создание таблицы
    //     Todo::createTable(dbClient);

    //     LOG_INFO << "Database initialized successfully";

    //     // Добавление тестовых данных (опционально)
    //     if (getenv("ADD_TEST_DATA")) {
    //         dbClient->execSqlAsync(
    //             "INSERT OR IGNORE INTO todos (title, description, priority) VALUES "
    //             "('Learn Drogon', 'Study C++ web framework', 1), "
    //             "('Build REST API', 'Create todo backend', 2), "
    //             "('Test application', 'Write unit tests', 3)",
    //             [](const Result& r) {
    //                 LOG_INFO << "Test data added successfully";
    //             },
    //             [](const DrogonDbException& e) {
    //                 LOG_ERROR << "Failed to add test data: " << e.base().what();
    //             }
    //         );
    //     }
    // });

    // LOG_DEBUG << "Load config file";
    drogon::app().loadConfigFile("../config.json");

    // LOG_DEBUG << "Running on http://localhost:4000";
    drogon::app().setThreadNum(16).enableRunAsDaemon().run();
    return EXIT_SUCCESS;
    // drogon::app()
    //     .setLogPath("./")
    //     .setLogLevel(trantor::Logger::kWarn)
    //     .addListener("0.0.0.0", 4000)
    //     .setThreadNum(16)
    //     .enableRunAsDaemon()
    //     .run();
}
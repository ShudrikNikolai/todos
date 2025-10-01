CREATE SCHEMA IF NOT EXIST postgres;

CREATE TABLE IF NOT EXISTS user_
(
    id          BIGINT                   NOT NULL GENERATED ALWAYS AS IDENTITY,
    first_name  VARCHAR(50)                       DEFAULT NULL,
    last_name   VARCHAR(50)                       DEFAULT NULL,
    email       VARCHAR(255)                      DEFAULT NULL,
    token       text                              DEFAULT NULL,
    password    text                     NOT NULL,
    created_at  TIMESTAMP WITH TIME ZONE NOT NULL,
    updated_at  TIMESTAMP WITH TIME ZONE          DEFAULT NULL,
    is_deleted  BOOLEAN                  NOT NULL DEFAULT FALSE,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS todo
(
    id         BIGINT       NOT NULL GENERATED ALWAYS AS IDENTITY,
    user_id    BIGINT       REFERENCES users NULL,
    title      VARCHAR(75)  NOT NULL,
    description TEXT DEFAULT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_todo_users FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);
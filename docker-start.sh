#!/bin/sh
if [ -f "/app/config.yaml" ]; then
    echo "Config file found, starting application..."
    if [ -f "/app/build/todo_backend" ]; then
        echo "Executable found, starting..."
        exec /app/build/todo_backend
    else
        echo "Building application..."
        mkdir -p /app/build
        cd /app/build
        cmake ..
        make -j4
        exec ./todo_backend
    fi
else
    echo "Error: Config file not found at /app/config.yaml"
    exit 1
fi
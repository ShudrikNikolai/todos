#!/bin/bash

start_dev() {
    echo "---------- start script ----------"
    echo "----------   kill port  ----------"
    fuser -k 4000/tcp 2>/dev/null # kill if daemon start
    echo "---------- cleaer build ----------"
    rm -rf build
    mkdir build
    cd ./build
    echo "---------- start build -----------"
    cmake ..
    make
    echo "---------- start daemon ----------"
    ./todo_backend
    echo "--------- daemon started ---------"
}

start_docker() {
    echo "---------- DOCKER MODE ----------"
    echo "To run in Docker, use: docker-compose up"
    echo "Or: docker build -t todos-app . && docker run -p 4000:4000 todos-app"
}

show_help() {
    echo "Usage: $0 [OPTION]"
    echo "Options:"
    echo "  docker     - Build for Docker (skip port killing and direct execution)"
    echo "  help, -h   - Show this help message"
    echo "  No option  - Normal build and execution"
}

case "${1:-}" in
    docker|--docker|-d)
        start_docker
        ;;
    help|--help|-h)
        show_help
        ;;
    "")
        start_Dev
        ;;
    *)
        echo "Error: Unknown option '$1'"
        echo "Use '$0 help' for usage information"
        exit 1
        ;;
esac
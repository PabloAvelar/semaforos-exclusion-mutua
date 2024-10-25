cmake_minimum_required(VERSION 3.28)
project(productorconsumidor C)

set(CMAKE_C_STANDARD 11)

add_executable(productorconsumidor src/main.c
        include/buffer.h
        src/buffer.c
        include/consumer.h
        include/producer.h
        src/producer.c
        src/consumer.c
)

cmake_minimum_required(VERSION 3.28)
project(productorconsumidor C)

set(CMAKE_C_STANDARD 11)

add_executable(productorconsumidor src/main.c
        include/producer.h
        include/consumer.h
        include/semaphore.h
        include/queue.h
        include/Node.h
        src/queue.c)

//
// Created by Avelar on 10/25/2024.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <windows.h>

#define BUFFER_SIZE 10

extern int buffer[BUFFER_SIZE];
extern int count;
extern int producer_count;
extern int consumer_count;

extern HANDLE mutex;
extern HANDLE empty;
extern HANDLE full;

void initialize_sync();

void show_buffer();

void cleanup_sync();

#endif //BUFFER_H

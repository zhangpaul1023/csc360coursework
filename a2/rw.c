/*Required Headers*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "rw.h"
#include "resource.h"

/*
 * Declarations for reader-writer shared variables -- plus concurrency-control
 * variables -- must START here.
 */

static resource_t data;
sem_t reader_mutex;
int num_reader;
sem_t writer_mutex;

void initialize_readers_writer() {
    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */

    init_resource(&data, "rw_initialize");
    sem_init(&reader_mutex, 0, 1);
    sem_init(&writer_mutex, 0, 1);
    num_reader = 0;
}


void rw_read(char *value, int len) {
    sem_wait(&reader_mutex);
    ++num_reader;
    if (num_reader == 1)
        sem_wait(&writer_mutex);
    sem_post(&reader_mutex);

    read_resource(&data, value, len);

    sem_wait(&reader_mutex);
    --num_reader;
    if (num_reader == 0)
        sem_post(&writer_mutex);
    sem_post(&reader_mutex);
}


void rw_write(char *value, int len) {
    sem_wait(&writer_mutex);
    write_resource(&data, value, len);
    sem_post(&writer_mutex);
}

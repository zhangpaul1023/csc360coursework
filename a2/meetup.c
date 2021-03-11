/*Required Headers*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "meetup.h"
#include "resource.h"

/*
 * Declarations for barrier shared variables -- plus concurrency-control
 * variables -- must START here.
 */

resource_t g_codeword;
pthread_mutex_t g_mux;
pthread_cond_t g_cond;
pthread_mutex_t g_codeword_mux;
pthread_cond_t g_codeword_cond;
pthread_cond_t g_block_other_meetup_cond;
int g_codeword_ready;
int g_n_arrived;
int g_block_other_meetup;
int g_mf;
int g_n;

void initialize_meetup(int n, int mf) {
    if (n < 1) {
        fprintf(stderr, "Who are you kidding?\n");
        fprintf(stderr, "A meetup size of %d??\n", n);
        exit(1);
    }

    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */

    pthread_mutex_init(&g_mux, NULL);
    pthread_cond_init(&g_cond, NULL);
    pthread_mutex_init(&g_codeword_mux, NULL);
    pthread_cond_init(&g_codeword_cond, NULL);
    pthread_cond_init(&g_block_other_meetup_cond, NULL);

    init_resource(&g_codeword, "meetup");

    g_codeword_ready = 0;
    g_n_arrived = 0;
    g_block_other_meetup = 0;
    g_mf = mf;
    g_n = n;
}


void join_meetup(char *value, int len) {
    int first_player = 0;
    int last_player = 0;

    pthread_mutex_lock(&g_mux);

    while (g_block_other_meetup) {
        pthread_cond_wait(&g_block_other_meetup_cond, &g_mux);
    }


    ++g_n_arrived;
    if (g_n_arrived == 1) {
        first_player = 1;
    }

    if (g_n_arrived == g_n) {
        last_player = 1;
        g_block_other_meetup = 1;
        pthread_cond_broadcast(&g_cond);
    } else {
        while (g_n_arrived != g_n)
            pthread_cond_wait(&g_cond, &g_mux);
    }
    pthread_mutex_unlock(&g_mux);

    if ((first_player && g_mf == MEET_FIRST) || (last_player && g_mf == MEET_LAST)) {
        pthread_mutex_lock(&g_codeword_mux);
        write_resource(&g_codeword, value, len);
        g_codeword_ready = 1;
        pthread_cond_broadcast(&g_codeword_cond);
        pthread_mutex_unlock(&g_codeword_mux);
    } else {
        pthread_mutex_lock(&g_codeword_mux);
        while (g_codeword_ready == 0)
            pthread_cond_wait(&g_codeword_cond, &g_codeword_mux);
        pthread_mutex_unlock(&g_codeword_mux);

        read_resource(&g_codeword, value, len);
    }

    pthread_mutex_lock(&g_mux);
    --g_n_arrived;
    if (g_n_arrived == 0) {
        g_codeword_ready = 0;
        g_block_other_meetup = 0;
        pthread_cond_broadcast(&g_block_other_meetup_cond);
    }
    pthread_mutex_unlock(&g_mux);
}

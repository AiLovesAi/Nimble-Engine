/*
*  main.c
*  Nimble Engine
*
*  Created by Avery Aaron on 2020-08-09.
*  Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
*
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <Nimble/NimbleEngine.h>
#include <Nimble/Graphics/NimbleOpenGL.h>

nThreadRoutine_t start(void *data)
{
    puts("Hello!\n");
    printf("Thread data: %d\n", *((int *) data));
    nFree(data);
    nThreadReturn();
}

int main(int argc, char **argv)
{
    printf("Initializing engine...\n");
    nEngineInit(argv, argc, NULL, NULL);
    printf("Initialized engine.\n");

    printf("CPU info: %s\n", nSysGetCPUInfo(NULL));

    int *data = nAlloc(sizeof(int));
    *data = 10;
    nThread_t thread;
    nThreadCreate(&thread, &start, (void *) data);
    nThreadDetach(thread);
    //nThreadJoin(thread, NULL);

    return EXIT_SUCCESS;
}

// main.c

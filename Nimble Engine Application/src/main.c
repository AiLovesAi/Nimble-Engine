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

int main(int argc, char **argv)
{
    printf("Initializing engine...\n");
    nEngineInit(argv, argc, NULL, NULL);
    printf("Initialized engine.\n");

    return EXIT_SUCCESS;
}

// main.c

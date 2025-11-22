#include "file.h"
#include <stdio.h>
#include <stdlib.h>

char* ReadFile(char *path)
{
    char* data = NULL;
    FILE* fptr = fopen(path, "r");
    if (fptr == NULL) 
    {
        goto cleanup;
    }
    if (fseek(fptr, 0, SEEK_END) != 0)
    {
        goto cleanup;
    }
    long size = ftell(fptr);
    if (size == -1L)
    {
        goto cleanup;
    }
    if (fseek(fptr, 0, SEEK_SET) != 0)
    {
        goto cleanup;
    }
    data = malloc(sizeof(char) * (size + 1));
    if (data == NULL)
    {
        goto cleanup;
    }
    size_t file_read = fread(data, sizeof(char), size, fptr);
    if (file_read < (size_t)size)
    {
        free(data);
        data = NULL;
        goto cleanup;
    }
    data[size] = '\0';

    cleanup:
        if (fptr != NULL)
        {
            fclose(fptr);
        }
        return data;
}
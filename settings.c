#include "settings.h"
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "file.h"

int ReadSettings(Settings *settings)
{
    int rc = 1;
    char* data = NULL;
    cJSON* settingsjson = NULL;
    data = ReadFile("settings.json");
    if (data == NULL)
    {
        goto cleanup;
    }
    settingsjson = cJSON_Parse(data);
    if (settingsjson == NULL)
    {
        goto cleanup;
    }
    cJSON* width = cJSON_GetObjectItemCaseSensitive(settingsjson, "width");
    cJSON* height = cJSON_GetObjectItemCaseSensitive(settingsjson, "height");
    cJSON* fullscreen = cJSON_GetObjectItemCaseSensitive(settingsjson, "fullscreen");
    cJSON* language = cJSON_GetObjectItemCaseSensitive(settingsjson, "language");
    if (width != NULL && cJSON_IsNumber(width) && 
        height != NULL && cJSON_IsNumber(height) &&
        fullscreen != NULL && cJSON_IsBool(fullscreen) &&
        language != NULL && language->valuestring != NULL && cJSON_IsString(language))
    {
        settings->width = width->valueint;
        settings->height = height->valueint;
        if (cJSON_IsTrue(fullscreen))
        {
            settings->fullscreen = true;
        }
        else 
        {
            settings->fullscreen = false;
        }
        settings->language = malloc(sizeof(char) * (strlen(language->valuestring) + 1));
        if (settings->language == NULL)
        {
            goto cleanup;
        }
        strcpy(settings->language, language->valuestring);
        rc = 0;
    }
    cleanup:
        if (data != NULL)
        {
            free(data);
        }
        if (settingsjson != NULL)
        {
            cJSON_Delete(settingsjson);
        }
        return rc;
}
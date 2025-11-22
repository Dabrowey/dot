import json

varlist = ""

vardeclaration = ""

condition = ""

assignment = ""

localejson = open("../build/localization/english.json", "r")

data = json.loads(localejson.read())

for key in data:
    if key != list(data.keys())[-1]:
        varlist += "*{}".format(key) + "," + " "
        condition += """{0} != NULL && {0}->valuestring != NULL && cJSON_IsString({0})""".format(key) + " " + "&&" + '\n' + '\t'
    else:
        varlist += "*{}".format(key)
        condition += """{0} != NULL && {0}->valuestring != NULL && cJSON_IsString({0})""".format(key)
    vardeclaration += """cJSON* {0} = cJSON_GetObjectItemCaseSensitive(localejson, "{0}");""".format(key) + '\n'
    assignment += """
    localization->{0} = malloc(sizeof(char) * (strlen({0}->valuestring) + 1));
    if (localization->{0} == NULL)
    {{
        goto cleanup;
    }}
    strcpy(localization->{0}, {0}->valuestring);""".format(key) + '\n'

LOCALIZATION_H = """#ifndef LOCALIZATION_H
#define LOCALIZATION_H

typedef struct {{
    char {};
}} Localization;

int ReadLocalization(Localization *localization, char *language);

#endif""".format(varlist)

LOCALIZATION_C = """#include "localization.generated.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "file.h"

int ReadLocalization(Localization *localization, char *language)
{{
    int rc = 1;
    char* data = NULL;
    cJSON* localejson = NULL;
    int size = strlen("localization/") + strlen(language) + strlen(".json") + 1;
    char buf[size];

    if (sprintf(buf, "localization/%s.json", language) != size)
    {{
        goto cleanup;
    }}

    data = ReadFile(buf);
    if (data == NULL)
    {{
        goto cleanup;
    }}
    localejson = cJSON_Parse(data);
    if (localejson == NULL)
    {{
        goto cleanup;
    }}
    {0}
    if ({1})
    {{
        {2}
        rc = 0;
    }}
    cleanup:
        if (data != NULL)
        {{
            free(data);
        }}
        if (localejson != NULL)
        {{
            cJSON_Delete(localejson);
        }}
        return rc;
}}""".format(vardeclaration, condition, assignment)

header = open("../localization.generated.h", "w")
header.write(LOCALIZATION_H)

source = open("../localization.generated.c", "w")
source.write(LOCALIZATION_C)
#include "localization.generated.h"
#include "settings.h"

int main(void)
{
    Settings settings = {0};
    Localization localization = {0};

    if (ReadSettings(&settings) != 0)
    {
        return 1;
    }
    if (ReadLocalization(&localization, settings.language) != 0)
    {
        return 1;
    }
}
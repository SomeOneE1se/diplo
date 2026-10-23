#include "apple/apple.h"

int main(
    int    argc,
    char **argv
)
{
    LOG_INFO("\n\t----- Project start\t-----\n\n");

    if (apple_initialize())
    {
        return FAILURE;
    }

    LOG_INFO("\n\t----- Render start\t-----\n\n");

    apple_render();

    LOG_INFO("\n\t----- Project Terminate\t-----\n\n");

    apple_terminate();

    return SUCCESS;
}

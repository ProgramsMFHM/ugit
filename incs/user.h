#ifndef USER
#define USER

typedef struct _user
{
    char name[16];
    char mail[32];
} user;

int userConfig();

#endif
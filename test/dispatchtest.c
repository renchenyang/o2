//  dispatchtest.c -- dispatch messages between local services
//

#include <stdio.h>
#include "o2.h"

#pragma comment(lib,"o2_static.lib")

#define N_ADDRS 20

int s = 0;
int w = 1;

int service_one(const o2_message_ptr data, const char *types,
                o2_arg_ptr *argv, int argc, void *user_data)
{
    char p[100];
    sprintf(p, "/two/benchmark/%d", s % N_ADDRS);
    o2_send(p, 0, "i", s);
    if (s % 10000 == 0) {
        printf("Service one received %d messages\n", s);
    }
    s++;
    return O2_SUCCESS;
}

int service_two(const o2_message_ptr data, const char *types,
                o2_arg_ptr *argv, int argc, void *user_data)
{
    char p[100];
    sprintf(p, "/one/benchmark/%d", w % N_ADDRS);
    o2_send(p, 0, "i", w);
    if (w % 10000 == 0) {
        printf("Service two received %d messages\n", w);
    }
    w++;
    return O2_SUCCESS;
}


int main(int argc, const char * argv[])
{
    o2_initialize("test");    
    o2_add_service("one");
    for (int i = 0; i < N_ADDRS; i++) {
        char path[100];
        sprintf(path, "/one/benchmark/%d", i);
        o2_add_method(path, "i", &service_one, NULL, FALSE, FALSE);
    }
    
    o2_add_service("two");
    for (int i = 0; i < N_ADDRS; i++) {
        char path[100];
        sprintf(path, "/two/benchmark/%d", i);
        o2_add_method(path, "i", &service_two, NULL, FALSE, FALSE);
    }

    o2_send("/one/benchmark/0", 0, "i", 0);
    while (1) {
        o2_poll();
    }
    o2_finish();
    return 0;
}

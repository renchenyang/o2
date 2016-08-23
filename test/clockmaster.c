//  clockmaster.c - clock synchronization test/demo
//
//  This program works with clockslave.c. It monitors clock
//  synchronization and status updates.
//

#include "o2.h"
#include "stdio.h"
#include "string.h"

#ifdef WIN32
#include <windows.h> 
#else
#include <unistd.h>
#endif

//#pragma comment(lib,"o2_static.lib")

// this is a handler that polls for current status
//
int clockmaster(o2_message_ptr msg, const char *types,
                o2_arg_ptr *argv, int argc, void *user_data)
{
    int ss = o2_status("server");
    int cs = o2_status("client");
    printf("clockmaster: local time %g global time %g "
           "server status %d client status %d\n",
           o2_local_time(), o2_get_time(), ss, cs);
    o2_send("!server/clockmaster", o2_get_time() + 1, "");
    return O2_SUCCESS;
}


int main(int argc, const char * argv[])
{
    o2_initialize("test");
    o2_add_service("server");
    o2_add_method("/server/clockmaster", "", &clockmaster, NULL, FALSE, FALSE);
    // we are the master clock
    o2_set_clock(NULL, NULL);
    o2_send("!server/clockmaster", 0.0, ""); // start polling
    o2_run(100);
    o2_finish();
    return 0;
}

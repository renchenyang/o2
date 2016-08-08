//
//  O2_message.h
//  O2
//
//  Created by 弛张 on 1/26/16.
//  Copyright © 2016 弛张. All rights reserved.
//

#ifndef o2_message_h
#define o2_message_h

extern o2_message_ptr message_freelist;

#define MAX_SERVICE_LEN 64

/** get a free message */
o2_message_ptr alloc_message();

/* allocate message structure with at least size bytes in the data portion */
o2_message_ptr alloc_size_message(int size);

/** used by CHECK_MESSAGE_LENGTH to expand message */
o2_message_ptr alloc_bigger_message(o2_message_ptr msg, int needed);

o2_message_ptr o2_build_message(o2_time timestamp, const char *service_name,
                       const char *path, const char *typestring, va_list ap);


/**
 *  o2_recv will check all the set up sockets of the local process,
 *  including the udp socket and all the tcp sockets. The message will be
 *  dispatched to a matching method if one is found.
 *  Note: the recv will not set up new socket, as o2_discover will do that
 *  for the local process.
 *
 *  @return O2_SUCESS if succeed, O2_FAIL if not.
 */
int o2_recv();


/**
 *  Convert endianness of arg pointed to by data from network to host or from host to network.
 *
 *  @param type The type of the data.
 *  @param data The data.
 */
/*void o2_arg_swap_endian(o2_type type, void *data);*/

int o2_strsize(const char *s);


#endif /* O2_message_h */

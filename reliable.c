#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <poll.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>

#include "rlib.h"
#include "buffer.h"

struct reliable_state {
    rel_t *next;			/* Linked list for traversing all connections */
    rel_t **prev;

    conn_t *c;			/* This is the connection object */

    /* Add your own data fields below this */
    // ...
    buffer_t* send_buffer;
    // ...
    buffer_t* rec_buffer;
    // ...

};
rel_t *rel_list;

/* Creates a new reliable protocol session, returns NULL on failure.
* ss is always NULL */
rel_t *
rel_create (conn_t *c, const struct sockaddr_storage *ss,
const struct config_common *cc)
{
    /* config_common fields:
    int window;		           # of unacknowledged packets in flight
    int timer;			         How often rel_timer called in milliseconds
    int timeout;			       Retransmission timeout in milliseconds
    int single_connection;   Exit after first connection failure

    rel_t is a reliable_state
    */
    rel_t *r;

    fprintf(stderr, "create function, gets called automatically");

    r = xmalloc (sizeof (*r));
    memset (r, 0, sizeof (*r));

    if (!c) {
        c = conn_create (r, ss);
        if (!c) {
            free (r);
            return NULL;
        }
    }

    r->c = c;
    r->next = rel_list;
    r->prev = &rel_list;
    if (rel_list)
    rel_list->prev = &r->next;
    rel_list = r;
    /* TODO Do any other initialization you need here... */
    // ...
    r->send_buffer = xmalloc(sizeof(buffer_t));
    r->send_buffer->head = NULL;
    // ...
    r->rec_buffer = xmalloc(sizeof(buffer_t));
    r->rec_buffer->head = NULL;
    // ...
    return r;
}

void
rel_destroy (rel_t *r)
{
    if (r->next) {
        r->next->prev = r->prev;
    }
    *r->prev = r->next;
    conn_destroy (r->c);

    /* Free any other allocated memory here */
    buffer_clear(r->send_buffer);
    free(r->send_buffer);
    buffer_clear(r->rec_buffer);
    free(r->rec_buffer);
    // ...
    fprintf(stderr, "Destroy function");

}

// n is the expected length of pkt
void
rel_recvpkt (rel_t *r, packet_t *pkt, size_t n)
{
  /* Your logic implementation here */

  /* Although I cant rely on the correct size, I now assume that
  n is correct. Hence I can check first if the received packet
  is an ack or a data packet. */

  if (n < 12) {
    /* ack, that means we need sender functionality */
    /* check if the checksum is correct */
    if (cksum(pkt->data, n) == pkt->cksum) {
      /* packet succesfully sent */
      /* TODO mark packet as received move window */
      /* TODO move window */
    } else {
      /* Checksum is wrong, dont move window */
      /* TODO send packet again */

    }
  } else {
    /* packet, that means we need receiver functionality */
    /* check if the checksum is correct */
    if (cksum(pkt->data, n) == pkt->cksum) {
      /* packet successfully reiceved */
      /* TODO load packet into buffer */
      /* TODO create ack package */
      /* TODO send ack package back */
    } else {
      /* Checksum is wrong, do*/
      /* TODO send packet again */

    }
  }
}

void
rel_read (rel_t *s)
{
    /* Your logic implementation here */
    fprintf(stderr, "Read function");
}

void
rel_output (rel_t *r)
{
    /* Your logic implementation here */
    fprintf(stderr, "Output function");
}

void
rel_timer ()
{
    // Go over all reliable senders, and have them send out
    // all packets whose timer has expired
    rel_t *current = rel_list;
    while (current != NULL) {
        // ...
        current = rel_list->next;
    }
}

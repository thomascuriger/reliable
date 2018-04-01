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
    rel_t *r;

<<<<<<< HEAD
    fprintf(stderr, "This would be creating stuff");
=======
    fprintf(stderr, "This would be creating stuff", );
>>>>>>> origin/master

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
    /* Do any other initialization you need here... */
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

}

// n is the expected length of pkt
void
rel_recvpkt (rel_t *r, packet_t *pkt, size_t n)
{
  /* Your logic implementation here */
	/* me sender functionality and receiver funtionality*/
	/* check if sender*/
	/* important: check checksum first */
  if (cksum(pkt->data, n) == pkt->cksum) {
    if (n < 12) {
  		/* I'm a sender handling the acks */
  		fprintf(stderr, "sender recvpkt");
  		/* if (cksum(pkt->data, n) == pkt->cksum) {
  			fprintf(stderr, "successfull!")
  				/*
  			1) mark as succesfully sent
  			2) move window */
  		} else {
  		/* I'm a receiver handling normal packets*/
  		fprintf(stderr, "receiver recvpkt");
  		/* same checksumtest as above*/
  		/* if (cksum(pkt->data, n) == pkt->cksum) {
  			1) write into buffer pkt->seqno
  			2) calculate ack checksum
  			3) and send it back to sender
  		} else {
  			do nothing so far?
  		}*/
  	}
  } else {
    /* package damaged. send the package again */
    /* look up send buffer with seqno */
  }
}

void
rel_read (rel_t *s)
{
    /* Your logic implementation here */
}

void
rel_output (rel_t *r)
{
    /* Your logic implementation here */
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

#include "knet.h"

void client_cb(channel_ref_t* channel, channel_cb_event_e e) {
    char      buffer[1024] = {0};
    int       bytes      = 0;
    stream_t* stream     = channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) {
        bytes = stream_available(stream);
        if (error_ok == stream_pop(stream, buffer, sizeof(buffer))) {
            /* echoд�� */
            if (bytes) {
                stream_push(stream, buffer, bytes);
            }
        }        
    } else if (e & channel_cb_event_close) {
        printf("active channel count: %d, close channel count: %d\n",
            loop_get_active_channel_count(channel_ref_get_loop(channel)),
            loop_get_close_channel_count(channel_ref_get_loop(channel)));
    } else if (e & channel_cb_event_timeout) {
        printf("client channel timeout\n");
        channel_ref_close(channel);
    }
}

void acceptor_cb(channel_ref_t* channel, channel_cb_event_e e) {
    if (e & channel_cb_event_accept) {
        printf("accept fd: %d, active channel count: %d, close channel count: %d\n",
            channel_ref_get_socket_fd(channel),
            loop_get_active_channel_count(channel_ref_get_loop(channel)),
            loop_get_close_channel_count(channel_ref_get_loop(channel)));
        channel_ref_set_timeout(channel, 5);
        channel_ref_set_cb(channel, client_cb);
    }
}

int main(int argc, char* argv[]) {
    int               i        = 0;
    int               worker   = 0;
    char*             ip       = 0;
    int               port     = 0;
    loop_t*           loop     = 0;
    loop_t**          loops    = 0;
    loop_balancer_t*  balancer = 0;
    channel_ref_t*    acceptor = 0;
    thread_runner_t** threads  = 0;

    if (argc > 2) {
        for (i = 1; i < argc; i++) {
            if (!strcmp("-ip", argv[i])) {
                ip = argv[i+1];
            } else if (!strcmp("-port", argv[i])) {
                port = atoi(argv[i+1]);
            } else if (!strcmp("-w", argv[i])) {
                worker = atoi(argv[i+1]);
            }
        }
    }

    balancer = loop_balancer_create();
    loop     = loop_create();
    threads  = (thread_runner_t**)malloc(sizeof(thread_runner_t*) * worker);
    loops    = (loop_t**)malloc(sizeof(loop_t*) * worker);

    loop_balancer_attach(balancer, loop);

    acceptor = loop_create_channel(loop, 8, 1024);
    channel_ref_set_cb(acceptor, acceptor_cb);
    channel_ref_accept(acceptor, ip, port, 500);

    for (i = 0; i < worker; i++) {
        loops[i] = loop_create();
        loop_balancer_attach(balancer, loops[i]);
        threads[i] = thread_runner_create(0, 0);
        thread_runner_start_loop(threads[i], loops[i], 0);
    }

    loop_run(loop);

    for (i = 0; i < worker; i++) {
        thread_runner_destroy(threads[i]);        
    }
    for (i = 0; i < worker; i++) {
        loop_destroy(loops[i]);
    }
    loop_destroy(loop);
    loop_balancer_destroy(balancer);
    if (loops) {
        free(loops);
    }
    if (threads) {
        free(threads);
    }
    return 0;
}
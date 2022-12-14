#include "process.h"
#include "pipe.h"
#include "fifo.h"
//#include "message_queue.h" // can't compile on mac...
//#include "shared_mem.h" // can compile but failed to run on mac
#include "signal_handling.h"
#include "tcp_svr_client.h"

int main() {
    //process_fork::demo();
    //process_kill::demo();
    //process_deamon::demo();
    //pipe_playground::demo();
    //fifo_playground::demo();
    //msg_queue_playground::demo<true>();
    //shared_mem_playground::demo<true>();
    //shared_mem_playground::demo<false>();
    //signal_handling::demo();
    #if defined(TCP_SERVER)
        tcp::server::demo();
    #elif defined(TCP_CLIENT)
        tcp::client::demo();
    #endif
}

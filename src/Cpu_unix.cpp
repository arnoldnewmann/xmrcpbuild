#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>


#include "Cpu.h"


void Cpu::init()
{
#   ifdef XMRIG_NO_LIBCPUID
    m_totalThreads = sysconf(_SC_NPROCESSORS_CONF);
#   endif

    initCommon();
}


void Cpu::setAffinity(int id, uint64_t mask)
{
    cpu_set_t set;
    CPU_ZERO(&set);

    for (int i = 0; i < m_totalThreads; i++) {
        if (mask & (1UL << i)) {
            CPU_SET(i, &set);
        }
    }

    if (id == -1) {
        sched_setaffinity(0, sizeof(&set), &set);
    } else {
        pthread_setaffinity_np(pthread_self(), sizeof(&set), &set);
    }
}

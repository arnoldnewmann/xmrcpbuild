#ifndef __JOBRESULT_H__
#define __JOBRESULT_H__


#include <memory.h>
#include <stdint.h>


#include "Job.h"


class JobResult
{
public:
    inline JobResult() : poolId(0), diff(0), nonce(0) {}
    inline JobResult(int poolId, const char *jobId, uint32_t nonce, const uint8_t *result, uint32_t diff) : poolId(poolId), diff(diff), nonce(nonce)
    {
        memcpy(this->jobId, jobId, sizeof(this->jobId));
        memcpy(this->result, result, sizeof(this->result));
    }


    inline JobResult(const Job &job) : poolId(0), diff(0), nonce(0)
    {
        memcpy(jobId, job.id(), sizeof(jobId));
        poolId = job.poolId();
        diff   = job.diff();
        nonce  = *job.nonce();
    }


    inline JobResult &operator=(const Job &job) {
        memcpy(jobId, job.id(), sizeof(jobId));
        poolId = job.poolId();
        diff   = job.diff();

        return *this;
    }


    char jobId[64];
    int poolId;
    uint32_t diff;
    uint32_t nonce;
    uint8_t result[32];
};

#endif /* __JOBRESULT_H__ */

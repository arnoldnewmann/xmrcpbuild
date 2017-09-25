#ifndef __SUBMITRESULT_H__
#define __SUBMITRESULT_H__


#include <uv.h>


class SubmitResult
{
public:
    inline SubmitResult() : seq(0), diff(0), start(0) {}
    inline SubmitResult(int64_t seq, uint32_t diff) :
        seq(seq),
        diff(diff)
    {
        start = uv_hrtime();
    }

    inline uint64_t elapsed() const { return (uv_hrtime() - start) / 1000000; }

    int64_t seq;
    uint32_t diff;
    uint64_t start;
};

#endif /* __SUBMITRESULT_H__ */

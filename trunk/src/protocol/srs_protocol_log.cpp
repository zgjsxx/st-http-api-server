#include <sys/time.h>
#include <unistd.h>
#include <srs_protocol_log.hpp>
#include <srs_protocol_utility.hpp>
#include <srs_protocol_st.hpp>

static SrsContextId _srs_context_default;
static int _srs_context_key = -1;

void _srs_context_destructor(void* arg)
{
    SrsContextId* cid = (SrsContextId*)arg;
    srs_freep(cid);
}

SrsThreadContext::SrsThreadContext()
{
}

SrsThreadContext::~SrsThreadContext()
{
}

SrsContextId SrsThreadContext::generate_id()
{
    SrsContextId cid = SrsContextId();
    return cid.set_value(srs_random_str(8));
}

const SrsContextId& SrsThreadContext::set_id(const SrsContextId& v)
{
    SrsContextId* cid = new SrsContextId();
    *cid = v;  

    if (_srs_context_key < 0) {
        int r0 = srs_key_create(&_srs_context_key, _srs_context_destructor);
        // srs_assert(r0 == 0);
    }


    int r0 = srs_thread_setspecific(_srs_context_key, cid);
    // srs_assert(r0 == 0);
    return v;
}

const SrsContextId& SrsThreadContext::get_id()
{
    // ++_srs_pps_cids_get->sugar;

    // if (!srs_thread_self()) {
    //     return _srs_context_default;
    // }

    void* cid = srs_thread_getspecific(_srs_context_key);
    if (!cid) {
        return _srs_context_default;
    }

    return *(SrsContextId*)cid;
}

void SrsThreadContext::clear_cid()
{
}

bool srs_log_header(char* buffer, int size, bool utc, bool dangerous, const char* tag, SrsContextId cid, const char* level, int* psize, const char* func, const char* file, int line)
{
    timeval tv;
    if(gettimeofday(&tv, NULL) == -1){
        return false;
    }
    
    // to calendar time
    struct tm now;
    // Each of these functions returns NULL in case an error was detected. @see https://linux.die.net/man/3/localtime_r
    if (utc) {
        if (gmtime_r(&tv.tv_sec, &now) == NULL) {
            return false;
        }
    } else {
        if (localtime_r(&tv.tv_sec, &now) == NULL) {
            return false;
        }
    }

    int written = -1;
    if (dangerous) {
        if (tag) {
            written = snprintf(buffer, size,
                "[%d-%02d-%02d %02d:%02d:%02d.%03d][%s][%d][%s][%d][%s][%s][%s:%d]",
                1900 + now.tm_year, 1 + now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, (int)(tv.tv_usec / 1000),
                level, getpid(), cid.c_str(), errno, tag, func, file, line);
        } else {
            written = snprintf(buffer, size,
                "[%d-%02d-%02d %02d:%02d:%02d.%03d][%s][%d][%s][%d][%s][%s:%d] ",
                1900 + now.tm_year, 1 + now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, (int)(tv.tv_usec / 1000),
                level, getpid(), cid.c_str(), errno, func, file, line);
        }
    } else {
        if (tag) {
            written = snprintf(buffer, size,
                "[%d-%02d-%02d %02d:%02d:%02d.%03d][%s][%d][%s][%s][%s][%s:%d] ",
                1900 + now.tm_year, 1 + now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, (int)(tv.tv_usec / 1000),
                level, getpid(), cid.c_str(), tag, func, file, line);
        } else {
            written = snprintf(buffer, size,
                "[%d-%02d-%02d %02d:%02d:%02d.%03d][%s][%d][%s][%s][%s:%d] ",
                1900 + now.tm_year, 1 + now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, (int)(tv.tv_usec / 1000),
                level, getpid(), cid.c_str(), func, file, line);
        }
    }
    // Exceed the size, ignore this log.
    // Check size to avoid security issue https://github.com/ossrs/srs/issues/1229
    if (written <= 0 || written >= size) {
        return false;
    }
    
    // write the header size.
    *psize = written;
    
    return true;
}

impl_SrsContextRestore::impl_SrsContextRestore(SrsContextId cid)
{
    cid_ = cid;
}

impl_SrsContextRestore::~impl_SrsContextRestore()
{
    _srs_context->set_id(cid_);
}
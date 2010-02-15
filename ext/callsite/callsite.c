#include "callsite.h"

static ID m_hash;

static int strhash(register const char *string)
{
    register int c;

    register int val = 0;

    while ((c = *string++) != '\0') {
    val = val*997 + c;
    }

    return val + (val>>5);
}

void
Init_callsite()
{
    m_hash = rb_intern("hash");
    rb_define_global_function("callsite", rb_f_callsite, -1);
}
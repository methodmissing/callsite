#include "ruby.h"

static int strhash(register const char *string);

static VALUE rb_f_callsite(int argc, VALUE *argv, VALUE obj);

#ifdef RUBY18
#include "node.h"
#include "env.h"
#include "callsite_18.h"
#else
#include "callsite_19.h"
#endif
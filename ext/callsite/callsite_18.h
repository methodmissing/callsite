static VALUE rb_f_callsite(int argc, VALUE *argv, VALUE obj)
{
    struct FRAME *frame = ruby_frame;
    NODE *n;
    int lev = -1;
    int csite = 0;
    VALUE lv;

    rb_scan_args(argc, argv, "01", &lv);
    if (!NIL_P(lv)) lev = NUM2INT(lv);

    if (frame->last_func == ID_ALLOCATOR) {
    frame = frame->prev;
    }
    if (lev < 0) {
    ruby_set_current_source();
    if (frame->last_func) {
      csite += strhash(ruby_sourcefile) + ruby_sourceline + frame->last_func; 
    }
    else if (ruby_sourceline == 0) {
      csite += strhash(ruby_sourcefile);
    }
    else {
      csite += strhash(ruby_sourcefile) + ruby_sourceline; 
    }
    if (lev < -1) return INT2FIX(csite);
    }
    else {
    while (lev-- > 0) {
        frame = frame->prev;
        if (!frame) {
        csite = 0;
        break;
        }
      }
    }
    for (; frame && (n = frame->node); frame = frame->prev) {
    if (frame->prev && frame->prev->last_func) {
        if (frame->prev->node == n) {
        if (frame->prev->last_func == frame->last_func) continue;
        }
       csite += strhash(n->nd_file) + nd_line(n) + frame->prev->last_func;
    }
    else {
      csite += strhash(n->nd_file) + nd_line(n);
    }
    }

    return INT2FIX(csite);
}
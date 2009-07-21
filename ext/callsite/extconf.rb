require 'mkmf'

dir_config('callsite')

create_makefile('callsite')

$defs.push("-DRUBY18") if have_var('rb_trap_immediate', ['ruby.h', 'rubysig.h'])
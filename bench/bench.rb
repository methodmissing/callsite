require "benchmark"
require File.dirname(__FILE__) + "/../ext/callsite/callsite"

module Kernel
  CallsiteSample = (1..10).freeze
  
  private
  def rb_callsite
    caller[CallsiteSample].hash
  end
end

TESTS = 10_000
Benchmark.bmbm do |results|
  results.report("rb_callsite") { TESTS.times { rb_callsite() } }  
  results.report("callsite") { TESTS.times { callsite() } }
end
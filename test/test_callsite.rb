require File.dirname(__FILE__) + '/helper'

class TestCallsite < Test::Unit::TestCase
  def test_callsite
    assert_instance_of Fixnum, callsite
    assert_equal callsite, callsite
    assert_equal callsite(5), callsite(5)
    assert_not_equal callsite(5), callsite
    assert_not_equal callsite(5), callsite(4)
  end
end
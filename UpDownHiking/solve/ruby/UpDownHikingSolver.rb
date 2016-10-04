#! /usr/bin/env ruby

require_relative "UpDownHiking"

require "gettc/types"
include Gettc

def init
  gettc_home = File.expand_path(ENV["GETTC_HOME"] || File.join(ENV["HOME"], ".gettc"))
  $LOAD_PATH << File.join(gettc_home, "include", "ruby")
  require "topcoder"
  include TopCoder
end

def main
  reader = Reader.new(IO.read(ARGV[0]))
  N = reader.next(TInt)
  reader.next()
  A = reader.next(TInt)
  reader.next()
  B = reader.next(TInt)

  result = UpDownHiking.new().maxHeight(N, A, B)
  IO.write(ARGV[1], Writer.new.next(result, TInt).to_s)
end

init
main

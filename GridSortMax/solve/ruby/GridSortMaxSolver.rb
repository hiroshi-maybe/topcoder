#! /usr/bin/env ruby

require_relative "GridSortMax"

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
  n = reader.next(TInt)
  reader.next()
  m = reader.next(TInt)
  reader.next()
  grid = reader.next(TArray.new(TInt))

  result = GridSortMax.new().findMax(n, m, grid)
  IO.write(ARGV[1], Writer.new.next(result, TString).to_s)
end

init
main

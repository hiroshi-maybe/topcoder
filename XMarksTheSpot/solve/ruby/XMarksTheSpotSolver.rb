#! /usr/bin/env ruby

require_relative "XMarksTheSpot"

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
  board = reader.next(TArray.new(TString))

  result = XMarksTheSpot.new().countArea(board)
  IO.write(ARGV[1], Writer.new.next(result, TInt).to_s)
end

init
main

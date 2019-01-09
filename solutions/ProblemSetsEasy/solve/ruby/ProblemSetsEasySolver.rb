#! /usr/bin/env ruby

require_relative "ProblemSetsEasy"

require "gettc/types"
include Gettc

def init()
    gettc_home = File.join(ENV["HOME"], ".gettc")
    if ENV.has_key?("GETTC_HOME")
        gettc_home = ENV["GETTC_HOME"]
    end 
    gettc_home = File.expand_path(gettc_home)
    $LOAD_PATH << File.join(gettc_home, "include", "ruby")
    require "topcoder"
    include TopCoder
end

def main()
    reader = Reader.new(IO.read(ARGV[0]))
    E = reader.next(TInt)
    reader.next()
    EM = reader.next(TInt)
    reader.next()
    M = reader.next(TInt)
    reader.next()
    MH = reader.next(TInt)
    reader.next()
    H = reader.next(TInt)

    result = ProblemSetsEasy.new().maxSets(E, EM, M, MH, H)
    IO.write(ARGV[1], Writer.new().next(result, TInt).to_s())
end
init()
main()

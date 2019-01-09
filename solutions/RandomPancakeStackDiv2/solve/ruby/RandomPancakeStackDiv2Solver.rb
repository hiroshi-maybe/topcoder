#! /usr/bin/env ruby

require_relative "RandomPancakeStackDiv2"

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
    d = reader.next(TArray.new(TInt))

    result = RandomPancakeStackDiv2.new().expectedDeliciousness(d)
    IO.write(ARGV[1], Writer.new().next(result, TDouble).to_s())
end
init()
main()

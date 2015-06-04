#! /usr/bin/env ruby

require_relative "MutaliskEasy"

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
    x = reader.next(TArray.new(TInt))

    result = MutaliskEasy.new().minimalAttacks(x)
    IO.write(ARGV[1], Writer.new().next(result, TInt).to_s())
end
init()
main()

#! /usr/bin/env ruby

require_relative "ABBA"

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
    initial = reader.next(TString)
    reader.next()
    target = reader.next(TString)

    result = ABBA.new().canObtain(initial, target)
    IO.write(ARGV[1], Writer.new().next(result, TString).to_s())
end
init()
main()

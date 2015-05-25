#! /usr/bin/env python
import os, sys
import ProblemSetsEasy

def init():
    default_path = os.path.join(os.getenv("HOME"), ".gettc")
    gettc_home = os.path.abspath(os.getenv("GETTC_HOME", default_path))
    include_dir = os.path.join(gettc_home, "include/python")
    sys.path.append(include_dir)

def main():
    import topcoder as tc
    with open(sys.argv[1], "r") as fi:
        input = fi.read()
        reader = tc.Reader(input)
    
        E = reader.next("int")
        reader.next()
        EM = reader.next("int")
        reader.next()
        M = reader.next("int")
        reader.next()
        MH = reader.next("int")
        reader.next()
        H = reader.next("int")

    result = ProblemSetsEasy.maxSets(E, EM, M, MH, H)
    with open(sys.argv[2], "w") as fo:
        fo.write(tc.write(result, "int"))

if __name__ == "__main__":
    init()
    main()

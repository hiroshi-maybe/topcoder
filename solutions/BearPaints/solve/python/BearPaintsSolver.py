#! /usr/bin/env python
import os, sys
import BearPaints

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
    
        W = reader.next("int")
        reader.next()
        H = reader.next("int")
        reader.next()
        M = reader.next("long")

    result = BearPaints.maxArea(W, H, M)
    with open(sys.argv[2], "w") as fo:
        fo.write(tc.write(result, "long"))

if __name__ == "__main__":
    init()
    main()

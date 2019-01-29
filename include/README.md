# Referring templates of `cpp-macro.h`

Generator template
- https://github.com/hiroshi-maybe/topcoder/blob/master/plugin/greed/cpp.tmpl
- https://github.com/hiroshi-maybe/codeforces/blob/master/script/template-solver.cpp

Manual template
- https://github.com/hiroshi-maybe/codeforces/blob/master/template.cpp
- https://github.com/hiroshi-maybe/leetcode/blob/master/cpp-macro.h
- https://github.com/hiroshi-maybe/GCJ/blob/master/template.cpp
- https://github.com/hiroshi-maybe/fbhackercup/blob/master/template.cpp

# Usage of #include<bits/stdc++.h> on MacOS

## Command

```
$ sudo ln -s {this dir}/bits {xcode-toolchain-path}/usr/include/c++/v1/
```

## Examples of `{xcode-toolchain-path}`

### Xcode.app

 `/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain`

### CommandLineTools

`/Library/Developer/CommandLineTools/`

Manual install from https://developer.apple.com/download/more/

# References

- https://codeforces.com/blog/entry/15643
- https://codeforces.com/blog/entry/10124

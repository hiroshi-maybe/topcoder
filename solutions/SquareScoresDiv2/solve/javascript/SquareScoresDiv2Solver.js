#! /usr/bin/env node

var fs = require("fs");
var path = require("path");
var tc = null;

function init() {
    var gettcHome = process.env.GETTC_HOME || path.join(process.env.HOME, ".gettc");
    var includeDir = path.join(gettcHome, "include", "javascript");
    tc = require(path.join(includeDir, "topcoder"));
}

function main() { try {
    var input = fs.readFileSync(process.argv[2], { encoding: "ascii" });
    var reader = new tc.Reader(input);
    var s = reader.next("String");

    var SquareScoresDiv2 = require("./SquareScoresDiv2");
    var result = SquareScoresDiv2.getscore(s);
    
    var writer = new tc.Writer();
    writer.next(result, "int");
    fs.writeFileSync(process.argv[3], writer.toString(), { encoding: "ascii" });
} catch (err) {
    console.log(err.toString());
    console.trace();
}}

init();
main();

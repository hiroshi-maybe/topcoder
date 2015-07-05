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
    var a = reader.next("int[]"); reader.next();
    var b = reader.next("int[]"); reader.next();
    var K = reader.next("int");

    var BridgeBuildingDiv2 = require("./BridgeBuildingDiv2");
    var result = BridgeBuildingDiv2.minDiameter(a, b, K);
    
    var writer = new tc.Writer();
    writer.next(result, "int");
    fs.writeFileSync(process.argv[3], writer.toString(), { encoding: "ascii" });
} catch (err) {
    console.log(err.toString());
    console.trace();
}}

init();
main();

#!/bin/sh

export DYLD_LIBRARY_PATH=lib

java -XX:+UnlockDiagnosticVMOptions -XX:CompileCommand='print,*.larger*' -jar target/benchmarks.jar

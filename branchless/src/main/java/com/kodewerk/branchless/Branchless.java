package com.kodewerk.branchless;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

public class Branchless {

    //@Benchmark
    public void testBranch() {

    }

    //@Benchmark
    public void testNoBranch() {

    }
    @State(Scope.Benchmark)
    public static class BenchmarkState {
        @Param({"10000000"})
        public int listSize;
        public long index = -1;

        public List<Integer> testList;

        @Setup(Level.Trial)
        public void setUp() {
            if (testList != null) return;
            testList = new Random()
                    .ints()
                    .limit(listSize)
                    .boxed()
                    .collect(Collectors.<Integer>toList());
        }

        @TearDown(Level.Trial)
        public void tearDown() {
            //testList = null;
        }
    }
}

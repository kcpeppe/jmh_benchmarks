package com.kodewerk.branchless;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.infra.Blackhole;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

public class NoBranch {

    @Benchmark
    public void testLargerIntWithoutIf(Blackhole blackhole, BenchmarkState state) {
        int returnedValue = largerIntWithoutIf(state.getValue(),state.getValue());
        blackhole.consume(returnedValue);
    }

    public int largerIntWithoutIf(int a, int b) {
        int signa = a >>> 31, signb = b >>> 31;
        int selector = (((signb - signa) >>> 31) * (signa ^ signb)) + ((1 - (signa ^ signb)) * ((a-b) >>> 31));
        return (a * (1 - selector)) + (b * selector);
    }

    @Benchmark
    public void testLargerWithIf(Blackhole blackhole, BenchmarkState state) {
        int returnedValue = largerWithIf(state.getValue(),state.getValue());
        blackhole.consume(returnedValue);
    }

    public int largerWithIf(int a, int b) {
        return (a < b) ? b : a;
    }

    @State(Scope.Benchmark)
    public static class BenchmarkState {
        @Param({"1048576"})
        public int listSize;
        public long index = -1;

        public List<Integer> testList;

        public int getValue() {
            return testList.get((int)(++index & 0xFFFFF));
        }

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


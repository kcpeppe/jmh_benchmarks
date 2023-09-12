package com.kodewerk.noise;

import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.*;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;
import java.util.stream.*;

@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
@State(Scope.Benchmark)
public class Noise {

    byte[] garbage;
//    @Fork(value = 1, warmups = 1)
//    @Warmup(iterations=1)
    @Benchmark
    public void produceGarbage(Blackhole sink) {
        for ( int i = 0; i < 10000; i++) {
            garbage = new byte[1024 * 100];
            sink.consume(garbage);
        }
    }

//    @Fork(value = 1, warmups = 1)
//    @Warmup(iterations=1)
    @Benchmark
    public void produceGarbageWithParkedThreads(Blackhole sink, BenchmarkState state) {
        produceGarbage(sink);
    }

    @State(Scope.Benchmark)
    public static class BenchmarkState {
        @Param({"5000"})
        public int threadCount;

        @Param({"platform", "virtual"})
        public String builderType;

        List<Thread> threads;

        @Setup(Level.Trial)
        public void setUp() {
            System.out.println("setup " +  threadCount);
            var builder = switch(builderType) {
                case "platform" -> Thread.ofPlatform();
                case "virtual" -> Thread.ofVirtual();
                default -> throw new IllegalArgumentException(
                        "Unexpected builder type: " + builderType);
            };
            threads = IntStream.range(0, threadCount)
                    .mapToObj(i -> builder.start(LockSupport::park))
                    .toList();
        }

        @TearDown(Level.Trial)
        public void tearDown() {
            for (Thread thread : threads) {
                LockSupport.unpark(thread);
            }
        }
    }
}
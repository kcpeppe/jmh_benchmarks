package com.kodewerk.noise;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.Blackhole;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;

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

        Thread[] threadPool;

        @Setup(Level.Trial)
        public void setUp() {
            System.out.println("setup " +  threadCount);
            threadPool = new Thread[threadCount];
            for (int i = 0; i < threadCount; i++) {
                threadPool[i] = new Thread(LockSupport::park);
                threadPool[i].start();
                //threadPool[i] = Thread.ofVirtual().start(LockSupport::park);
            }
        }

        @TearDown(Level.Trial)
        public void tearDown() {
            for (Thread thread : threadPool) {
                LockSupport.unpark(thread);
            }
        }
    }
}
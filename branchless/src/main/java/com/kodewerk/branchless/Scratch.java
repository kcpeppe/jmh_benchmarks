package com.kodewerk.branchless;

public class Scratch {

    public static void main(String[] args) {
        Scratch i = new Scratch();
        System.out.println();

        int withoutIf = i.largerWithNoIf(Integer.MAX_VALUE, 10);
        int withIf = i.largerWithIf(Integer.MAX_VALUE, 10);
        System.out.println(withIf + ":" + withoutIf);
        if (withIf != withoutIf) {
            System.out.println(withIf + " != " + withoutIf);
        }

        withoutIf = i.largerWithNoIf(0, 0);
        withIf = i.largerWithIf(0, 0);
        System.out.println(withIf + ":" + withoutIf);
        if (withIf != withoutIf) {
            System.out.println(withIf + " != " + withoutIf);
        }

        withoutIf = i.largerWithNoIf(Integer.MIN_VALUE, -10);
        withIf = i.largerWithIf(Integer.MIN_VALUE, -10);
        System.out.println(withIf + ":" + withoutIf);
        if (withIf != withoutIf) {
            System.out.println(withIf + " != " + withoutIf);
        }

        withoutIf = i.largerWithNoIf(10, Integer.MAX_VALUE);
        withIf = i.largerWithIf(10, Integer.MAX_VALUE);
        System.out.println(withIf + ":" + withoutIf);
        if (withIf != withoutIf) {
            System.out.println(withIf + " != " + withoutIf);
        }

        withoutIf = i.largerWithNoIf(-10, Integer.MIN_VALUE);
        withIf = i.largerWithIf(-10, Integer.MIN_VALUE);
        System.out.println(withIf + ":" + withoutIf);
        if (withIf != withoutIf) {
            System.out.println(withIf + " != " + withoutIf);
        }

        withoutIf = i.largerWithNoIf(-1_000_000_000, 2_000_000_000);
        withIf = i.largerWithIf(-1_000_000_000, 2_000_000_000);
        System.out.println(withIf + ":" + withoutIf);
        if (withIf != withoutIf) {
            System.out.println(withIf + " != " + withoutIf);
        }

    }

/*
    public int largerWithNoIf(int a, int b) {
        int sign = (int)(((long)a - (long)b) >>> 63);
        return (a * (1 - sign)) + (b * sign);
    }

    public int largerWithNoIfx(int a, int b) {
        int sign = (int)(((long)a - (long)b) >>> 63);
        return (a * (1 - sign)) + (b * sign);
    }

*/

    public int largerWithNoIf(int a, int b) {
        return (a * ((b - a) >>> 31))  + (b * ((a - b) >>> 31));
    
    }

    public int largerWithIf(int a, int b) {
        return (a < b) ? b : a;
    }

}

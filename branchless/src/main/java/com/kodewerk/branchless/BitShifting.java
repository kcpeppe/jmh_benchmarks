package com.kodewerk.branchless;

public class BitShifting {

    /*
    a - b = c
+ = + then a > b
+ = -  then b > a
- - = -   then b > a
- - = +  then a > b
- = + then a > b , we don’t need the calculation in this case
- = -  then a > b, this has wrapped
- + = -  then b > a, we don’t need the calculation in this case
+ = + then b > a, this has wrapped

This can be reduced to the following observations. If the signs are the same, then the result of the subtraction can be trusted. The signs are different, the positive value should always be taken. Let’s see if we can translate this to code.

((~((a ^ b) >>> 31) & 0x00000001) * ((b - a) >>> 31)) ^ (((a ^ b) >>> 31) * (b >>> 31));
     */

    public static void main(String[] args) {
        //Integer.MIN_VALUE;
        testing(2,10);
        System.out.println("--------");
        testing(100,10);
        System.out.println("--------");
        testing( -2, -20);
        System.out.println("--------");
        testing( -20, -2);
        System.out.println("--------");
        testing( -10, 2);
        System.out.println("--------");
        testing( 2, -10);
        System.out.println("--------");
        testing(Integer.MIN_VALUE, 1);
        System.out.println("--------");
        testing(1, Integer.MIN_VALUE);
        System.out.println("--------");
    }

    private static String[] booleans = {"false", "true"};
    private static String[] pick= { "a", "b"};

    public static void testing(int a, int b) {
        System.out.println(a + ", " + b);
        int signa = a >>> 31;
        int signb = b >>> 31;
        int answer = (((signb - signa) >>> 31) * (signa ^ signb)) + ((1 - (signa ^ signb)) * ((a-b) >>> 31));

//        System.out.println("same sign = " + booleans[(1 - differentSign)]);
//        System.out.println("Same sign answer = " + pick[sameSignAnswer]);
//        System.out.println("Different sign answer = " + pick[differentSignAnswer]);
        System.out.println("Pick " + pick[answer]);
        //int positive = xor /* take postive value */ + (sameSign * ((a-b) >>> 31));
        //System.out.println(positive);

        int c = (a * (1 - answer)) + (b * answer);

        if ( answer > 0)
            System.out.println(c + " is larger than " + a);
        else
            System.out.println(c + " is larger than " + b);
    }
}


package com.tencent.smtt.util;

public class XZUtil
{
    /**
     * Checks that the range described by {@code offset} and {@code count} doesn't exceed
     * {@code arrayLength}.
     *
     * @hide
     */
    public static void checkOffsetAndCount(int arrayLength, int offset, int count) {
        if ((offset | count) < 0 || offset > arrayLength || arrayLength - offset < count) {
            //throw new java.lang.ArrayIndexOutOfBoundsException(arrayLength, offset, count);
            throw new ArrayIndexOutOfBoundsException("length=" + arrayLength + "; regionStart=" + offset + "; regionLength=" + count);
        }
    }



}

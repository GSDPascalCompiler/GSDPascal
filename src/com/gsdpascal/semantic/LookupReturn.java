package com.gsdpascal.semantic;

import com.gsdpascal.astree.ExpressionType;


public class LookupReturn {
    public int totalOff;
    public int jumpLevel;
    public ExpressionType type;

    public LookupReturn(int totalOff, int jumpLevel, ExpressionType type) {
        this.totalOff = totalOff;
        this.jumpLevel = jumpLevel;
        this.type = type;
    }
}

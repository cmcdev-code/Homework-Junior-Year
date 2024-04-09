int arith(int x, int y, int z)
{
    int t1 = x + y;
    int t2 = z * 48;
    int t3 = t1 & 0xFFFF; 
	//0000 0000 0000 0000 1111 1111 1111 1111 == 0xFFFF
    int t4 = t2 * t3;
    return t4;
}

//gcc -S -fno-asynchronous-unwind-tables -mno-red-zone -O0 arith.c
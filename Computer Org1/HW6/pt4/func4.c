

int func4(int x) {
    int lcl= 0;
    if (x < 0)
        return 0;

    int i;
    for (i = 0; i < x; i++) {
        lcl+= i;
    }
    return lcl;
}
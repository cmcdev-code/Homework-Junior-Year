

int func2(int y , int x){
    int lcl=0;
    do{
        lcl+=y;
        x=x-1;
    }
    while(-2 <= x);
    return lcl;
}
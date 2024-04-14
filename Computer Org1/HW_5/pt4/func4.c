

void func4(int x, int y){
    int local=y;
    int local_2=x+7;
    y=local_2 | y;
    local+=y;
    x+=1;
}


void func3(int x , int y, int z){
    int lcl1=x;
    int lcl2=y;
    int lcl3=z;
    

    if(lcl1<=lcl2){
        lcl2-=lcl1;
    }
    else if( lcl2> lcl3){
        lcl3=lcl2;
    }else{
        lcl1=lcl3+lcl2;
    }

}



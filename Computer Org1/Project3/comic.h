

struct Comic
{
    char* date;
    char* code;
    char* publisher;
    char* title;
    char *cost;
};

struct Comic_List
{
    struct Comic* list;
    int size;
    int count;
};

//Sample Data
// DATE,CODE,PUBLISHER,TITLE,PRICE
// 03/08/23,JAN231097,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover A Letizia Cadonici),$3.99 
// 03/08/23,JAN231098,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover B Keyla Valerio),$3.99 
// 03/08/23,JAN231099,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover C Fritz Casis Giant-Size X-Men #1 Homage Variant),$3.99 
// 03/08/23,JAN231100,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover D Letizia Cadonici Virgin Variant),AR
// 03/08/23,JAN231101,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover E Keyla Valerio Virgin Variant),AR
// 03/08/23,JAN231102,ABLAZE PUBLISHING,Children Of The Black Sun #3 (Cover F Fritz Casis Giant-Size X-Men #1 Homage Virgin Variant),AR
// 03/08/23,DEC220991,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover A Roberto Meli),$3.99 
// 03/08/23,DEC220992,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover B Emilio Pilliu),$3.99 
// 03/08/23,DEC220993,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover C Alessandro Amoruso),$3.99 
// 03/08/23,DEC220994,ABLAZE PUBLISHING,Traveling To Mars #4 (Cover D Brent McKee Marvel Premiere #1 Warlock Homage Variant),$3.99 


//Sample Solution buffer sizes 
//100 , 100 , 100 ,1000, 10
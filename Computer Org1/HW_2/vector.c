#include "vector.h"
#include <math.h>


#define PI 3.14159625 

double dot_product(const double vec1[], int v1_len, const double vec2[], int v2_len) {
    double dot_product = 0;
        v2_len+=0;
    for (int i =0; i< v1_len; i++){
        dot_product += vec1[i] * vec2[i];
    }
return dot_product;
}

double calculate_magnitude(const double vec[], int v_len) {
    double magnitude = 0;

    for (int i = 0; i < v_len; i++) {
        
        magnitude += vec[i] * vec[i];
    }

    return sqrt(magnitude);
}



double angle_between(const double vec1[], int v1_len,const double vec2[], int v2_len){

    double dot= dot_product(vec1,v1_len,vec2,v2_len);
    double mag_1= calculate_magnitude(vec1,v1_len);
    double mag_2= calculate_magnitude(vec2,v2_len);

    return acos(dot/(mag_1*mag_2))* 180/PI;
}

void subtract(double v1_dir, double v1_mag, double v2_dir, double v2_mag, double* new_dir, double* new_mag){
    
    double i_part= v1_mag* cos((PI/180)* v1_dir)-v2_mag* cos((PI/180)*v2_dir);
    double j_part= v1_mag* sin((PI/180)*v1_dir)-v2_mag* sin((PI/180)*v2_dir);
    


    double vec[2]={i_part,j_part};
    *new_dir = atan2(j_part, i_part) * (180 / PI); 
    if (*new_dir < 0) {
    *new_dir += 360; }

    *new_mag= calculate_magnitude(vec,2);

}

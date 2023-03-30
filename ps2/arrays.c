//KNIZNICE POUZITE V TOMTO ZADANI
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <float.h>


//FUNKCIE DEKLAROVANE PRED MAINOM NECH SA DAJU POUZIVAT PRI VOLANI V MAINE 
float lift_a_car(const int stick_length, const int human_weight, const int car_weight);
float unit_price(const float pack_price, const int rolls_count, const int pieces_count);
int collatz(const int number);
int opposite_number(const int n, const int number);
int array_max(const int input_array[], const int array_size);
int array_min(const int input_array[], const int array_size);
unsigned long special_counter(const int input_array[], const int array_size);
void counter(const int input_array[], const int array_size, int result_array[2]);
int special_numbers(const int input_array[], const int array_size, int result_array[]);
unsigned long sum_squared(const int line);
 
int main(){

    return 0;
 
}

//V tejto funkcii zistujeme pomocou vzorca kde sa ma podlozit tyc aby clovek nadvihol auto svojou vlasntou vahou
//pouzita bola funkcia roundf ktora zaokruhli cislo nasledne vydelena 100 aby nam dala vysledok aky mala mat
float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
 
    float goal,z;
    goal = (float)stick_length * (float)human_weight / ((float)human_weight + (float)car_weight);
    z = roundf(goal * 100);
 
    return z/100;
}

//Tato funkcia sluzi na vypocet ceny 100ks utrzkov z celeho balenia toaletaku
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
 
    int pieces_in_pack;
    float hundred_pieces,z;
    pieces_in_pack = rolls_count * pieces_count;
    hundred_pieces = (pack_price / (float) pieces_in_pack) * 100;
    z = roundf(hundred_pieces * 100);
 
    return z/100;
}

//Tato funkcia sluzi na vypocet postupnosti smerom k 1, vzdy deleno 2 ak je nahodou cislo
//n%2 == 1 tak vynasobi 3 a nasledne pripocita 1 a tak pokracuje az do nuly 
int collatz(const int number){
    int num = number;
    int counter = 1;
    while (num != 1){
        if(num %2 == 0){
            num /= 2;
        }else{
            num *= 3;
            num++;
        }
        counter++;
    }
    return counter;
}

//Tato funkcia sluzi na najdenie opozitneho cisla v "kruhu", funckia funguje tak ze 
//ak n/2 >= ako z tak sa len pripocita z ktore predstavuje nam predtym poskytnute cislo
//v inom pripade sa z odpocita a vraciame absolutnu hodnotu vysledku
int opposite_number(const int n, const int number){
    int x = n;
    int z = number;
    int y,a;
    if(z < (n/2)){
        y = (x/2)+z;
        return y;
    }else{
        a = (x/2)-z;
        return abs(a);
    }
}

//Tato funkcia pocita, cisla v timoch(resp. poli), prvy prvok je 1 tim druhy prvok je 2 tim atd.,
//funkcia nam vracia 2 hodnoty, 1 hodnota je sucet v 1 timme, 2 honota je sucet v 2 time
void counter(const int input_array[], const int array_size, int result_array[2]){
    result_array[0] = 0;
    result_array[1] = 0;
    for (int i = 0; i < array_size; i++)
    {
        if(i%2 == 0){
            result_array[0] += input_array[i];
        }else{
            result_array[1] += input_array[i];
        }
    }
}

//Funkcia na pascalov trojuholnik, ktora najprv zisti v ktorom riadku je potom pomocou vzorca vypocita
//zvysne prvky v danom riadku, a nasledne returnuje counter ktory je +1 kedze prvy prvok treba pripocitat
//este
unsigned long sum_squared(const int line){
    unsigned long stable = 1;
    unsigned long past = 1;
    unsigned long counter = 0;
    for (int i = 1; i <= line; i++) {
        unsigned long now = (past * (line - i + 1)) / i;
        past = now;
        counter += pow(past,2);
    }
    return counter + pow(stable,2);
}

//Funkcia ktora hlada minimum v poli, v cykle for prechadza cele pole a vzdy ked najde mensie cislo
//zapise sa ako nove minimum a toto robi az pokym nedojde na koniec pola
int array_min(const int input_array[], const int array_size){
    if(input_array == NULL){
        return -1;
    }
    int minimum = input_array[0];
    
    for (int i = 0; i < array_size; i++){
        if(input_array[i] < minimum){
            minimum = input_array[i];
        }
    }
    return minimum;
}

//Funkcia ktora hlada maximum v poli, v cykle for prechadza cele pole a vzdy ked najde vacsie cislo
//zapise sa ako nove maximum a toto robi az pokym nedojde na koniec pola
int array_max(const int input_array[], const int array_size){
    if(input_array == NULL){
        return -1;
    }
    int maximum = input_array[0];
    
    for (int i = 0; i < array_size; i++){
        if(input_array[i] > maximum){
            maximum = input_array[i];
        }
    }
    return maximum;
}

//tato funkcia na kazdom i%2 == 0 zratava prvky a ak nie je i%2 == 0 tak tie prvky da na druhu
//a nasledne pripocitava k countru, funkcia vracia int counter, ktory je vlastne sucet vsetkeho
//v poli 
unsigned long special_counter(const int input_array[], const int array_size){
    int counter = 0;
    for (int i = 0; i < array_size; i++){
        if(i%2 == 0){
            counter += input_array[i];
        }else{
            counter += pow(input_array[i],2);
        }
    }
    return counter;
}

//Tato funkcia prechadza pole na kazdom prvku v poli sa zastavi a pozrie ci vsetky na pravo od daneho prvku
//su po sucte, menej ako cilso na ktorom prave v poli sme ak je, tak sa cislo zapise ako special number,
//a program pokracuje dalej, funkcia vlastne vracia len cisla ktore su "SPECIAL"
int special_numbers(const int input_array[], const int array_size, int result_array[]){
    int sum = 0;
    int counter = 0;
    for (int i = 0; i < array_size; i++)
    {
        sum = 0;
        for (int j = i+1; j < array_size; j++)
        {
            sum += input_array[j];
        }
        if(sum < input_array[i]){
            result_array[counter]= input_array[i];
            counter += 1;
        }
    }
    return counter;
}

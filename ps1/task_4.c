#include <superkarel.h>

//funkcie zadeklarovane pre mainom ktore boli pouzite
void turnAround();
void puttingBeepers();
void findBeeper();
void nextRow();

int main(){
	turn_on("task_4.kw");
	set_step_delay(300);

    findBeeper();
    
	turn_off();
	return 0;
}


//hlada beepre v stlpci ak najde dokonci cely stlpec otoci sa
//zacne ich pokladat na miesta kde beepre este niesu
//nasledne prestupi do dalsieho stlpca a robi to iste
void findBeeper(){
    turn_left();
    while(front_is_clear() && no_beepers_present()){
        step();
    }
    if(beepers_present()){
        while(not_facing_north()){
            turn_left();
        }
        while(front_is_clear()){
            step();
        }
        puttingBeepers();
    }else if(no_beepers_present()){
        turnAround();
        while(front_is_clear()){
            step();
        }
        if(front_is_blocked() && left_is_blocked()){
            turn_left();
            turn_off();
        }
        nextRow();
    }
}

//otocka
void turnAround(){
    turn_left();
    turn_left();
}

//funkcia na pokladanie beeprov na miesta kde beepre chybaju
void puttingBeepers(){
    turnAround();
    while(front_is_clear()){
        if(beepers_present()){
            step();
        }else if(no_beepers_present()){
            put_beeper();
            step();
        }
        
    }
    if(no_beepers_present()){
        put_beeper();
    }
    if(front_is_blocked() && left_is_blocked()){
        turn_left();
    }else{
        nextRow();
    }
}

//funkcia na prechod do dalsieho stlpca a nasledne znovu zapnutie hlavnej funkcie na vyhladavanie 
//ci v danom stlpci beepre su
void nextRow(){
    while(not_facing_east()){
        turn_left();
    }
    step();
    findBeeper();
}

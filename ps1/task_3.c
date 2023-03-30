#include <superkarel.h>

//zadeklarovane funkcie pouzite v programe
void turnAround();
void firstRow();
void goingHome();
void nextRow();
void puttingFirstBeepers();
void nextRows();
void turnRight();
bool rightIsBeeper();
void nextBeepers();
void lastRow();


int main(){
	turn_on("task_3.kw");
	set_step_delay(50);

    firstRow();
    puttingFirstBeepers();
    while(left_is_clear()){
        nextRows();
        nextBeepers();
    }
    goingHome();

	turn_off();
	return 0;
}

//hlada beepre v riadku ak najde, dojde na koniec riadka otoci sa a zacne ich pokladat
void firstRow(){
    if(right_is_blocked()){
        lastRow();
    }
    while(front_is_clear() && no_beepers_present()){
            step();
    }
    if(beepers_present()){
        pick_beeper();
        firstRow();
    }
}

//prve beepre polozene
void puttingFirstBeepers(){
    turnAround();
    while(front_is_clear()){
        if(beepers_in_bag() && right_is_blocked()){
            put_beeper();
        }
        step();
    }
}

//cesta naspat na vychodziu poziciu
void goingHome(){
    while(not_facing_north()){
        turn_left();
    }
    while(front_is_clear()){
        step();
        if(beepers_present()){
            while(front_is_clear()){
                step();
            }
            turn_left();
            while(front_is_clear()){
                step();
            }
            turnAround();
            turn_off();
            return;
        }
    }
    turnAround();
    while(front_is_clear()){
        step();
    }
    turn_left();
    step();
    turn_left();
    goingHome();
}

//ostatne riadky
void nextRows(){
    nextRow();
    firstRow();
}

//dava beepre ak ma beepre v taske plus ak funkcia rightisbeeper vracia hodnotu true
void nextBeepers(){
    turnAround();
    while(front_is_clear()){
        if(beepers_in_bag() && rightIsBeeper()){
            put_beeper();
        }
        step();
    }
}

//otocka
void turnAround(){
	turn_left();
	turn_left();
}

//novy riadok
void nextRow(){
    turn_left();
    step();
    turn_left();
}

//funkcia na zistenie ci je beeper nad poziciou
bool rightIsBeeper(){
    turnRight();
    step();
    if(beepers_present()){
        while(not_facing_south()){
            turn_left();
        }
        step();
        turnRight();
        return true;
    }else{
        while(not_facing_south()){
            turn_left();
        }
        step();
        turnRight();
        return false;
    }
}

//otocka doprava
void turnRight(){
    turn_left();
    turn_left();
    turn_left();
}

//posledny riadok
void lastRow(){
    while(front_is_clear()){
        step();
        if(beepers_present()){
            pick_beeper();
            lastRow();
        }
    }
}

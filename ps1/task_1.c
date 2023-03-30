#include <superkarel.h>

//funkcie pouzite v tomto programe zadeklarovane pred mainom
void turnRight();
void turnAround();
void leftBlocked();
void rightBlocked();

int main(){
	turn_on("task_1.kw");
	set_step_delay(300);

    put_beeper();
    //zaciatok mapy nech je otoceny na spravnu stranu
    while(front_is_blocked()){
        turn_left();
    }
    step();
    
    rightBlocked();

	turn_off();
	return 0;
}

//funkcia na otocenie do prava
void turnRight() {
        turn_left();
        turn_left();
        turn_left();
}

//funkcia na otocenie o 180 stupnov
void turnAround(){
    turn_left();
    turn_left();
}

//funkcia na cestu do lava po drahe
void leftBlocked(){
    if (beepers_present()){
        pick_beeper();
        turnAround();
    }
    while(left_is_blocked() && front_is_clear() && no_beepers_present()){
        step();
    }
    if(left_is_clear()){
        turn_left();
        step();
        leftBlocked();
    }
    if(left_is_blocked() && front_is_blocked() && right_is_blocked() && no_beepers_present()){
        turnAround();
        leftBlocked();
    }
    if(front_is_blocked() && no_beepers_present()){
        turnRight();
        leftBlocked();
    }
    if(beepers_present()){
        pick_beeper();
        while(not_facing_west()){
            turn_left();
        }
        turn_off();
    }    
}

//funkcia na cestu do prava po drahe
void rightBlocked(){
    while(right_is_blocked() && front_is_clear() && no_beepers_present()){
        step();
    }    
    if(right_is_clear() && no_beepers_present()){
        turnRight();
        step();
        rightBlocked();
    }
    if(left_is_blocked() && front_is_blocked() && right_is_blocked() && no_beepers_present()){
        turnAround();
        rightBlocked();
    }
    if(right_is_blocked() && front_is_blocked() && no_beepers_present()){
        turn_left();
        while(front_is_clear() && right_is_blocked() && no_beepers_present()){
            step();
        }
    }
    if(beepers_present()){
        leftBlocked();
    }
    rightBlocked();
}    

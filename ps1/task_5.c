#include <superkarel.h>

//funkcie zadeklarovane pre mainom ktore boli pouzite
void turnRight();
void findCorner();
void frameMap();
void bottomCenter();
void northCenter();

int main(){
	turn_on("task_5.kw");
	set_step_delay(300);

    findCorner();
    frameMap();
    bottomCenter();
    turnRight();
    northCenter();
    while(not_facing_north()){
        turn_left();
    }

	turn_off();
	return 0;
}

//funkcia na dostanie sa do lava do rohu mapy
void findCorner(){
    while(not_facing_south()){
        turn_left();
    }
    while(front_is_clear()){
        step();
    }
    turnRight();
    while(front_is_clear()){
        step();
    }
    while(not_facing_east()){
        turn_left();
    }
}

//funkcia na otocku do prava
void turnRight(){
    turn_left();
    turn_left();
    turn_left();
}

//funkcia na oramovanie mapy beeprami 
void frameMap(){
    while(front_is_clear()){
        put_beeper();
        step();
    }
    turn_left();
    while(front_is_clear()){
        put_beeper();
        step();
    }
    turn_left();
    while(front_is_clear()){
        put_beeper();
        step();
    }
    turn_left();
    while(front_is_clear()){
        put_beeper();
        step();
    }
    turn_left();
}

//funkcia na najdenie stredu v spodnom riadku mapy
void bottomCenter(){
    if(front_is_clear()){
        step();
    }
    if(front_is_clear()){
        step();
    }
    if(front_is_clear()){
        bottomCenter();
    }
    while(not_facing_west()){
        turn_left();
    }
    step();
}

//funkcia na najdenie stredu stredneho stplca na mape 
void northCenter(){
    if(front_is_clear()){
        step();
    }
    if(front_is_clear()){
        step();
    }
    if(front_is_clear()){
        northCenter();
    }
    while(not_facing_south()){
        turn_left();
    }
    step();

}

#include <superkarel.h>

//funkcie pouzite v tomto programe zadeklarovane pred mainom
void turnRight();
void turnAround();
void goingLeft();
void goingRight();

int main(){
	turn_on("task_2.kw");
	set_step_delay(150);

	if(no_beepers_present()){
		goingLeft();
	}
	
	if(beepers_present()){
		pick_beeper();
		turnAround();
		goingRight();
	}

	turn_off();
	return 0;
}

//cesta do lavej strany po bludisku
void goingLeft(){

	while(front_is_clear() && no_beepers_present()){
		step();
		while(front_is_blocked() && no_beepers_present()){
			turn_left();
			step();
			goingLeft();
		}
	}
}

//cesta naspat na zaciatok
void goingRight(){
	while(front_is_clear() && beepers_in_bag()){
		step();
		while(front_is_blocked() && right_is_clear()){
			turnRight();
			step();
			goingRight();
		}
	}

}

//otocka o 180 stupnov
void turnAround(){
	turn_left();
	turn_left();
}

//otocenie do prava
void turnRight(){
	turn_left();
	turn_left();
	turn_left();
}

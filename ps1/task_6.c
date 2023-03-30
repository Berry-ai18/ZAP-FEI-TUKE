#include <superkarel.h>

//zadeklarovane funkcie pouzite v tomto programe nad mainom
void goBeeper();
void turnBeeper();
void foundBeeper();
void lastBeeper();

int main(){
	turn_on("task_6.kw");
	set_step_delay(300);

    goBeeper();

	turn_off();
	return 0;
}

//funkcia na pohnutie karla dopredu alebo ak uz je na beepri
//tak sa zavola funkcia ze nasla sa pozicia 
void goBeeper(){
    if(no_beepers_present()){
        while(no_beepers_present()){
            step();
        }
    }
    if(beepers_present()){
        foundBeeper();
    }
}

//funkcia na otacanie karla po zobrati beepra
//ak je tam 4 a viac beeprov posle ho kontrolovat do dalsej funkcie
//kde sa zisti ci ich tam su 4 alebo 5
void turnBeeper(){
    if(beepers_present()){
        turn_left();
        pick_beeper();
    }
    if(beepers_present()){
        turn_left();
        pick_beeper();
    }
    if(beepers_present()){
        turn_left();
        pick_beeper();
    }
    if(no_beepers_present() || beepers_present()){
        lastBeeper();
    }
}

//funkcia na zistenie ci sa nasiel beeper ak sa nasiel otoci sa smerom na vychod
//ak je uz otocena na vychod zavola sa funkcia turnBeeper
void foundBeeper(){
    if(beepers_present() && facing_east()){
        turnBeeper();
    }else if(not_facing_east()){
        while(not_facing_east()){
            turn_left();
            foundBeeper();
        }
    }
}

//pokladovy beeper
void lastBeeper(){
    if(beepers_present()){
        pick_beeper();
        turn_left();
    }
    if(beepers_present()){
        pick_beeper();
        turn_off();
    }
    goBeeper();
}

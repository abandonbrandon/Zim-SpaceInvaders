CC=g++
OBJS=Tuple.o List.o Object.o Shield.o Movable.o PowerUp.o Projectile.o Agent.o Tank.o Enemy.o Alien.o Alien1.o Alien2.o Alien3.o AlienHorde.o RegShot.o FloodShot.o BombShot.o SliceShot.o StubShot.o TriShot.o Game.o main.o ShieldBlock.o Splash_begin.o Splash_end.o
CFLAGS=-g -Wall -c
COMP=$(CC) $(CFLAGS) $<

main : $(OBJS)
	$(CC) -g -Wall -o $@ $(OBJS) -lncurses

main.o : main.cpp Game.o  Splash_begin.o Splash_end.o
	$(COMP) 

Game.o : Game.cpp Game.hpp PowerUp.o AlienHorde.o Tank.o 
	$(COMP) 

Splash_end.o : Splash_end.cpp
	$(COMP) 

Splash_begin.o : Splash_begin.cpp
	$(COMP) 

AlienHorde.o : AlienHorde.cpp AlienHorde.hpp Alien1.o Alien2.o Alien3.o
	$(COMP)

Alien3.o : Alien3.cpp Alien3.hpp Alien.o 
	$(COMP)

Alien2.o : Alien2.cpp Alien2.hpp Alien.o 
	$(COMP)

Alien1.o : Alien1.cpp Alien1.hpp Alien.o 
	$(COMP)

Alien.o : Alien.cpp Alien.hpp Enemy.o
	$(COMP)

Enemy.o : Enemy.cpp Enemy.hpp Agent.o 
	$(COMP)

Tank.o : Tank.cpp Tank.hpp Agent.o 
	$(COMP)

Agent.o : Agent.cpp Agent.hpp Movable.o 
	$(COMP)

PowerUp.o : PowerUp.cpp PowerUp.hpp FloodShot.o BombShot.o SliceShot.o StubShot.o TriShot.o
	$(COMP)

FloodShot.o : FloodShot.cpp FloodShot.hpp Projectile.o 
	$(COMP)

BombShot.o : BombShot.cpp BombShot.hpp Projectile.o 
	$(COMP)

SliceShot.o : SliceShot.cpp SliceShot.hpp Projectile.o 
	$(COMP)

StubShot.o : StubShot.cpp StubShot.hpp Projectile.o 
	$(COMP)

TriShot.o : TriShot.cpp TriShot.hpp Projectile.o 
	$(COMP)

RegShot.o : RegShot.cpp RegShot.hpp Projectile.o 
	$(COMP)

Projectile.o : Projectile.cpp Projectile.hpp Movable.o
	$(COMP)

Movable.o : Movable.cpp Movable.hpp Object.o 
	$(COMP)

ShieldBlock.o : ShieldBlock.cpp ShieldBlock.hpp Shield.o 
	$(COMP)

Shield.o : Shield.cpp Shield.hpp Object.o 
	$(COMP)

Object.o : Object.cpp Object.hpp Tuple.o
	$(COMP)

List.o : List.cpp List.hpp Tuple.o
	$(COMP)

Tuple.o : Tuple.cpp Tuple.hpp
	$(COMP)

clean :
	rm -f *o main

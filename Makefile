
GTK_ARGS:=$(shell pkg-config --cflags --libs gtkmm-3.0)

all:
	@g++ main.cpp limobot.cpp order.cpp socket.cpp

gui:
	@g++ main_gui.cpp gui.cpp $(GTK_ARGS)
backend:
	@g++ main.cpp limobot.cpp order.cpp socket.cpp

run:
	@./a.out

listen:
	@nc -lp 15020 | xxd -c 7

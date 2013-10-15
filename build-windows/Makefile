# 076021bf9aab8bdb6612741084299b26
CFLAGS=-O$(O) -std=c++11
O=2
LFLAGS=-l sfml-graphics -l sfml-window -l sfml-system
OBJS=objs/map.o objs/main.o objs/gameover.o objs/play.o


.PHONY: all
all: objs DSD.exe

./DSD.exe: $(OBJS)
	@ echo "    LINK ./DSD.exe"
	@ $(CXX) $(OBJS) -o "./DSD.exe" $(LFLAGS)

objs/map.o: ../src/map.cpp ../src/map.h ../src/arr2d.h
	@ echo "    CXX  ../src/map.cpp"
	@ $(CXX) $(CFLAGS) -c "../src/map.cpp" -o $@
objs/main.o: ../src/main.cpp ../src/scene.h ../src/scenes/play.h \
 ../src/scenes/../map.h ../src/scenes/../arr2d.h
	@ echo "    CXX  ../src/main.cpp"
	@ $(CXX) $(CFLAGS) -c "../src/main.cpp" -o $@
objs/gameover.o: ../src/scenes/gameover.cpp ../src/scenes/gameover.h \
 ../src/scenes/../scene.h
	@ echo "    CXX  ../src/scenes/gameover.cpp"
	@ $(CXX) $(CFLAGS) -c "../src/scenes/gameover.cpp" -o $@
objs/play.o: ../src/scenes/play.cpp ../src/scenes/play.h \
 ../src/scenes/../scene.h ../src/scenes/../map.h ../src/scenes/../arr2d.h \
 ../src/scenes/gameover.h
	@ echo "    CXX  ../src/scenes/play.cpp"
	@ $(CXX) $(CFLAGS) -c "../src/scenes/play.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./DSD.exe"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././DSD.exe

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)

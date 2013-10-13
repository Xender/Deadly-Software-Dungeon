# e15bd0ead5c4a4b3e594b920047f4d4c
CFLAGS=-O$(O) -std=c++11
O=2
LFLAGS=-l sfml-graphics -l sfml-window -l sfml-system
OBJS=objs/main.o objs/map.o objs/scene.o


.PHONY: all
all: objs a.out

./a.out: $(OBJS)
	@ echo "    LINK ./a.out"
	@ $(CXX) $(OBJS) -o "./a.out" $(LFLAGS)

objs/main.o: src/main.cpp src/scene.h src/map.h src/arr2d.h
	@ echo "    CXX  src/main.cpp"
	@ $(CXX) $(CFLAGS) -c "src/main.cpp" -o $@
objs/map.o: src/map.cpp src/map.h src/arr2d.h
	@ echo "    CXX  src/map.cpp"
	@ $(CXX) $(CFLAGS) -c "src/map.cpp" -o $@
objs/scene.o: src/scene.cpp src/scene.h src/map.h src/arr2d.h
	@ echo "    CXX  src/scene.cpp"
	@ $(CXX) $(CFLAGS) -c "src/scene.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./a.out"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././a.out

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)

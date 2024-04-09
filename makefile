MAKEFLAGS += --silent

buildDir = build/
srcDir = src/

objects = $(buildDir)network.o $(buildDir)syn_flood.o $(buildDir)main.o 
target = $(buildDir)ASTER

ASTER : $(objects)
	g++ -o $(target) $(objects)

$(buildDir)syn_flood.o : $(srcDir)syn_flood.cpp
	g++ -c -o $@ $<
	echo $<
$(buildDir)network.o : $(srcDir)network.cpp
	g++ -c -o $@ $<
	echo $<
$(buildDir)main.o : $(srcDir)main.cpp
	g++ -c -o $@ $<
	echo $<
clean:
	rm $(buildDir)*.o $(buildDir)ASTER
	echo Cleaning build files..

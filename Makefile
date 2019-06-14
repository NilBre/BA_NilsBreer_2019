ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)

CXX = g++
RM  = rm -f

CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += -Wall -Wno-deprecated -ggdb -fPIC
LIBS     += $(ROOTLIBS) -lTreePlayer

SRC = $(wildcard *.cxx)
OBJ = $(patsubst %.cxx, %.o, $(SRC))

RUN = $(wildcard *.C)
EXE = $(patsubst %.C, %.exe, $(RUN))

GARBAGE = $(OBJ) $(EXE)

all : $(OBJ) $(EXE)

%.exe : %.C $(OBJ)
	@echo "creating " $@
	@$(CXX) $+ -o $@ $(CXXFLAGS) $(LIBS)

%.o : %.cxx %.h
	@echo "creating " $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@$(RM) $(GARBAGE)
	rm lambda_mittelwerte1.txt
	rm lambda_mittelwerte2.txt
	rm lambda_mittelwerte3.txt
	rm rocwerte_ssbar.txt
	rm rocwerte_ddbar.txt
	rm rocwerte_uubar.txt
	rm vxvywerte_ssbar.txt
	rm vxvywerte_ddbar.txt
	rm vxvywerte_uubar.txt

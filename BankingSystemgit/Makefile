CXX = g++
CXX_STANDARD = c++17
CXXFLAGS = -Wall -Wextra -Wpedantic -std=$(CXX_STANDARD)
COMPILER_CALL = $(CXX) $(CXXFLAGS)
COMPILATION_FILES = Logs.o encryptionModule.o UserDB.o BankInterface.o main.o

build: $(COMPILATION_FILES)
	$(COMPILER_CALL) $(COMPILATION_FILES) -o main
main.o:
	$(COMPILER_CALL) main.cpp -c
BankInterface.o:
	$(COMPILER_CALL) BankInterface.cpp -c
UserDB.o:
	$(COMPILER_CALL) UserDB.cpp -c
encryptionModule.o:
	$(COMPILER_CALL) encryptionModule.cpp -c
Logs.o:
	$(COMPILER_CALL) Logs.cpp -c
execute:
	./main
clean:
	rm -f *.o
	rm -f main
debug: clean build
CC=gcc
#CCARGS= -DDEBUG -DYYDEBUG=1 -DASM_DEBUG
CCARGS= 

BISON=bison  -d -t -v
FLEX=flex


LIB_OBJECTS=lib/dlxinstset.o lib/dlxdebug.o 
VM_OBJECTS=vm/dlxvm.o 
ASM_OBJECTS=asm/dlxasm.o asm/symbols.o asm/gencode.o asm/lex.yy.o asm/asm.tab.o asm/analyse.o
SIM_OBJECTS=sim/dlxsim.o 
OBJECTS=main.o ${LIB_OBJECTS} ${VM_OBJECTS} ${ASM_OBJECTS} ${SIM_OBJECTS}


.SUFFIXES: .c .o

compile: parser ${OBJECTS} dlx
	@echo "Done."


dlx: ${OBJECTS}
	@echo "Linking"
	@${CC} ${CCARGS} ${OBJECTS} -lreadline -o dlx.exe
	@echo "Linking done"

.c.o:
	@echo "Compiling " $*.c " ..."
	@${CC} ${CCARGS} -c -o $*.o $*.c 

build: clean compile
	@echo "Build done!"	

run: compile
	@./dlx

clean:
	@echo "Clean..."
	@rm -rf ${OBJECTS} *~ core* dlx
	@echo "Done."	

parser: asm/asm.y asm/asm.l 
	@echo "Building parser"
	@( cd asm; ${BISON} asm.y; ${FLEX} asm.l )



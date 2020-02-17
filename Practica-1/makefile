# Definición de macros para definir las carpetas de trabajo
BIN=./bin
OBJ=./obj
SRC=./src
INC=./include
LIB=./lib
ZIP=./zip
DOC=./doc
# Opciones de compilación
# -Wall muestra todas las advertencias
# -g compila en modo "depuración"
OPT=-Wall -g
# Nombre de la práctica
PRJ=practica1


# Las macros se usan en las reglas del makefile como si fuesen variables
# que se sustituyen por su valor definido anteriormente
all : $(BIN)/ejercicio

$(BIN)/ejercicio: $(OBJ)/main.o $(OBJ)/intervalo.o
	g++ $(OPT) $(OBJ)/main.o $(OBJ)/intervalo.o -o $(BIN)/ejercicio

$(OBJ)/main.o : $(SRC)/main.cpp  $(OBJ)/intervalo.o
	g++ $(OPT) -c $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC) 

$(OBJ)/intervalo.o: $(SRC)/intervalo.cpp $(INC)/intervalo.h
	g++ $(OPT) -c $(SRC)/intervalo.cpp -o $(OBJ)/intervalo.o -I$(INC) 

clean:
	@echo "Limpiando ... "
	rm -i -r -f $(OBJ)/*.o $(BIN)/* $(LIB)/* $(ZIP)/* $(DOC)/latex $(DOC)/html
	
zip: clean
	@echo "Generando ZIP del proyecto " $(PRJ)
	zip -r $(ZIP)/$(PRJ).zip *
	
doxy:
	doxygen $(DOC)/intervalo.doxy

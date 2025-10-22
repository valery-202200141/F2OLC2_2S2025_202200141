CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -g -Iinclude $(shell pkg-config --cflags gtk+-3.0)
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)
# Añade las flags de GTK a las de compilación y la librería -lfl
LDFLAGS = $(GTK_LIBS) -lfl -lm -Wl,--as-needed

# Lista de todos tus archivos de código fuente
SRCS = src/main.c src/gui.c src/ast.c src/semantic.c src/runtime.c src/lexer_utils.c src/errores.c src/codegen_arm64.c src/codegen_ast.c

# Los archivos generados por Flex y Bison también son fuentes
GENERATED_SRCS = src/lexer.c src/parser.c
# Todos los archivos fuente juntos
ALL_SRCS = $(SRCS) $(GENERATED_SRCS)

# Genera la lista de archivos objeto (.o) a partir de la lista de fuentes (.c)
OBJS = $(ALL_SRCS:.c=.o)

# El nombre del ejecutable final
TARGET = javalang


# Regla principal: depende del ejecutable
all: $(TARGET)

# Regla para generar el ejecutable: enlaza todos los objetos
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Static version to avoid library conflicts
static: $(OBJS)
	$(CC) -static -o $(TARGET)-static $(OBJS) -lfl -lm -pthread

# Alternative: build without GTK for testing parser/lexer only
console: $(OBJS)
	$(CC) -o $(TARGET)-console $(OBJS) -lfl -lm

# Ejecutar con entorno limpio para evitar conflictos de snap
run: $(TARGET)
	env -i HOME="$(HOME)" PATH="/usr/bin:/bin:/usr/local/bin" DISPLAY="$(DISPLAY)" ./$(TARGET)
	
# ----- REGLA GENÉRICA PARA COMPILAR CUALQUIER .c EN .o -----
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# ----- DEPENDENCIAS ESPECÍFICAS -----
# La compilación de lexer.o REQUIERE que parser.c y parser.h existan primero
src/lexer.o: src/parser.c include/parser.h include/lexer_utils.h

# Dependencias de headers
src/parser.o: include/parser.h include/lexer_utils.h include/ast.h include/semantic.h
src/main.o: include/parser.h
src/gui.o: include/parser.h include/lexer_utils.h include/ast.h include/parser_utils.h
src/lexer_utils.o: include/lexer_utils.h
src/ast.o: include/ast.h
src/semantic.o: include/parser.h include/ast.h include/semantic.h
src/runtime.o: include/parser.h include/ast.h include/codegen_arm64.h
src/codegen_arm64.o: include/codegen_arm64.h


#  regla para el generador por AST
src/codegen_ast.o: src/codegen_ast.c include/codegen_ast.h include/codegen_arm64.h include/ast.h
	$(CC) $(CFLAGS) -c $< -o $@
# ----- REGLAS PARA ARCHIVOS GENERADOS (Flex y Bison) -----
src/lexer.c: src/lexer.l
	$(FLEX) -o $@ $<

src/parser.c include/parser.h: src/parser.y
	$(BISON) --defines=include/parser.h -o src/parser.c $<

# Limpieza: borra el ejecutable, los .o y los archivos generados
clean:
	rm -f $(TARGET) $(TARGET)-static $(TARGET)-console $(OBJS) include/parser.h
	# Opcional: Borra también los .c generados si quieres una limpieza profunda
	rm -f $(GENERATED_SRCS)

# Le dice a make que 'all' y 'clean' no son nombres de archivos
.PHONY: all clean arm64-cc arm64-run
arm64-cc: $(TARGET) reports/out_arm64.s
	@mkdir -p reports
	@test -f reports/out_arm64.s || { echo "Falta reports/out_arm64.s. Primero ejecuta la app para generarlo."; exit 1; }
	@echo "Compilando reports/out_arm64.s -> reports/out_arm64 (AArch64)"
	aarch64-linux-gnu-gcc -no-pie -o reports/out_arm64 reports/out_arm64.s
	@echo "OK: reports/out_arm64"
	
arm64-run: arm64-cc
	@echo "Ejecutando binario ARM64 con qemu-aarch64"
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./reports/out_arm64
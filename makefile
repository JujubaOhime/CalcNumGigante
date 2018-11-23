nome_executavel = teste.exe
codigo_fonte = TLPE.c TLPEmain.c
compilador = gcc

run:
	$(compilador) $(codigo_fonte) -o $(nome_executavel)
	@ echo "\033c\n"
	@ ./$(nome_executavel)
	@ echo "\033c\n"

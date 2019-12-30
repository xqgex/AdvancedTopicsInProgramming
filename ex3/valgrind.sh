valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -v --log-file="valgrind.log" ./bin/ex3 -threads 10 -path ./bin

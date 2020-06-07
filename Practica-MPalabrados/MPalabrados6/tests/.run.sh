touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/reko98/repos/Metodologia-de-la-Programacion/Practica-MPalabrados/MPalabrados6/dist/Debug/GNU-Linux/mpalabrados6  -open data/OPEN_ERROR.data 1> tests//.out9 2>&1"
eval $CMD
rm tests//.timeout

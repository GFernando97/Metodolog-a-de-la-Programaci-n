touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/adrian/Escritorio/Home/MP/NetBeansProyectosMP/MPalabrados5/dist/Debug/GNU-Linux/mpalabrados5  -l ES -r 2020 -w 15 -h 15 -p data/ES_2020_155.data -b  AENAXABUESITSMNYAATCPSTREUISAHDOOGOAEOAOAEIAELRISAURDAIETCVNMRNRUPOUDDDÑLFEILZBEOHGQOOECEELCSJN 1> tests//.out8 2>&1"
eval $CMD
rm tests//.timeout

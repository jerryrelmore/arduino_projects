set term x11

#set ytics 5
#set mytics 5

set xrange [0:160000]

set datafile separator ","

#set samples 500

plot "/home/jerry/Documents/Arduino/Greenhouse/testdata.csv" using 0:7 with lines title "light level adjusted", "/home/jerry/Documents/Arduino/Greenhouse/testdata.csv" using 0:4 with lines title "air temp (C)", "/home/jerry/Documents/Arduino/Greenhouse/testdata.csv" using 0:6 with lines title "water temp (C)", "/home/jerry/Documents/Arduino/Greenhouse/testdata.csv" using 0:8 with lines title "tank depth"

j_values=(1 3 5 7 9)

for i in {0..2}
do
    for j in {1..9}
    do
        python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C1 -l1 -v --no-desc taskset -c 1 ./main $i 0.$j
        echo ''
    done
done
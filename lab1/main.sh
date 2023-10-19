j_values=(1 3 5 7 9)

for i in {0..2}
do
    for j in "${j_values[@]}"
    do
        python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C0 -l1 -v --no-desc taskset -c 0 ./main $i 0.$j
        echo ''
    done
done
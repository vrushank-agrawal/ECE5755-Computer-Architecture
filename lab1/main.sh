for i in {0..6}
do
    for j in {0..1}
    do
        python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C0,S0-C1,S0-C2,S0-C3,S0-C4,S0-C5,S0-C8,S0-C9 -l1 -v --no-desc taskset -a -c 0-7 ./main $i 8 $j
        echo ''
    done
done
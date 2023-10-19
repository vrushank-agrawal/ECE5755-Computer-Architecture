j_values=(1 3 5 7 9)

for i in {0}
do
    for j in "${j_values[@]}"
    do
        prof ./main $i 0.$j
        echo ''
    done
done
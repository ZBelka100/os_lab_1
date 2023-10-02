#!/bin/bash

# Путь к исполняемому файлу lab1 (относительно папки test)
executable="../src/build/lab1"

# Список файлов с данными
test_files=("test1.txt" "test2.txt" "test3.txt" "test4.txt")

# Перебираем файлы и запускаем программу для каждого из них
for ((i=0; i<${#test_files[@]}; i++)); do
    current_test_file="${test_files[$i]}"  # Сохраняем имя текущего файла в переменной
    echo "Запуск программы для файла $current_test_file:"
    result="$($executable "$current_test_file")"
    echo "$result"
    if [[ "$result" == $(cat "good_res$((i+1)).txt") ]]; then
        echo "Пройдено"
    else
        echo "Не пройдено"
    fi
    echo "--------------------------------------"
done

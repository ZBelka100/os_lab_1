#!/bin/bash

# Путь к исполняемому файлу lab1 (относительно папки test)
executable="../src/build/lab1"

# Список файлов с данными
test_files=("test1.txt" "test2.txt" "test3.txt" "test4.txt")

# Перебираем файлы и запускаем программу для каждого из них
for ((i=0; i<${#test_files[@]}; i++)); do
    echo "Запуск программы для файла $file:"
    $executable "${test_files[$i]}" 
    if($executable "${test_files[$i]}" | diff - "good_res$((i+1)).txt"); then
        echo "Пройдено"
    else
        echo "Не пройдено"
    fi
    echo "--------------------------------------"
done

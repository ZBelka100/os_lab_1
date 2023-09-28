#!/bin/bash

# Путь к исполняемому файлу lab1 (относительно папки test)
executable="../src/build/lab1"

# Список файлов с данными
data_files=("test1.txt" "test2.txt" "test3.txt" "test4.txt")

# Перебираем файлы и запускаем программу для каждого из них
for file in "${data_files[@]}"; do
    echo "Запуск программы для файла $file:"
    $executable "$file"
    echo "--------------------------------------"
done

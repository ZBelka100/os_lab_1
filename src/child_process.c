#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    
    int sum = 0;
    char buffer[1024];
    int num = 0;
    int num_started = 0; // Флаг, указывающий, что число началось
    int is_negative = 0; //Флаг для отрицательных чисел
    ssize_t bytes_read;

    // Считываем данные из файла в виде строк
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            char c = buffer[i];
            if (c == '-') {
                // Если обнаружен символ '-', устанавливаем флаг отрицательного числа
                is_negative = 1;
            } else if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                num_started = 1;
            } else if (c == ' ' || c == '\n') {
                // Если обнаружен пробел или символ новой строки, значит число закончилось
                if (num_started) {
                    // Если число отрицательное, вычитаем его модуль из суммы
                    if (is_negative) {
                        sum -= num;
                        is_negative = 0;
                    } else {
                        // Иначе прибавляем число к сумме
                        sum += num;
                    }
                    num = 0;
                    num_started = 0;
                }
            }
        }
    }
    char sum_chars[32];
    int len = 0;
    int temp_sum = sum;

    if (sum == 0) {
        sum_chars[0] = '0';
        write(STDOUT_FILENO, sum_chars, sizeof(char));
        return 0;
    }

    if (num_started) {
        if (is_negative) {
            sum -= num;
        } else {
            sum += num;
        }
    }

    // Вычисляем длину суммы
    if (temp_sum < 0) {//число отрицательное
        char minus = '-';
        write(STDOUT_FILENO, &minus, sizeof(char));
        temp_sum = sum * -1;
        sum *= -1;
    }
    while (temp_sum > 0) {
        len++;
        temp_sum /= 10;
    }
    if (sum == 0) {
        sum_chars[0] = '0';
        write(STDOUT_FILENO, sum_chars, len*sizeof(char));
        return 0;
    }
    // Преобразуем сумму в символы, начиная с конца массива
    for (int i = len - 1; i >= 0; i--) {
        sum_chars[i] = '0' + (sum % 10);
        sum /= 10;
    }

    write(STDOUT_FILENO, sum_chars, len*sizeof(char)); 

    return 0;
}

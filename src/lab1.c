#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//пользоваться strace

int main(int argc, char *argv[]) {
    int pipefd[2];
    int sum;
    // Создаем канал для обмена данными между процессами
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Дочерний процесс
        pid = getpid();
        // Закрываем конец канала, который не используется дочерним процессом
        close(pipefd[0]);
        // Открываем файл для чтения
        int file_fd = open(argv[1], O_RDONLY);
        //где то после этого портятся данные
        if (file_fd == -1) {
            perror("open");
            close(pipefd[1]); // Закрываем запись в канал
            exit(EXIT_FAILURE);
        }

        // Перенаправляем стандартный вывод в канал
        dup2(file_fd, STDIN_FILENO);//возможно из-за это все ломается, попробовать протестить 
        dup2(pipefd[1], STDOUT_FILENO);
        //close(pipefd[1]);

        execl("/home/andrey/Desktop/cpp_memes/os_lab_1/src/build/child", "child", NULL);//иначе не идет

        // Этот код выполняется только в случае неудачи запуска execl
        perror("execl");
        exit(EXIT_FAILURE);
        
    } else {
        // Родительский процесс
        pid = getpid();
        close(pipefd[1]);

        // Ждем завершения дочернего процесса
        wait(NULL);

        // Читаем число из канала
        char buffer; // Буфер для чтения данных
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], &buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, &buffer, bytes_read);
        }
        char endline = '\n';
        write(STDOUT_FILENO, &endline, 1);

        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    }

    return 0;
}

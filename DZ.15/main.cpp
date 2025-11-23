#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>


const int ROWS = 18;
const int COLS = 36;

void randomFill(int train[][COLS])
{
    srand(time(nullptr));

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            train[i][j] = rand() % 2;
        }
    }
}

void emptyFill(int train[][COLS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            train[i][j] = 0;
        }
    }
}

void printTrain(const int train[][COLS], const char* mode)
{
    std::cout << "\nТекущее состояние поездов (" << mode << ") :\n";
    for (int i = 0; i < ROWS; ++i) {
        std::cout << "Вагон №" << i + 1 << ": ";

        for (int j = 0; j < COLS; ++j)
        {
            if (train[i][j] == 0)
            {
                std::cout << "0";
            }
            else
            {
                std::cout << "1";
            }

            if ((j + 1) % 6 == 0 && j != COLS - 1)
            {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void changeSeatState(int train[][COLS])
{
    int wagonNumber, seatNumber;
    bool validInput = false;

    while (!validInput)
    {
        std::cout << "Выберите вагон (от 1 до " << ROWS << "): ";
        std::cin >> wagonNumber;
        --wagonNumber;

        if (wagonNumber >= 0 && wagonNumber < ROWS)
        {
            std::cout << "Выберите место (от 1 до " << COLS << "): ";
            std::cin >> seatNumber;
            --seatNumber;

            if (seatNumber >= 0 && seatNumber < COLS)
            {
                validInput = true;

                if (train[wagonNumber][seatNumber] == 0)
                {
                    train[wagonNumber][seatNumber] = 1;
                    std::cout << "Место успешно забронировано.\n";
                }
                else
                {
                    train[wagonNumber][seatNumber] = 0;
                    std::cout << "Место освобождено.\n";
                }
            }
            else
            {
                std::cout << "Неверный номер места!\n";
            }
        }
        else
        {
            std::cout << "Неверный номер вагона!\n";
        }
    }
}

int countFreeSeatsInWagon(const int train[][COLS], int wagonIndex)
{
    int freeSeats = 0;
    for (int j = 0; j < COLS; ++j)
    {
        if (train[wagonIndex][j] == 0)
        {
            ++freeSeats;
        }
    }
    return freeSeats;
}

int countTotalFreeSeats(const int train[][COLS])
{
    int totalFreeSeats = 0;
    for (int i = 0; i < ROWS; ++i)
    {
        totalFreeSeats += countFreeSeatsInWagon(train, i);
    }
    return totalFreeSeats;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    setlocale(LC_ALL, "");

    int train[ROWS][COLS];

    int choice;
    std::cout << "\nВыберите способ заполнения:\n"
        << "1. Рандомное заполнение\n"
        << "2. Все места свободны\n"
        << "Ваш выбор: ";
    std::cin >> choice;

    if (choice == 1)
    {
        randomFill(train);
    }
    else if (choice == 2)
    {
        emptyFill(train);
    }
    else
    {
        std::cerr << "Ошибка: некорректный выбор заполнения.\n";
        exit(EXIT_FAILURE);
    }

    int actionChoice;
    while (true)
    {
        std::cout << "\nЧто хотите сделать?\n"
            << "1. Посмотреть текущее состояние состава\n"
            << "2. Изменить состояние места (забронировать/освободить)\n"
            << "3. Узнать количество свободных мест в вагоне\n"
            << "4. Узнать общее количество свободных мест во всех вагонах\n"
            << "5. Завершить работу\n"
            << "Ваш выбор: ";
        std::cin >> actionChoice;

        if (actionChoice == 1)
        {
            printTrain(train, (choice == 1 ? "случайное заполнение" : "все места свободны"));
        }
        else if (actionChoice == 2)
        {
            changeSeatState(train);
        }
        else if (actionChoice == 3)
        {
            int wagonNumber;
            std::cout << "Для какого вагона посчитать свободные места (от 1 до " << ROWS << ")? ";
            std::cin >> wagonNumber;

            if (wagonNumber > 0 && wagonNumber <= ROWS)
            {
                int freeSeats = countFreeSeatsInWagon(train, wagonNumber - 1);
                std::cout << "Свободных мест в вагоне №" << wagonNumber << ": " << freeSeats << "\n";
            }
            else
            {
                std::cout << "Некорректный номер вагона." << "\n";
            }
        }
        else if (actionChoice == 4)
        {
            int totalFreeSeats = countTotalFreeSeats(train);
            std::cout << "Общее количество свободных мест во всех вагонах: " << totalFreeSeats << "\n";
        }
        else if (actionChoice == 5)
        {
            break;
        }
        else
        {
            std::cout << "Ошибка: неверный ввод команды.\n";
        }
    }

    return 0;
}
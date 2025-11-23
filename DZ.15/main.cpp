#include <iostream>
#include <ctime>
#include <iomanip>
#include <Windows.h>


const int ROWS = 18; 
const int COLS = 36; 

int trainTickets[ROWS][COLS];

void randomFill() 
{
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            trainTickets[i][j] = rand() % 2; 
        }
    }
}


void emptyFill() 
{
    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j) 
        {
            trainTickets[i][j] = 0; 
        }
    }
}


void printTrain() 
{
    std::cout << "Текущее состояние билетов:\n";
    for (int i = 0; i < ROWS; ++i) 
    {
        std::cout << "Вагон №" << i + 1 << ": ";
        for (int j = 0; j < COLS; ++j) 
        {
            std::cout << trainTickets[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void changeSeatState() 
{
    int wagon, seat;
    std::cout << "Введите номер вагона (от 1 до " << ROWS << "): ";
    std::cin >> wagon;
    std::cout << "Введите номер места (от 1 до " << COLS << "): ";
    std::cin >> seat;

    --wagon;
    --seat;

    if (wagon >= 0 && wagon < ROWS && seat >= 0 && seat < COLS) 
    {
        if (trainTickets[wagon][seat] == 0) 
        {
            trainTickets[wagon][seat] = 1;
            std::cout << "Место успешно забронировано.\n";
        }
        else 
        {
            trainTickets[wagon][seat] = 0; 
            std::cout << "Место успешно освобождено.\n";
        }
    }
    else 
    {
        std::cout << "Неверный номер вагона или места.\n";
    }
}

int countFreeSeatsInWagon(int wagon) 
{
    int count = 0;
    for (int j = 0; j < COLS; ++j) 
    {
        if (trainTickets[wagon][j] == 0) 
        {
            ++count;
        }
    }
    return count;
}

int countTotalFreeSeats() 
{
    int totalFree = 0;
    for (int i = 0; i < ROWS; ++i) 
    {
        totalFree += countFreeSeatsInWagon(i);
    }
    return totalFree;
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    while (true)
    {
        int fillMode;
        std::cout << "Выберите режим заполнения билетов:\n"
            << "1. Случайное заполнение\n"
            << "2. Все места свободны\n"
            << "Ваш выбор: ";
        std::cin >> fillMode;

        if (fillMode == 1) 
        {
            randomFill();
        }
        else if (fillMode == 2) 
        {
            emptyFill(); 
        }
        else 
        {
            std::cerr << "Ошибка: неверный выбор режима заполнения.\n";
            continue;
        }

        while (true) 
        {
            int action;
            std::cout << "\nВыберите действие:\n"
                << "1. Показать текущее состояние билетов\n"
                << "2. Изменить состояние места (забронировать/освободить)\n"
                << "3. Узнать количество свободных мест в вагоне\n"
                << "4. Узнать общее количество свободных мест\n"
                << "5. Закрыть программу\n"
                << "Ваш выбор: ";
            std::cin >> action;

            if (action == 1) 
            {
                printTrain(); 
            }
            else if (action == 2) 
            {
                changeSeatState(); 
            }
            else if (action == 3) 
            {
                int wagonNumber;
                std::cout << "Введите номер вагона (от 1 до " << ROWS << "): ";
                std::cin >> wagonNumber;
                --wagonNumber; 
                if (wagonNumber >= 0 && wagonNumber < ROWS) 
                {
                    std::cout << "Свободных мест в вагоне №" << wagonNumber + 1 << ": " << countFreeSeatsInWagon(wagonNumber) << "\n";
                }
                else 
                {
                    std::cout << "Неверный номер вагона.\n";
                    continue;
                }
            }
            else if (action == 4) 
            {
                std::cout << "Общее количество свободных мест: " << countTotalFreeSeats() << "\n";
            }
            else if (action == 5) 
            {
                std::cout << "Завершают работу программы.\n";
                break;
            }
            else 
            {
                std::cout << "Ошибка: неправильно выбрано действие.\n";
                continue;
            }
        }
    }

   

    return 0;
}
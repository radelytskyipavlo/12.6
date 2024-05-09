#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef int Info;
struct Elem
{
    Elem* link;
    Info info;
};

void enqueue(Elem*& first, Elem*& last, Info value);
Info dequeue(Elem*& first, Elem*& last);
void read(Elem*& first, Elem*& last);
void print(Elem* L);
float lastPassengerProbability(Elem* first);
void freeMemory(Elem*& first, Elem*& last);

int main()
{
    srand(time(NULL)); 

    Elem* first = nullptr;
    Elem* last = nullptr;
    read(first, last);

    cout << "Queue: ";
    print(first);

    float probability = lastPassengerProbability(first);
    cout << "Probability that the last passenger sits in their own seat: " << probability << endl;

    freeMemory(first, last);

    return 0;
}

void enqueue(Elem*& first, Elem*& last, Info value)
{
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = nullptr;
    if (last != nullptr)
        last->link = tmp;
    last = tmp;
    if (first == nullptr)
        first = tmp;
}

Info dequeue(Elem*& first, Elem*& last)
{
    Elem* tmp = first->link;
    Info value = first->info;
    delete first;
    first = tmp;
    if (first == nullptr)
        last = nullptr;
    return value;
}

void read(Elem*& first, Elem*& last)
{

    int passengerCount = 100;
    for (int i = 1; i <= passengerCount; ++i)
        enqueue(first, last, i);

    for (int i = 0; i < passengerCount; ++i)
    {
        int j = rand() % passengerCount + 1;
        int k = rand() % passengerCount + 1;
        Info temp = dequeue(first, last);
        enqueue(first, last, j);
        enqueue(first, last, temp);
    }
}

void print(Elem* L)
{
    while (L != nullptr)
    {
        cout << L->info << " ";
        L = L->link;
    }
    cout << endl;
}

float lastPassengerProbability(Elem* first)
{
    int trials = 1000000; 
    int success = 0; 

    for (int i = 0; i < trials; ++i)
    {
        Elem* current = first->link;
        int seatTakenByFirst = current->info;

        while (current != nullptr)
        {
            if (current->info == 100) 
            {
                if (seatTakenByFirst == 100) 
                {
                    ++success;
                }
                break;
            }
            current = current->link;
        }
    }

    return static_cast<float>(success) / trials;
}

void freeMemory(Elem*& first, Elem*& last)
{
    while (first != nullptr)
    {
        Elem* tmp = first;
        first = first->link;
        delete tmp;
    }
    last = nullptr;
}

#include <iostream>
using namespace std;

// Структура, що описує вузол
template <typename T>
struct NodeStack {
    T item;
    NodeStack<T>* next;
};

// Шаблонний клас Стек на основі однозв'язного списку
template <typename T>
class StackList {
private:
    NodeStack<T>* pTop; // покажчик на вершину стеку

public:
    // конструктор за замовчуванням
    StackList() {
        pTop = nullptr;
    }

    // конструктор копіювання
    StackList(const StackList& SL) {
        NodeStack<T>* p; // додаткові покажчики
        NodeStack<T>* p2;
        NodeStack<T>* p3;

        // Ініціалізувати pTop
        pTop = nullptr;
        p3 = nullptr;

        p = SL.pTop; // покажчик p рухається по списку SL.pTop->...
        while (p != nullptr) {
            // 1. Сформувати вузол p2
            try {
                // спроба виділення пам'яті
                p2 = new NodeStack<T>;
            }
            // якщо пам'ять не виділена, то вихід
            catch (bad_alloc e) {
                // Якщо пам’ять для покажчика p не виділилась, то вивести
                // відповідне системне повідомлення можна з допомогою
                // методу what() класу bad_alloc.
                cout << e.what() << endl;
                return;
            }

            p2->item = p->item;
            p2->next = nullptr;

            // 2. pTop = pTop + p2
            if (pTop == nullptr) { // створити чергу
                pTop = p2;
                p3 = p2;
            }
            else {
                p3->next = p2;
                p3 = p3->next;
            }

            // 3. Перейти на наступний елемент
            p = p->next;
        }
    }
    // помістити елемент у стек
    // елемент поміщається на початок списку
    void Push(T item) {
        NodeStack<T>* p;

        // 1. Сформувати елемент
        try {
            p = new NodeStack<T>; // спроба виділити пам'ять
        }
        catch(bad_alloc e) {
            // якщо пам'ять не виділилась, то вихід
            cout << e.what() << endl;
            return;
        }

        p->item = item;
        p->next = pTop; // p вказує на 1-й елемент

        // 2. Перенаправити pTop на p
        pTop = p;
    }

    // К-сть елементів у стеку
    int Count() {
        if (pTop == nullptr)
            return 0;
        else {
            NodeStack<T>* p = pTop;
            int count = 0;
            while (p != nullptr) {
                count++;
                p = p->next;
            }
        }
    }

    // очищує стек - видаляє усі елементи зі стеку
    void Empty() {
        NodeStack<T>* p; // додатковий покажчик
        NodeStack<T>* p2;

        p = pTop;
        while (p != nullptr) {
            p2 = p; // зробити копію з p
            p = p->next; // перейти на наступний елемент стеку
            delete p2; // видалити пам'ять, виділену під попередній елемент
        }
        pTop = nullptr; // поправити вершину стеку
    }

    // оператор копіювання
    StackList<T>& operator=(const StackList<T>& LS) {
        // чи є елементи в стеку?
        if (pTop != nullptr) Empty();

        NodeStack<T>* p; // додатковий покажчик
        NodeStack<T>* p2;
        NodeStack<T>* p3;

        // Ініціалізувати pTop
        pTop = nullptr;
        p3 = nullptr;

        p = LS.pTop; // покажчик p рухається по списку SL.pTop->...
        while (p != nullptr) {
            // 1. Сформувати вузол p2
            try {
                // спроба виділити пам'ять
                p2 = new NodeStack<T>;
            }
            catch (bad_alloc e) {
                // якщо пам'ять не виділена, то вихід
                cout << e.what() << endl;
                return *this;
            }
            p2->item = p->item;
            p2->next = nullptr;

            // 2. pTop = pTop + p2
            if (pTop == nullptr) { // створити чергу
                pTop = p2;
                p3 = p2;
            }
            else {
                p3->next = p2;
                p3 = p3->next;
            }

            // 3. Перейти на наступний елемент
            p = p->next;
        }
        return *this;
    }

    // вивід стеку в консоль
    void Print(const char* objName) {
        cout << "Object: " << objName << endl;

        if (pTop == nullptr)
            cout << "stack is empty." << endl;
        else {
            NodeStack<T>* p; // додатковий покажчик
            p = pTop;
            while (p != nullptr) {
                cout << p->item << "\t";
                p = p->next;
            }
            cout << endl;
        }
    }

    // деструктор
    ~StackList() {
        Empty();
    }

    // метод, що витягує елемент зі стеку
    T Pop() {
        // перевірка, чи стек порожній
        if (pTop == nullptr)
            return 0;

        NodeStack<T>* p2; // додатковий покажчик
        T item;
        item = pTop->item;

        // перенаправити покажчики pTop, p2
        p2 = pTop;
        pTop = pTop->next;

        // Звільнити пам'ять, виділену під 1-й елемент
        delete p2;

        // повернути item
        return item;
    }
};

int main() {
    system("chcp 1251");

    StackList<int> SL;
    SL.Print("SL");

    SL.Push(8);
    SL.Push(5);
    SL.Push(10);
    SL.Push(7);
    SL.Print("SL");

    // перевірка конструктора копіювання
    StackList<int> SL2 = SL;
    SL2.Print("SL2");

    SL.Empty();
    SL.Print("SL");

    SL = SL2;
    SL.Print("SL = SL2");

    StackList<int> SL3;
    SL3.Push(1);
    SL3.Push(2);
    SL3.Push(3);
    SL3.Print("SL3");

    SL = SL2 = SL3;
    SL.Print("SL");
    SL2.Print("SL2");

    int d = SL2.Pop();
    cout << "d = " << d << endl;
    SL2.Print("SL2-1");

    d = SL2.Pop();
    SL2.Print("SL2-2");

    d = SL2.Pop();
    SL2.Print("SL2-3");

    d = SL2.Pop();
    cout << "d = " << d << endl;
    SL2.Print("SL2----");
    
    return 0;
}

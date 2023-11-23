#include <iostream>
#include <vector>
#include <stack>

// Структура для представления процедуры
struct Procedure {
    std::string name;
    int memoryRequired;
    std::vector<Procedure*> calls;
};

// Функция для трассировки программы и построения дерева вызовов
void traceProgram(Procedure* head, int& totalMemory, std::vector<std::string>& callChain) {
    // Используем стек для отслеживания вызовов процедур
    std::stack<Procedure*> callStack;
    // Используем стек для отслеживания уровня памяти для каждой процедуры
    std::stack<int> memoryStack;

    callStack.push(head);
    memoryStack.push(head->memoryRequired);

    while (!callStack.empty()) {
        Procedure* currentProcedure = callStack.top();
        int currentMemory = memoryStack.top();

        // Добавляем процедуру в цепочку вызовов
        callChain.push_back(currentProcedure->name);

        // Обновляем общий объем памяти, если текущий уровень больше предыдущего максимального
        if (currentMemory > totalMemory) {
            totalMemory = currentMemory;
        }

        callStack.pop();
        memoryStack.pop();

        // Обрабатываем вызовы процедур, если есть
        for (Procedure* call : currentProcedure->calls) {
            callStack.push(call);
            memoryStack.push(currentMemory + call->memoryRequired);
        }
    }
}

int main() {
    // Создаем процедуры
    Procedure head = {"Main", 10};
    Procedure a = {"A", 5};
    Procedure b = {"B", 8};
    Procedure c = {"C", 12};
    Procedure d = {"D", 6};

    // Строим дерево вызовов
    head.calls = {&a, &b};
    a.calls = {&c, &d};

    // Переменные для хранения результатов
    int totalMemory = 0;
    std::vector<std::string> callChain;

    // Трассируем программу
    traceProgram(&head, totalMemory, callChain);

    // Выводим результаты
    std::cout << "Total Memory Required: " << totalMemory << " units\n";
    std::cout << "Call Chain:\n";
    for (const std::string& procedure : callChain) {
        std::cout << procedure << " -> ";
    }
    std::cout << "End\n";

    return 0;
}

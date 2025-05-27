#include <iostream>
#include <string>
#include <map>
#include <windows.h>

using namespace std;

int CodeError = 0; // 0 — успіх, 1 — не знайдено

// Структура для ПІБ
struct FullName {
    string surname;
    string name;
    string patronymic;

    friend ostream& operator<<(ostream& os, const FullName& fn) {
        os << fn.surname << " " << fn.name << " " << fn.patronymic;
        return os;
    }

    friend istream& operator>>(istream& is, FullName& fn) {
        is >> fn.surname >> fn.name >> fn.patronymic;
        return is;
    }

    string getName() const {
        return name;
    }
};

// Клас асоціації номер телефону <-> ПІБ
class PhoneBook {
private:
    map<string, FullName> data; // телефон -> ПІБ

public:
    // Додавання нового запису
    void add(const string& phone, const FullName& person) {
        data[phone] = person;
    }

    // Індексатор
    FullName operator[](const string& phone) {
        auto it = data.find(phone);
        if (it != data.end()) {
            CodeError = 0;
            return it->second;
        } else {
            CodeError = 1;
            return FullName{"", "", ""};
        }
    }

    // Альтернативний доступ
    FullName operator()(const string& phone) {
        return (*this)[phone];
    }

    // Перевантаження << для всіх записів
    friend ostream& operator<<(ostream& os, const PhoneBook& pb) {
        for (const auto& entry : pb.data) {
            os << "Телефон: " << entry.first << " | ПІБ: " << entry.second << '\n';
        }
        return os;
    }

    // Перевантаження >> для створення набору
    friend istream& operator>>(istream& is, PhoneBook& pb) {
        int n;
        cout << "Скільки записів хочете ввести? ";
        is >> n;

        for (int i = 0; i < n; ++i) {
            string phone;
            FullName fn;
            cout << "Введіть номер телефону: ";
            is >> phone;
            cout << "Введіть ПІБ (прізвище ім'я по-батькові): ";
            is >> fn;
            pb.add(phone, fn);
        }

        return is;
    }
};

// Головна функція
int main() {
    SetConsoleOutputCP(65001); // UTF-8 для Windows консолі

    PhoneBook book;

    // Введення записів
    cin >> book;

    // Виведення всіх записів
    cout << "\nЗбережені записи:\n" << book;

    string searchPhone;
    while (true) {
        cout << "\nВведіть номер телефону для пошуку (0 або q для виходу): ";
        cin >> searchPhone;

        if (searchPhone == "0" || searchPhone == "q") {
            cout << "Вихід з пошуку.\n";
            break;
        }

        // Пошук
        FullName found = book[searchPhone];
        if (CodeError == 0) {
            cout << "Знайдений абонент: " << found << '\n';
            cout << "Ім’я абонента: " << found.getName() << '\n';  // Виведення лише імені
        } else {
            cout << "Абонент з таким номером не знайдений.\n";
        }
    }

    return 0;
}

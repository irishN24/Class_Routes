#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class route {
    int* r, n; // r – массив, представляющий маршрут; n – количество городов
public:
    route(int num = 0); // создает начальную перестановку по возрастанию ++
    route(const route&); // конструктор копирования ++
    route& operator = (const route&); // операция присваивания ++
    ~route() { // деструктор ++
        if (r) delete[]r; r = NULL;
    }
    int routePrice(int**); // вычисляет стоимость маршрута по матрице стоимости ++
    bool nextRoute(); // вычисляет следующий маршрут, используя алгоритм Дейкстры
    friend ostream& operator << (ostream&, const route&); // вывод маршрута ++
};
//начальная перестановка
route::route(int num) : n(num) {
    r = new int[n];
    for (int i = 0; i < n; i++) {
        r[i] = i;
    }
}
// конструктор копирования
route::route(const route& ro) : n(ro.n) { 
    r = new int[n];
    for (int i = 0; i < n; i++) {
        r[i] = ro.r[i];
    }
}
// операция присвоения
route& route::operator = (const route& ro) { 
    if (this != &ro) {
        if (r) delete[]r;
        n = ro.n;
        r = new int[n];
        for (int i = 0; i < n; i++) {
            r[i] = ro.r[i];
        }
    }
    return *this;
}
//заполнение матрицы
void fillCostMatrix(int** costMatrix, int numCity) {
    cout << "Enter the costMatrix (" << numCity << "*" << numCity << "):\n";
    for (int i = 0; i < numCity; ++i) {
        for (int j = 0; j < numCity; ++j) {
            if (i == j) {
                costMatrix[i][j] = 0;
                cout << "(" << i << ", " << j << "): " << costMatrix[i][j] << endl;
            }
            else {
                cout << "(" << i << ", " << j << "): ";
                cin >> costMatrix[i][j];
            }
        }
    }
}
// стоимость маршрута по матрице стоимости
int route::routePrice(int** costMatrix) { 
    int price = 0;
    for (int i = 0; i < n - 1; i++) {
        price += costMatrix[r[i]][r[i + 1]];
    }
    price += costMatrix[r[n - 1]][r[0]];
    return price;
}
// вычисляет следующий маршрут
bool route::nextRoute() { 
    vector<int> P(r, r + n);
    int i = n - 2;
    while (i >= 0 && P[i] >= P[i + 1]) {
        i--;
    }
    if (i < 0) {
        return false;
    }
    else {
        int j = n - 1;
        while (P[j] <= P[i]) {
            j--;
        }
        swap(P[i], P[j]);
        reverse(P.begin() + i + 1, P.end());
        for (int k = 0; k < n; k++) {
            r[k] = P[k];
        }
        return true;
    }
}
ostream& operator << (ostream& os, const route& rt) {
    for (int i = 0; i < rt.n; i++) {
        os << rt.r[i] << "";
    }
    return os;
}


int main() {
    int numCity; //количество городов
    cout << "Enter the numbers of cities: ";
    cin >> numCity;
    route rt(numCity);

    //матрица стоимости
    int** costMatrix = new int* [numCity];
    for (int i = 0; i < numCity; i++) {
        costMatrix[i] = new int[numCity];
    }
    fillCostMatrix(costMatrix, numCity);

    int minPrice = numeric_limits<int>::max();
    route BestRoute(numCity);

    do {
        int currentPrice = rt.routePrice(costMatrix);
        if (currentPrice < minPrice) {
            minPrice = currentPrice;
            BestRoute = rt;
        }
    } while (rt.nextRoute());

    cout << "best Route: " << BestRoute << "\n";
    cout << "Min Price: " << minPrice << "\n";

    for (int i = 0; i < numCity; i++) {
        delete[]costMatrix[i];
    }
    delete[]costMatrix;
    return 0;
}
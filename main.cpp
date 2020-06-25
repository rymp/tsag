#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

const int nv = 20; //Число вершин
const int ne = nv - 1; //Число рёбер

vector<int> graph[nv];

bool used[nv];
int refcomp[nv]; //Массив компонент связности

vector<int> ans; //Вектор результата

void dfs (int v){ //Поиск в глубину
    used[v] = true;
    for (size_t i=0; i<graph[v].size(); ++i) {
        int to = graph[v][i];
        if (!used[to])
            dfs (to);
    }
    ans.push_back (v);
}

void topological_sort() {
    for (int i=0; i<nv; ++i)
        used[i] = false;
    ans.clear();
    for (int i=0; i<nv; ++i)
        if (!used[i])
            dfs (i);
    reverse(ans.begin(), ans.end());
}

void setGraph(){
    int v1,v2; //Вершины ребра
    int tmp1,tmp2;
    for(int i = 0;i < ne;i++){
        v1 = rand()%nv;
        do{
            v2 = rand()%nv;
        }while(refcomp[v1] == refcomp[v2] || binary_search(graph[v1].begin(),graph[v1].end(),v2)); //Если ребро создаст цикл или уже создано то продолжить
        graph[v1].push_back(v2);

        //Изменение массива компонент связности
        tmp1 = refcomp[v1];
        tmp2 = refcomp[v2];
        for(int j = 0;j < nv;j++)
            if(refcomp[j] == tmp2)
                refcomp[j] = tmp1;
    }
}

void viewGraph(){
    for(int i = 0;i < nv;i++){
        cout << "Вершина №" << i << "смежна с - ";
        for(int j = 0;j < graph[i].size();j++){
            cout << graph[i][j];
            if(j != graph[i].size() - 1) //Если не последняя в векторе
                cout << " и ";
        }
        cout << " вершинами" << endl;
    }
}

int main(){
    srand(time(NULL));
    setlocale(LC_ALL,"rus");

    for(int i = 0;i < nv;i++) //Инициализация массива компонент связности
        refcomp[i] = i;
    setGraph();
    viewGraph();

    topological_sort();

    cout << "Результат: ";
    for(int i = 0;i < ans.size();i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

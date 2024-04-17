#include <stdio.h>
#include <locale.h>
#define n 16     // начальное количество игроков
#define m 7     // игроки, уже занявшие места в таблице
double graf[n][n] = {
    //     G      E     Z     I     M     P     S     C     9     0     1     2     3     4     5     6
/*G*/   {    0, 0.75, 0.80, 0.70, 0.65, 0.95, 0.60, 0.50, 0.60, 0.85, 0.95, 0.45, 0.50, 0.70, 0.80, 0.55 },
/*E*/   { 0.25,    0, 0.15, 0.10, 0.20, 0.70, 0.25, 0.20, 0.40, 0.60, 0.80, 0.15, 0.30, 0.35, 0.35, 0.15 },
/*Z*/   { 0.20, 0.85,    0, 0.75, 0.50, 0.90, 0.45, 0.40, 0.30, 0.80, 0.90, 0.25, 0.35, 0.50, 0.55, 0.35 },
/*I*/   { 0.30, 0.90, 0.25,    0, 0.45, 0.80, 0.45, 0.35, 0.45, 0.75, 0.85, 0.20, 0.50, 0.40, 0.45, 0.25 },
/*M*/   { 0.35, 0.80, 0.50, 0.55,    0, 0.90, 0.50, 0.30, 0.35, 0.75, 0.85, 0.25, 0.45, 0.55, 0.50, 0.30 },
/*P*/   { 0.05, 0.30, 0.10, 0.20, 0.10,    0, 0.15, 0.05, 0.10, 0.50, 0.60, 0.05, 0.20, 0.15, 0.25, 0.05 },
/*S*/   { 0.40, 0.75, 0.55, 0.55, 0.50, 0.85,    0, 0.25, 0.55, 0.70, 0.90, 0.45, 0.55, 0.60, 0.65, 0.40 },
/*C*/   { 0.50, 0.80, 0.60, 0.65, 0.70, 0.95, 0.75,    0, 0.65, 0.90, 0.95, 0.55, 0.40, 0.75, 0.80, 0.45 },
/*9*/   { 0.40, 0.60, 0.70, 0.55, 0.65, 0.90, 0.45, 0.35,    0, 0.75, 0.80, 0.45, 0.35, 0.65, 0.70, 0.50 },
/*0*/   { 0.15, 0.40, 0.20, 0.25, 0.25, 0.50, 0.30, 0.10, 0.25,    0, 0.65, 0.30, 0.15, 0.30, 0.30, 0.20 },
/*1*/   { 0.05, 0.20, 0.10, 0.15, 0.15, 0.40, 0.10, 0.05, 0.20, 0.35,    0, 0.05, 0.05, 0.10, 0.15, 0.10 },
/*2*/   { 0.55, 0.85, 0.75, 0.80, 0.75, 0.95, 0.55, 0.45, 0.55, 0.70, 0.95,    0, 0.65, 0.85, 0.90, 0.40 },
/*3*/   { 0.50, 0.70, 0.65, 0.50, 0.55, 0.80, 0.45, 0.60, 0.65, 0.85, 0.95, 0.35,    0, 0.80, 0.85, 0.60 },
/*4*/   { 0.30, 0.65, 0.50, 0.60, 0.45, 0.85, 0.40, 0.25, 0.35, 0.70, 0.90, 0.15, 0.20,    0, 0.75, 0.40 },
/*5*/   { 0.20, 0.65, 0.45, 0.55, 0.50, 0.75, 0.35, 0.20, 0.30, 0.70, 0.85, 0.10, 0.15, 0.25,    0, 0.30 },
/*6*/   { 0.45, 0.85, 0.65, 0.75, 0.70, 0.95, 0.60, 0.55, 0.50, 0.80, 0.90, 0.60, 0.40, 0.60, 0.70,    0 } };

int itisnot (int *a, int x) {                   // ищет число в массиве: если его нет - возвращает 1
    for (int i=0; i<m; ++i)
        if (a[i]==x) return 0;
    return 1;
}
void fill_ost (int *a, int *ost, int razm) {    // добавляет в массив2 только числа, которых нет в массиве1
    int k=1;
    for (int i=0; i<razm; ++i) {
        if (itisnot(a,k)) ost[i]=k;
        else --i;
        ++k;
    }
}
void sdvig (int *a, int razm) {                 // сдвигает массив вперёд на 1 (первый становится последним)
    int k=a[0];
    for (int i=0; i<razm-1; ++i) a[i]=a[i+1];
    a[razm-1]=k;
}
void copy (int *kuda, int *otkuda, int razm) {  // копирует массив2 в массив1
    for (int i=0; i<razm; ++i) kuda[i]=otkuda[i];
}
void show_mass(int *mass, int razm) {           // вывод массива
    for (int i=0; i<razm; ++i)
        printf (" %d  ", mass[i]);
    printf ("\n\n");
}
double formula (int *rasklad, int place, int N) {   // изначально N - количество игроков; i в main = place
    if (N/2==1) {
        if (place%2==0) return graf[rasklad[place]-1][rasklad[place+1]-1];
        else return graf[rasklad[place]-1][rasklad[place-1]-1];
    }
    double summ=0;
    int koef = (place/N)*N;
    if (place%N < (N/2)) {
        for (int i=N/2+koef; i<N+koef; ++i)
            summ += formula(rasklad, i, N/2)*graf[rasklad[place]-1][rasklad[i]-1];
        return summ*formula(rasklad, place, N/2);
    }
    else {
        for (int i=koef; i<N/2+koef; ++i)
            summ += formula(rasklad, i, N/2)*graf[rasklad[place]-1][rasklad[i]-1];
        return summ*formula(rasklad, place, N/2);
    }
}
int best_place (int *rasklad, int *ostpl, int *order, int *rask_our_best, int repeat) { // выбор лучшего места в раскладе
    if (repeat == 1) { // последний игрок занимает оставшееся место (0, т.к. массив сдвигали при передаче в функцию)
        rasklad[ostpl[0]-1]=order[0];
        return 0;
    }
    int *rask_best, BP=0;
    double vertBest=0, vert=0;
    rask_best = (int*)malloc(sizeof(int)*n);
    for (int i=0; i<repeat; ++i) {      // на каждое пустое место ставим игрока
        rasklad[ostpl[0]-1]=order[0];   // нового игрока (0) всегда ставим на 0, т.к. массивы order и ostpl сдвигаются
        best_place(rasklad,ostpl+1,order+1,rask_our_best,repeat-1);
        vert = formula(rasklad,ostpl[0]-1,n);
       /* if (repeat==n-m) {
            printf ("Вероятность победы %d игрока на месте %d: %f\nРакслад:", order[0], ostpl[0], vert);
            show_mass(rasklad,n);
        }*/
        if (vert>vertBest) {
            vertBest=vert;
            if (repeat==n-m) copy(rask_our_best,rasklad,n);
            else copy(rask_best,rasklad,n);
            BP=ostpl[0];
        }
        sdvig(ostpl,repeat);
    }
    copy(rasklad,rask_best,n);
    free(rask_best);
    return BP;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int igr[m], places[m], order[n-m], ostpl[n-m], rasklad[n], rask_our_best[n], BP;
    double ver=0;

// ввод игроков и мест из сетки, порядок жребия остальных игроков
    printf ("Введите номер игрока и его место (%d раз):\n", m);
    for (int i=0; i<m; ++i) scanf ("%d %d", &igr[i],&places[i]);
    for (int i=0; i<m; ++i) rasklad[places[i]-1]=igr[i];
    printf ("Введите номера остальных игроков в порядке жребия (наш первый):\n"); // наш = order[0]
    for (int i=0; i<n-m; ++i) scanf ("%d", &order[i]);
    fill_ost(places,ostpl,n-m);

    BP = best_place(rasklad,ostpl,order,rask_our_best,n-m);
    ver = formula(rask_our_best,BP-1,n);
    printf ("Лучшее место для участника %d: %d (вероятность победы: %f)\nРасклад: ", order[0],BP,ver);
    show_mass(rask_our_best,n);

return 0;
}

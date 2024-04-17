#include <stdio.h>
#include <locale.h>
#define n 16    // ��������� ���������� �������
#define m 7     // ������, ��� �������� ����� � �������
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

void swap (int *a, int *b) {            // �������� ������� ��� ��������
    int t = *a;
    *a = *b;
    *b = t;
}
void rand_perest (int *a, int razm) {   // ��������� ������������ ��������� �������
    int j;
    for (int i=razm-1; i>0; --i) {
        j = rand()%(i+1);
        swap(&a[i],&a[j]);
    }
}
int itisnot (int *a, int x) {           // ���� ����� � �������: ���� ��� ��� - ���������� 1
    for (int i=0; i<m; ++i)
        if (a[i]==x) return 0;
    return 1;
}
void fill_ost (int *a, int *ost, int razm, int our) {   // ��������� � ������2 ������ �����, ������� ��� � �������1
    int k=1;
    for (int i=0; i<razm; ++i) {
        if ((k!=our)&&(itisnot(a,k))) ost[i]=k;
        else --i;
        ++k;
    }
}
void perest_ost (int *pl, int *rasklad, int *ostigr, int razm, int our_pl) {   // ��������� ������� ���������� ��������
    // ������: places[0-3]-1, ostpl[i]-1 razm=n-m-1
    int k=0;
    for (int i=0; i<razm; ++i) {
        if ((k+1!=our_pl)&&(itisnot(pl,k+1))) rasklad[k]=ostigr[i];
        else --i;
        ++k;
    }
}
double formula (int *rasklad, int place, int N) { // ���������� N - ���������� �������; i � main = place
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

int main() {
    setlocale(LC_ALL, "Rus");
    int igr[m], places[m], ostigr[n-m-1], ostpl[n-m], rasklad[n], t=0, our,BP;
    double sred=0, ver=0;

// ���� ������� � ����, ���������� � ������� ����������
    printf ("������� ����� ������ � ��� ����� (%d ���):\n", m);
    for (int i=0; i<m; ++i) scanf ("%d %d", &igr[i],&places[i]);
    for (int i=0; i<m; ++i)
        rasklad[places[i]-1]=igr[i];
    printf ("������� ����� ������ ������:\n");
    scanf ("%d", &our);
    fill_ost(igr,ostigr,n-m-1,our);
    fill_ost(places,ostpl,n-m,0);

    for (int i=0; i<n-m; ++i) { // �� ������ ������ ����� ������ ������
        do {    // �������� ����������� ��� ������� �� ��� ������ t ���, ������� ����������� ������
            rand_perest(ostigr,n-m-1);
            rasklad[ostpl[i]-1]=our;
            perest_ost(places,rasklad,ostigr,n-m-1,ostpl[i]);
            ver += formula(rasklad,ostpl[i]-1,n);
            t++;
        } while (t<10000);
        printf ("������� ����������� ������ ��� ����� %d: %f\n", ostpl[i],ver/t);
        if ((ver/t)>sred) { // �������� ������ ����������� � �����
            sred = ver/t;
            BP = ostpl[i];
        }
        ver=t=0;
    }
    printf ("������ ����� ��� ��������� %d: %d (������� ����������� ������: %f)\n", our, BP,sred);

return 0;
}

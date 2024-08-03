#include <iostream>
#include <cstring>
#include <list>
#include <forward_list>
#include <print>

#define TYPE(typer) typer

struct Person {
    char a[20];
    char b[20];
             };
int f7(int a) {
    int n,k,s;
    for(n = a, s = 0; n!=0; n=n/10) {
        k = n%10;
        s = s + k;
    }
    return s;
}
int f9(int a) {
    int n,k,s;
    for(n = a, s = 0; n!=0; n=n/10) {
        k = n%10;
        s = s*10 + k;
    }
    return s;
}
char *f21(char * c, int &s) {
    int n; char * z, *p;
    for(; *c != 0; c++) {
        for(p = c, n = 0; *p != '\0'; p++) {
            if(*p == *c) n++;
        }
        if(n > s) {
            z=c; s=n;
        }
    }
    return z;
}
struct tree3 {
    int vv;
    tree3 *l, *r;
};
std::forward_list<int> F5(std::forward_list<int>& lst, int n) {
    auto it = lst.before_begin();
    auto prev = lst.before_begin();

    for (int i = 0; i < n && std::next(it) != lst.end(); ++i) {
        prev = it;
        it = std::next(it);
    }

    if (std::next(it) == lst.end()) {
        return lst;
    }

    if (prev == lst.before_begin()) {
        lst.pop_front();
    } else {
        lst.erase_after(prev);
    }

    return lst;
}
class Printer {
    std::string vendor;
    std::string paperSize;
public:
    Printer(std::string _vendor, std::string _paperSize) : vendor(_vendor), paperSize(_paperSize) {}
    Printer() { vendor = "123"; paperSize = "123"; }
};

int *F6(){
    int *p, n=10, i;
    p=(int*)malloc(n*sizeof(int));
    for (i=0;i<n;i++) {
        if (i==n) { n*=2; p=(int*)realloc(p,sizeof(int)*n); }
        scanf("%d",&p[i]);
        if (p[i]==0)
            break;
    }
    return p;
}

int main() {
    TYPE(int) a = 123;
    std::cout << "Hello, World!" << std::endl;
    /*std::cout << "RESULT F7: " << f7(7715) << std::endl;
    int s1 = 1;
    std::cout << "F21: '" << f21("a1aabcd", s1) << "'; S = " << s1 << std::endl;
    auto A3 = new tree3{1,NULL, NULL};
    auto B3 = new tree3{2,NULL, NULL};
    auto C3 = new tree3{3,A3, B3};
    auto D3 = new tree3{4,C3, NULL};
    tree3 *p3 = D3;
    int c1,c2;
    c2 = p3->l->r->vv;
    std::cout << "C2 = " << c2;
    std::forward_list<int> lst = {1, 5, 9, 11};
    F5(lst, 1);
    std::cout << "F5: " << std::endl;
    for (int value : lst) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    // 18
    Printer p;
    Printer p1("A3", "Epson");
    Printer p2("Epson", "A5");
    Printer p4("HP", "A4");
    std::cout << "RESULT F9: " << f9(3675) << std::endl;
    std::cout << "CYCLE NUMBER 13" << std::endl;
    int n = 6;
    int val = 72;
    int A[n];
    int i, s;

    for (i = 0; i < n - 1 && val != 1; i++) {
        for (s = 2; val % s != 0; s++);
        val /= s; A[i] = s;
    }
    A[i] = 0; // Завершающий элемент массива
    for (int j = 0; j <= i; j++) {
        std::cout << A[j] << " ";
    }
    std::cout << std::endl;*/


    // 2 6
    /*int k=0, b=-1, m=0;
    char c[] = "abcccca";
    for (i=0; c[i]!='\0'; i++) {
        if (c[i] == c[i+1]) {
            for (k=2; c[i] == c[i+k]; k++);
            if (k > m) {
                m = k;
                b = i;
            }
        }
    }
    std::print("K={}, B={}, C={}", k,b,m);*/
    // ------- 1 -------
    typedef enum Season {
        Winter = 10,
        Spring = 9,
        Summer,
        Autumn
    } Season;

    Season currSeason = Spring;

    // ------- 2 -------
    enum Status {
        Success = 1,
        Wait,
        Proceed,
        Error = -1
    };

    Status s;
    s = Proceed;
    // ------- 4 -------
    enum Status2 {
        Success1,
        Wait1,
        Proceed1,
        Error1
    };

    enum Status2 s2;
    s2 = Success1;
    return 0;
}

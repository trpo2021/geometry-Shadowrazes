#include <cmath>
#include <libgeometry/calculations.h>
#include <string>
#include <vector>

using namespace std;

const long double PI = acos(-1.0);

vector<double> sqrSum(double a, double b)
{
    vector<double> sq;
    sq.push_back(a * a);
    sq.push_back(2 * a * b);
    sq.push_back(b * b);
    return sq;
}

vector<double> sqrEq(vector<double> coef)
{
    vector<double> radical(0);
    struct abc {
        double a;
        double b;
        double c;
    };
    abc arg = {coef[0], coef[1], coef[2]};
    double d = arg.b * arg.b - 4 * arg.a * arg.c;
    if (d < 0)
        return radical;
    else if (d > 0) {
        radical.push_back((-arg.b + sqrt(d)) / (2 * arg.a));
        radical.push_back((-arg.b - sqrt(d)) / (2 * arg.a));
        return radical;
    } else if (d == 0) {
        radical.push_back(-arg.b / (2 * arg.a));
        return radical;
    } else
        return radical;
}

double lenCircle(double r)
{
    return 2 * PI * r;
}

double sqrCircle(double r)
{
    return PI * pow(r, 2);
}

double sqrTriangle(double p, vector<double> lines)
{
    double half = p;
    for (int i = 0; i < 3; i++) {
        half *= p - lines[i];
    }
    return sqrt(half);
}

pair<double, double>
vectCoord(pair<double, double> start, pair<double, double> close)
{
    pair<double, double> vect;
    vect.first = close.first - start.first;
    vect.second = close.second - start.second;
    return vect;
}

double lenLine(pair<double, double> start, pair<double, double> close)
{
    pair<double, double> vect = vectCoord(start, close);
    double leng = sqrt(pow(vect.first, 2) + pow(vect.second, 2));
    return leng;
}

bool cirTOcir(vector<double> cirf, vector<double> cirs)
{
    bool cross = 0;
    pair<double, double> start(cirf[0], cirf[1]);
    pair<double, double> close(cirs[0], cirs[1]);
    double distance = lenLine(start, close);
    if (distance <= cirf[2] + cirs[2] && distance >= abs(cirf[2] - cirs[2]))
        return cross = 1;
    else
        return cross;
}

bool trTOcir(vector<double> tr, vector<double> cir)
{
    int i, j, z;
    bool cross = 0;
    vector<double> x;
    vector<double> y;
    pair<double, double> q;
    for (i = 0; i < 6; i += 2) {
        q.first = tr[i + 2] - tr[i];      // X
        q.second = tr[i + 3] - tr[i + 1]; // Y

        x = sqrSum(q.first, tr[i] - cir[0]);
        y = sqrSum(q.second, tr[i + 1] - cir[1]);
        for (j = 0; j < 3; j++)
            x[j] += y[j];
        x[j - 1] -= cir[2] * cir[2];
        y = sqrEq(x);
        z = y.size();
        for (j = 0; j < z; j++)
            if (y[j] >= 0 && y[j] <= 1)
                return cross = 1;
    }
    return cross;
}

bool trTOtr(vector<double> trf, vector<double> trs)
{
    int i, j, z = trf.size(), m = trs.size();
    bool cross = 0;
    vector<double> x;
    vector<double> y;
    vector<double> tx;
    vector<double> ty;
    vector<double> point;
    pair<double, double> q;
    pair<double, double> qsec;
    for (i = 0; i < z - 2; i += 2) {
        q.first = trf[i + 2] - trf[i];      // X
        q.second = trf[i + 3] - trf[i + 1]; // Y
        x.push_back(q.first);
        y.push_back(q.second);
        for (j = 0; j < m - 2; j += 2) {
            x.push_back(trf[i]);
            y.push_back(trf[i + 1]);
            tx = x;
            ty = y;
            x[1] -= trs[j];
            y[1] -= trs[j + 1];

            qsec.first = trs[j + 2] - trs[j];      // X
            qsec.second = trs[j + 3] - trs[j + 1]; // Y

            x[0] *= qsec.second;
            x[1] *= qsec.second;
            y[0] *= qsec.first;
            y[1] *= qsec.first;

            x[0] -= y[0];
            x[1] -= y[1];

            double t = -x[1] / x[0];

            point.push_back(tx[0] * t + tx[1]);
            point.push_back(ty[0] * t + ty[1]);

            if (((trf[i] <= point[0] && point[0] <= trf[i + 2])
                 || (trf[i + 2] <= point[0] && point[0] <= trf[i]))
                && ((trf[i + 1] <= point[1] && point[1] <= trf[i + 3])
                    || (trf[i + 3] <= point[1] && point[1] <= trf[i + 1]))) {
                if (((trs[j] <= point[0] && point[0] <= trs[j + 2])
                     || (trs[j + 2] <= point[0] && point[0] <= trs[j]))
                    && ((trs[j + 1] <= point[1] && point[1] <= trs[j + 3])
                        || (trs[j + 3] <= point[1] && point[1] <= trs[j + 1])))
                    return cross = 1;
            }
            //проверка точки пересечения на принадлежность отрезку: от начала и
            //до конца || от конца и до начала, в обе стороны - т.к могут быть
            //разные направления векторов

            x.pop_back();
            y.pop_back();
            point.clear();
            x[0] = q.first;
            y[0] = q.second;
        }
        x.clear();
        y.clear();
        tx.clear();
        ty.clear();
    }
    return cross;
}

vector<vector<int>> intersects(
        vector<pair<string, vector<double>>> flist, vector<vector<int>> inter)
{
    int i, j, z = flist.size();
    bool cross = 0;
    vector<int> repeat;
    for (i = 0; i < z; i++) {
        for (j = i + 1; j < z; j++) {
            if ((flist[i].first == "triangle" && flist[j].first == "circle")
                || (flist[i].first == "circle"
                    && flist[j].first == "triangle")) {
                if (flist[i].first == "circle")
                    cross = trTOcir(flist[j].second, flist[i].second);
                else
                    cross = trTOcir(flist[i].second, flist[j].second);
                if (cross) {
                    inter[i].push_back(j);
                    inter[j].push_back(i);
                }
            } else if (
                    flist[i].first == "triangle"
                    && flist[j].first == "triangle") {
                if (trTOtr(flist[i].second, flist[j].second)) {
                    inter[i].push_back(j);
                    inter[j].push_back(i);
                }
            } else if (
                    flist[i].first == "circle" && flist[j].first == "circle") {
                if (cirTOcir(flist[i].second, flist[j].second)) {
                    inter[i].push_back(j);
                    inter[j].push_back(i);
                }
            }
        }
    }
    return inter;
}

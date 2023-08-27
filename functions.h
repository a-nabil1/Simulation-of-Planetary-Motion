#include <vector>
#include "bodyClass.h"

void readFile(vector<bodyClass>& bodies, double& G, double& T, double& dt);
vector<bodyClass> f(vector<bodyClass> bodies, double G);
vector<bodyClass> addBodyVector(vector<bodyClass> yVec, vector<bodyClass> kVec, double divisor);
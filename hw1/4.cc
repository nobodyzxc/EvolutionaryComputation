#include <cstdio>
#include <cstdlib>
#include <time.h>

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

#define ULL unsigned long long

using namespace std;

template <typename FitType, typename BinRepr> class GA {
public:
  GA(ULL size, FitType (*eval)(BinRepr)) {
    popsize = size;
    evaluate = eval;
    fitness = new FitType[popsize];
    selected = new BinRepr[popsize];
    population = new BinRepr[popsize];
  }

  ~GA() {
    delete[] fitness;
    delete[] selected;
    delete[] population;
  }

  void random_initialize() {
    for (ULL i = 0; i < popsize; i++)
      population[i].random_initialize();
  }

  void select_parent() {
    vector<FitType> expect;
    for (ULL i = 0; i < popsize; i++)
      expect.push_back(FitType((totfit)*rand() / (RAND_MAX + 1.0)));
    /* expect element: [0, totfit) */
    sort(expect.begin(), expect.end());

    ULL sel = 0, base = 0;
    for (ULL i = 0; i < popsize; i++) {
      while (expect[i] >= base + fitness[sel])
        base += fitness[sel], sel++;
      selected[i].copy(population[sel]);
    }
  }

  void recombination() {
    for (ULL i = 0; i < popsize / 2; i++) {
      ULL end = rand() % selected[i].size();
      selected[i].crossover(0, end, selected[popsize - 1 - i]);
    }
    swap(selected, population);
  }

  void run(ULL generations) {
    random_initialize();
    for (ULL g = 0; g < generations; g++) {
      for (ULL i = 0; i < popsize; i++)
        fitness[i] = evaluate(population[i]);

      totfit = accumulate(fitness, fitness + popsize, 0);
      ULL king = max_element(fitness, fitness + popsize) - fitness;

      log_king(g, generations, fitness[king], population[king]);
      select_parent();
      recombination();
    }
  }

private:
  FitType (*evaluate)(BinRepr);
  BinRepr *population, *selected;
  ULL popsize;
  FitType totfit, *fitness;
};

template <ULL array_size> class fixedBoolArray {
public:
  fixedBoolArray() { data = new bool[array_size]; }
  void copy(fixedBoolArray<array_size> &c) {
    for (ULL i = 0; i < array_size; i++)
      data[i] = c.data[i];
  }
  bool at(unsigned int idx) { return data[idx]; }
  void random_initialize() {
    for (ULL i = 0; i < array_size; i++)
      data[i] = rand() % 2;
  }
  ULL size() { return array_size; }
  void crossover(ULL beg, ULL end, fixedBoolArray<array_size> &mate) {
    while (beg != end)
      swap(data[beg], mate.data[beg]), beg++;
  }
  void show() {
    for (ULL i = 0; i < size(); i++) {
      printf("%d", data[i]);
    }
    puts("");
  }

private:
  bool *data;
};

template <typename BinRepr> ULL oneMax(BinRepr expr) {
  ULL acc = 0;
  for (ULL i = 0; i < expr.size(); i++)
    acc += expr.at(i);
  return acc + 800;
}

template <typename BinRepr>
void log_king(int gidx, int gtot, int score, BinRepr expr) {
  printf("%d%c", score, gidx == gtot - 1 ? '\n' : ',');
}

#define RepType fixedBoolArray<60>
int main() {
  srand(time(NULL));
  GA<ULL, RepType> ga(500, oneMax);
  int rounds = 10;
  while (rounds--)
    ga.run(200);
}

#include <cstdio>
#include <cstdlib>
#include <time.h>

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

#define ULL unsigned long long

using namespace std;

template <typename BinRepr, typename Eval> class GA {
public:
  GA(ULL size, Eval eval) {
    popsize = size;
    evaluate = eval;
    fitness = new ULL[popsize];
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
    const unsigned int k = 2;
    for (ULL i = 0; i < popsize; i++) {
      ULL sel = 0, maxfit = 0;

      set<ULL> sample;
      while (sample.size() < k)
        sample.insert(rand() % popsize);

      for (auto s = sample.begin(); s != sample.end(); s++) {
        if (fitness[*s] > maxfit)
          maxfit = fitness[*s], sel = *s;
      }

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
  Eval evaluate;
  BinRepr *population, *selected;
  ULL totfit, popsize, *fitness;
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

template <typename BinExpr> ULL oneMax(BinExpr expr) {
  ULL acc = 0;
  for (ULL i = 0; i < expr.size(); i++)
    acc += expr.at(i);
  return acc + 800;
}

template <typename BinExpr>
void log_king(int gidx, int gtot, int score, BinExpr expr) {
  printf("%d%c", score, gidx == gtot - 1 ? '\n' : ',');
}

#define RepType fixedBoolArray<60>
int main() {
  srand(time(NULL));
  GA<RepType, ULL (*)(RepType)> ga(500, oneMax);
  int rounds = 10;
  while (rounds--)
    ga.run(200);
}

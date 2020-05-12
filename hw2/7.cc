#include <cstdio>
#include <cstdlib>
#include <time.h>

#include <numeric>
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
#include <random>

#define ULL unsigned long long

using namespace std;

template <typename T>
vector<size_t> sort_indexes(const T &v, size_t size) {
  vector<size_t> idx(size);
  iota(idx.begin(), idx.end(), 0);
  stable_sort(idx.begin(), idx.end(),
      [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
  return idx;
}

template <typename FitType, typename RValVec> class ES {
  public:
    ULL stopGen;
    ES(ULL psize, char notat, ULL csize, FitType (*eval)(RValVec), double sig, ULL g, double al) {
      init_sigma = sig;
      popsize = psize;
      notation = notat;
      childsize = csize / psize;
      G = g, alpha = al;

      if(notation == ',')
        spwansize = csize;
      else if(notation == '+')
        spwansize = csize + psize;
      else
        puts("notation sould be ',' or '+'"), exit(1);

      evaluate = eval;
      fitness = new FitType[spwansize];
      population = new RValVec[popsize];
      competitors = new RValVec[spwansize];
      sigmas = new double[RValVec::size()];
    }

    ~ES() {
      delete[] fitness;
      delete[] competitors;
      delete[] population;
      delete[] sigmas;
    }

    void const_initialize(FitType x) {
      for (ULL i = 0; i < popsize; i++)
        population[i].const_initialize(x);
    }

    void selection() {
      ULL i = 0, select_mut = 0;
      for (auto idx: sort_indexes(fitness, spwansize)) {
        if(i >= popsize) break;
        //printf("idx = %lu\n", idx);
        if(idx < popsize * childsize) select_mut++;
        population[i++].copy(competitors[idx]);
      }
      Gacc++;
      if(select_mut >= spwansize / 2) Gs++;
    }

    void recombination() {

      if(Gacc >= G){
        double frac = double(Gs) / double(Gacc);
        //printf("%lld / %lld = %lf\n", Gs, Gacc, frac);
        Gs = Gacc = 0;
//#define uniq
#ifdef uniq
        if(frac > 0.2)
          for(auto i = 0llu; i < RValVec::size(); i++)
            sigmas[i] = sigmas[i] / alpha;
        else if(frac < 0.2)
          for(auto i = 0llu; i < RValVec::size(); i++)
            sigmas[i] = sigmas[i] * alpha;
#else
        if(frac > 9.2){
          sigma = sigma / alpha;
        }
        else if(frac < 0.2){
          sigma = sigma * alpha;
        }
        //printf("frac = %lf, sigma = %lf\n", frac, sigma);
#endif
      }

      for (ULL i = 0; i < popsize; i++) {
        for(ULL j = 0; j < childsize; j++){
          for(ULL k = 0; k < competitors[i].size(); k++){
#ifdef uniq

            competitors[i * childsize + j].at(k) = population[i].at(k) + sigmas[k] * (*distribution)(generator);
#else

            competitors[i * childsize + j].at(k) = population[i].at(k) + sigma * (*distribution)(generator);

#endif
          }
        }
      }
      if(notation == '+'){
        for (ULL i = 0; i < popsize; i++) {
          competitors[popsize * childsize + i].copy(population[i]);
        }
      }
    }

    void init(){
      const_initialize(1);
      sigma = init_sigma;
      //printf("init sigma = %lf\n", sigma);
      for(auto i = 0llu; i < RValVec::size(); i++)
        sigmas[i] = init_sigma;
      Gacc = Gs = 0;
    }

    void run(ULL generations, FitType diff) {

      init();

      if(distribution) delete distribution;
      distribution = new normal_distribution<double>(0, 1);
      for (stopGen = 0; stopGen < generations; stopGen++) {
        recombination();
        for (ULL i = 0; i < spwansize; i++)
          fitness[i] = evaluate(competitors[i]);
        if(*min_element(fitness, fitness + spwansize) < diff) return;
        selection();
      }
    }

    void summary(){
      printf("val = %lf, gen = %llu\n", *min_element(fitness, fitness + spwansize), stopGen);
    }

  private:
    std::default_random_engine generator;
    std::normal_distribution<double> *distribution = nullptr;
    FitType (*evaluate)(RValVec);
    RValVec *population, *competitors;
    FitType totfit, *fitness;
    double *sigmas, sigma, init_sigma;
    ULL popsize, spwansize, childsize, G, Gs, Gacc;
    double alpha;
    char notation;
};

template <ULL array_size> class fixedRealVector {
  public:
    fixedRealVector() { data = new double[array_size]; }
    void copy(fixedRealVector<array_size> &c) {
      for (ULL i = 0; i < array_size; i++)
        data[i] = c.data[i];
    }
    double &at(unsigned int idx) { return data[idx]; }
    void const_initialize(double x) {
      for (ULL i = 0; i < array_size; i++)
        data[i] = x;
    }
    static ULL size() { return array_size; }
    void crossover(ULL beg, ULL end, fixedRealVector<array_size> &mate) {
      while (beg != end)
        swap(data[beg], mate.data[beg]), beg++;
    }
    void show() {
      for (ULL i = 0; i < size(); i++) {
        printf("%lf ", data[i]);
      }
      puts("");
    }

  private:
    double *data;
};

template <typename RVV> double NDsphere(RVV vec) {
  double acc = 0;
  for (ULL i = 0; i < vec.size(); i++){
    acc += vec.at(i) * vec.at(i);
  }
  return acc;
}

template <typename RVV>
void log_king(int gidx, int gtot, int score, RVV expr) {
  printf("%d%c", score, gidx == gtot - 1 ? '\n' : ',');
}

#define RepType fixedRealVector<10>
int main() {
  srand(time(NULL));

  puts("| (1+1)-ES | σ = 0.010 | σ = 0.100 | σ = 1.000 |");
  puts("|:--------:|:---------:|:---------:|:---------:|");

  int G = 20;
  double alpha = 0.82; /* [0.817, 1] [0.85, 1) */
  ES<double, RepType> es_cov_a(1, '+', 1, NDsphere, 0.01, G, alpha);
  ES<double, RepType> es_cov_b(1, '+', 1, NDsphere, 0.1, G, alpha);
  ES<double, RepType> es_cov_c(1, '+', 1, NDsphere, 1, G, alpha);
  for(int rounds = 0; rounds < 10; rounds++, puts("")){
    printf("| Run  #%02d |", rounds + 1), fflush(stdout);
    es_cov_a.run(1e7, 0.005), printf(" %9llu |", es_cov_a.stopGen), fflush(stdout);
    es_cov_b.run(1e7, 0.005), printf(" %9llu |", es_cov_b.stopGen), fflush(stdout);
    es_cov_c.run(1e7, 0.005), printf(" %9llu |", es_cov_c.stopGen), fflush(stdout);
  }
  return 0;
}

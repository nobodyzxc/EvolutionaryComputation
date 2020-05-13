# Evolutionary Computation HW#2

1. Discuss why generational GAs and ES form opposites regarding wherethe fitness information influences the search.

   There are two selection in ES, parent selection and survivor selection, and survivor selection is more important than parent selection in ES. While for GA, there are only parent selection. Fitness information is used in ES's survivor selection and GA's parent selection, that's the mainly difference.

   ES mainly depends on mutation, while GA is the crossover. ES uses the distribution in parent selection, in ES the whole population is seen as parent - often called parent population. After the parent selection, we do the mutation, and the fitness information is used to do the survivor selection. While for GA, the "parent" denotes the member of the population that has been selected by fitness information to undergo variation (crossover or mutation).

   In short, GA uses fitness to select good parent, then do crossover to generate better child; ES does the mutation first, then uses fitness to select which mutation is good.

2. How the frequency change?
   1. Because the one-point crossover swap the bit from the two parents to generate the new two children, so after k operations, it wouldn't change the frequency of the population, that means it retains the 35% of 1 and 65% of 0.
   2. For the uniform crossover, the probability children get per bit from the two parent is equal. We have 4 cases here:

      - 65%(1) * 65%(1) = 0.4225 (1)
      - 65%(1) * 35%(0) = 0.11375 (1) + 0.11375 (0)
      - 35%(0) * 65%(1) = 0.11375 (1) + 0.11375 (0)
      - 35%(0) * 35%(0) = 0.1225 (0)

      Let's do the summation for child:
      - (0) 0.11375 + 0.11375 + 0.1225 = 0.35
      - (1) 0.4225 + 0.11375 + 0.11375 = 0.65

      We can found that, after one round, the probability remains the same, so after k round, the probability is still the same, that means it retains the 35% of 1 and 65% of 0.

3. (1+1)-ES and (1,1)-ES are as follows.

{tab3}


4. In the (1+1)-ES, it needs more generations to achieve convergence along with the bigger sigma. It shows the 0.01 is the most proper step size of the three. While for the (1,1)-ES, even with the 1e7 generations, it still cannot converge. Because (1,1)-ES is the random walk, it always selects the mutated child and drops the parent, survivor selection doesn't work on it. That's why (1+1)-ES may converge on proper step size, while (1,1)-ES not.


5. The uncorrelated Gaussian mutation is as follows.

  ```C
  double n = 10, ratio = 9;
  double τ = 1.0 / sqrt(2 * sqrt(n)) * ratio;
  double τ′ = 1.0 / sqrt(2 * n) * ratio;
  ```

  |  τ  |  τ′ |  ε0  |
  |:---:|:---:|:----:|
  |3.578|2.012| 1e-5 |

{tab5}


6. As answer (4) mentioned, because of the improper step size (sigma), convergence becomes harder. While in the uncorrelated Gaussian mutation, the step sizes have the self-adaption ability, once it found the proper step size, the convergence will be faster, that's why it needs less generations when sigma = 0.1 or 1. But when sigma = 0.01, (3)'s generations is still less than (5). Because the step sizes continue varying, it cannot stay in the proper step size. It may be the reason why the result of (3) is better than (5), because continue using the 0.01 as step size is more proper than the varying step size.

  (the (1,1)-ES result remains the same because of the same reason stated in answer (4))


7. The 1/5-rule results are as follows.

  |  G  |   a  |
  |:---:|:----:|
  |  20 | 0.82 |

{tab7}

8. 1/5-rule has better self-adaption ability than my uncorrelated implementation. I printed the step sizes of each generation of uncorrelated implementation, I found it varying like a wave, the value continue changing between two boundary. While for the 1/5-rule, in the sigma = 0.01 test, the step size remains the same in all generation, and for the other two test (sigma = 0.1 and 1), the sigma change to 0.02 and 0.04 in the last generation, both of them seems like to converge toward to 0.01. Because 1/5-rule makes the step size converge to a proper size, so it needs less generations than uncorrelated implementation.

  For the performance in the test sigma = 0.01, the 1/5-rule is as good as constant sigma implementation. But the more interesting thing is that the performances of other two test is better than all previous test in the 1/5-rule. It may caused by the initial step size set in the two test. Because the initial step size is large enough, it accelerated the convergence, while the target is approaching, it reduced the step size continuously to prevent exceeding the target. The whole process reduces the generations they needed successfully. (sigma = 1 may be too large as the initial step size, so the result is bad than 0.1)

  (the (1,1)-ES result remains the same because of the same reason stated in answer (4))

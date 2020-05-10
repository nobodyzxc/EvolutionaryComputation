# Evolutionary Computation HW#1

1. The eight queen problem
   - ( a ) C(64, 8) = 64! / (8! * 56!) = 4426165368
   - ( b ) permutation of the numbers 1 to 8
   - ( c ) P(8, 8) = 40320
   - ( d ) In 8 queen problem, the board is consisted of 8x8 cells, and the genotype is 8 cells where every cell is the number between 1 to 8. With the condition that a column can only exist one queen, the genotype can obvious mapping to the phenotype. and the row constraints can qualify the genotype into the permutation of number 1 to 8. 

2. Because of the need of precision within 0.001, the all possible value is from 0.000 to 1.000, totally 1001 values. ceil(log2(1001)) = 10, so we need 10 bits to achieve this precision for a bit-string genetic algorithm.

3. Apply roulette wheel selection on one max problem.

![figure of problem 3](img/3.png)


4. Apply roulette wheel selection on revised one max problem (add 800 as offset).

![figure of problem 4](img/4.png)

5. By the figure below, we can find that the algorithm can approach to the best fitness in original one max problem. While in the revised one max problem (which add 800 as offset), the algorithm cannot find the optimal solution. The reason is that the selection mechanism of roulette wheel selection is based on the probability computed by the fitness value. When we add a big offset on the population, it makes the probability been selected of every individual more equally. For example, assume we have a population whose fitness value is [1, 2, 7, 10], the probability would be [0.05, 0.1, 0.35, 0.5]. If we add a big offset 245 to it, the new fitness would be [246, 247, 252, 255], and the probability would be [0.246, 0.247, 0.252, 0.255]. From the example, we can see the offset make the probability of four individual almost the same. The avoid such kind of problem, we can do the normalization on the fitness before we apply roulette wheel selection.

![comparison of problem 3 and 4](img/3n4.png)

6. Apply tournament selection on one max problem.

![figure of problem 6](img/6.png)

7. Apply tournament selection on revised one max problem (add 800 as offset).

![figure of problem 7](img/7.png)

8. By the figure below, we can find the two fitness growth rate is very similar. That means the tournament selection can generally performed on original and revised one max problem perfectly.

![comparison of problem 6 and 7](img/6n7.png)

9. Through the following figure, we can find that the tournament selection can reach convergence earlier. This means that in one max problems, tournament selection has better selection capabilities than roulette wheel selection. Judging from the comparison of the original and revised one max problem, the tournament selection is more general than the roulette selection.

![summary](img/summary.png)

# Evolutionary Computation HW#2

1. fitness information is used on the selection, while the mainly selection strategy on ES is survival selection, and the GA is parent selection.

2. How the frequency change?
   - Because the one-point crossover swap the bit from the two parent to generate the new two children, so after k operations, it wouldn't change the frequency of the population, that's retain the 35% of 1 and 65% of 0.
   - For the uniform crossover, the probability children get per bit from the two parent is equal. We have 4 cases here:

      - 65%(1) * 65%(1) = 0.4225 (1)
      - 65%(1) * 35%(0) = 0.11375 (1) + 0.11375 (0)
      - 35%(0) * 65%(1) = 0.11375 (1) + 0.11375 (0)
      - 35%(0) * 35%(0) = 0.1225 (0)

   - Let's do the summation for child:
      - (0) 0.11375 + 0.11375 + 0.1225 = 0.35
      - (1) 0.4225 + 0.11375 + 0.11375 = 0.65


3. 

4. 

5. 

6. 

7. 

8. 

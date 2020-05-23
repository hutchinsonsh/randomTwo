This is my second attempt at a random number generator. This PRNG uses the linear congurential generator.
I used a double circular linked list to sort each generated number in numerical order to cut down on search time(and because i've never used them before and thought it would be fun. it wasn't) and array to place each number in the order it was generated.
this code
    1. takes original number- the 'seed'
    2. uses the formula : newNum = (a*seed + c) mod m, where a, c, and m are variables
    3. the new number is placed in the linked list and array in the order described above
    4. if that number has already been generated, meaning that the generator will go into a loop, the code stops
    5. if it hasn't been used, the number is passed on as the new seed
    This process is repeated until either 1) a number is repeated or 2) it reaches the specified number of digits it needed to reach. In my test cases, I set it to 200 numbers since the run time for searching was n/2, which isn't great.
    
    
Problems: the wiki page for this PNG gave variables for a, c, and m. However, even w/ a long variable, overflow occured pretty easily for this program, meaning that I made up my own numbers for the variables- which meant that it didn't take long for there to be repeats. But oh well. 
Also, sidenote, the code for linked list/array is just copied from my randomOne repository. 

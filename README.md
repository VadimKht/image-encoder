# Image encoder
Using Sean Barrett's image loading and writing tools i wrote an app that encodes a-z and spacebar letters into pixels, by dividing each RGB component by 27 values in range of 0-255 (9 brightness pixels each, in case if compression messes up the colors a bit). Each pixel contains 3 letters, any pixel color thats over 252 value counts as nothing and is discarded. The encoding always tries to be cubic.  
Repo used: [https://github.com/nothings/stb](https://github.com/nothings/stb)
# How to use
First of all compile it using     
`gcc main.c -lm -o main`  
(-lm is for math libraries)  
Then type:  
`./main --help`  
For basic functionality.     
Write data into txt file and use it as input - no new lines, no numbers, only a-z and spacebar.
Can also technically read image no matter what pixels they are, if the image isn't too bright it will just type letters out.  
Only uses png but it's easy to make it read other values just by changing source code a bit.
### Example 
Put `aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz   ` inside input.txt and then open console and type:  
`./main e input.txt`  
You will be able to see an output.png file in the same folder. It will be a grey gradient with brightness difference of around 9 per step

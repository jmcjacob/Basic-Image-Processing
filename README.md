<h1>Basic Image Processing Challenge</h1>

The challenge given was to use object orientated principles in order to design and implement an application that using the Nearest-Neighbour Search to complete two tasks. The first task the application should be able to unshuffle a 512 by 512 image of University of Lincoln logo was shuffled into block of 32 by 32. This image was accompanied by a fixed logo image with lots of noise. The task required cleaning the noisy image then comparing blocks from the cleaned image and comparing each 32 by 32 block from the cleaned image to all the blocks in the shuffled image. A new matrix will then be created and will set the block from the shuffled image to the location of the cleaned block in the new image. 

The second task is to locate Wally in a scene from Where’s Wally. Two images were provided a 768 by 1024 scene from Where’s Wally and a 49 by 36 image of Wally. To solve this task the Wally image is compared to blocks from the scene and once the closest match is found the area on the scene is then highlighted.

<h2>Matrix Class</h2>
A matrix class has been developed for the application that will hold the data of the images and will allow for the addition of methods that will deal with the data. This means the data for the images will be easier to manage as it will be done through the bespoke matrix class. The matrix class will be treating a one dimensional array as a two dimensional array. The matrix class is located in a header file as well as all the member functions. This is because the matrix class implements templates and for templates to be properly linked together the class declaration and the member functions need to be in the same header file.

<h3>Template</h3>
Templates have been implemented in the class so that any piece of data declared of `type t` will change depending on the data type that has been identified when creating a Matrix object. This allows the matrix to hold any sort of data making it much more reusable.

<h3>Data Members</h3>
The Matrix class has three data members. The first is an integer named `M` that will hold the number of rows in the matrix. The second is another integer names `N` that will hold the number of columns in the matrix. The third is a pointer that will change its data type depending on the template called data. This pointer will hold a one dimensional array and will be the main source of data in the program. Each of the data members have been declared as protected so that they can only be accessed by member functions of the class and classes with friendship.

<h3>Constructors</h3>
The matrix class uses three different constructors, a blank constructor, a constructor that takes two integers and a `t` value and another constructor that takes two constructors that takes two integers and a `type t` pointer that points to an array. These constructors are initialised when creating an object and the constructor that will be invoked will depend on the inputs given. The blank constructor is used for creating placeholder matrixes. The constructor that takes `M`, `N` and a `t` value will set the inputted `M` and `N` to the `M` and `N` of the object then allocate memory to data and set every location in that memory to the `t` value. 
```C++
M = inputtedM
N = inputtedN
Data = new t[M*N]
for(i = 0; i < M*N; i++)
  data[i] = inputtedData[i]
```

<h4>Copy Constructors</h4>
The matrix class has a copy constructor that will take a constant matrix reference into it. The copy constructor will set the matrix its running off equal to the inputted matrix copying the values.

<h3>Destructor</h3>
The destructor will be called when an object goes out of scope. The destructor will then delete the data that the matrix class has used. This helps make sure that the memory that the application creates is dealt with and does not cause an excessive amount of memory usage.

<h3>Get and Set</h3>
The Matrix class has two methods called `get` and `set`. The get function will accept two integers `i` and `j`. `i` will refer to a row and `j` will refer to a column and the method will return a value of type t from the according location in the array. Get is a constant function and calculates the data to return using the formula `i * N + j`.

The Set method takes three arguments two integers `i` and `j`, and a value of `type t`. The method goes to the location as determined by `i * N + j` then sets the inputted value to the position. As the function does not need to return anything it has the return type `void`.

<h3>GetM, GetN and GetData</h3>
The three methods all take no arguments. `GetM` and `GetN` both have the return type integer and will return the values `M` or `N`. `GetData` will return a `t` pointer that will point to the memory that has been allocated for the matrix object. 

<h3>GetBlock</h3>
The `GetBlock` method is a constant function that takes four integer arguments, `startRow`, `endRow`, `startColumn` and `endColumn`. The method will return a matrix that is a block from the matrix it has been called argument and then the method will return the newly created matrix.The constructor that takes `M`, `N` and a `t` pointer will also set the inputted `M` and `N` to the `M` and `N` of the object then allocate memory to data and then set every element of data to the according element of the inputted array. This can be implemented as according to the following example.
```C++
A = eR – sR + 1
B = eC – sC + 1
block = new t[A*B]
for(i = 0; i < A; i++)
  for(j = 0; j < B; j++)
    block[i*B+j] = data[(i+sC)*N+(j+sR)]
return Matrix(A, B, block)
```
 The method starts by declaring two integers `A` and `B` by finding the difference of rows plus one and the difference of columns plus one. An array will then be created of size `A` multiplied by `B`. This array will then be populated by the values of from the matrix calculated by `(i + startColumn) * N + (j + startRow)`. A matrix will then be made using the array as an argument and then the method will return the newly created matrix.

<h3>SetBlock</h3>
The SetBlock method is a void method and takes three arguments, `startRow`, `startColumn` and the matrix you want setting. The method will then have a nested for loop taking `M` and `N` from the inputted matrix then setting the value from the inputted matrix from position `i` and `j` to the location at `(i + startColumn) * N + (j + startRow)`.

<h3>Operators +, -, *, /</h3>
The operator overloads for the matrix class all work in the same way as they are declared `virtual` so they can be overridden for later and will return a matrix. Each will take one argument a constant Matrix reference. The method will then declare an array of `type t` and allocate it `M * N` worth of memory and will then go through every element of each matrix and will either add, subtract, multiply or divide depending on what operator is loaded. Although this is not the correct way to multiply or divide matrices it is functional and serves a purpose.
```C++
result = new t[M*N]
for(i = 0; i < M*N; i++)
 result[i] = data[i] + m.data[i]
return Matrix(M, N, result)
```

<h3>Operator ++ and –</h3>
The two operator overloads `++` and `--` will increment and decrement every value in a matrix by one. The two overload methods have a return type of `void` and take no arguments. The method will then loop through every value and either subtract one or add one to the current value.

<h3>Operator ()</h3>
The `()` operator overload takes two integer arguments `i` and `j` and returns a `t` value. It does this by returning a value from data using the formula `i * N + j`.

<h3>Operator =</h3> 
The operator overload for `=` will set the value of one matrix to another matrix. Its return type is a matrix reference and takes on argument a constant matrix overload. It will do this by first deleting the data of the first matrix. Then it will set the matrix `M` and `N` to the other matrix’s `M` and `N`. It then allocates memory sized `M*N` for data and sets each of its values in data equal to the values in the other matrix’s data. After this has been done the operator will then return the pointer of matrix.

<h3>Sum of Squared Differences</h3>
The `SSD` method takes a matrix as an argument; it will then return a double that will be the `SSD` score of the matrix and the inputted matrix. The method dose this by first declaring a double that will hold the answer followed by loops that will take the find the difference of each element and square the difference then add it to the answer. Once the loop is completed it the method will then return the answer.
```C++
double answer = 0
for(i = 0; i < M*N; i++)
 if(data[i] & m.data[i] != 255)
 answer += (data[i] – m.data[i])^2
return answer
```

<h3>Mean</h3>
This is a method that takes no arguments and returned a double that holds the mean of the matrix. The method calculates the mean by using a loop to add every element of the matrix then dividing the result by how many elements it has. The method then returns the calculated mean value.

<h3>Normalised Correlation</h3>
The `NC` method just like the `SSD` method takes one argument and returns a double. The resulting double will be `NC` score of the two matrices; it is calculated by fist finding the mean of each matrix. Three doubles are then declared and set to zero.A loop then goes through every element of the matrix and minus the mean of from the element. For the first double the value of each element minus the mean multiplied by the element of the second matrix minus its mean is then added to the part. The second and third and the entire matrix element minus the mean squared. After the loop is finished the method will then return `part1` divided by the square root of `part2` and `part3` multiplied together. This will result in a Normalised Correlation score ranging from -1 to 1.
```C++
meanA = mean() meanB = T.mean()
part1 = 0; part2 = 0; part3 = 0;
for (i = 0; i < M*N; i++)
  A = data[i] - meanA
  B = T.data[i] - meanB
  part1 += A * B;
  part2 += pow(A,2)
  part3 += pow(B,2)
return part1 / sqrt(part2*part3)
```

<h3>Print</h3>
The print method in the matrix class takes no arguments and doesn’t return anything; it only prints values to the console for testing purposes. It starts by printing the number of rows and columns then prints the entire content of the matrix with the correct rows and columns.

<h2>BinaryImage</h2>
The binary image class is created in order to deal with black and white images. The class is also to make a grey scale image into a black and white image by giving a threshold.

<h3>Inheritance</h3>
The BinaryImage class inherits from the matrix class this means that all the data members and member functions except constructors and destructors of Matrix will work for BinaryImage. As BinaryImage is derived from Matrix it can be used in place for a Matrix in cases such as inputs.

<h3>Template</h3>
Templates have been added BinaryImage for the same reasons as why they have been added to Matrix. They also function the same way.

<h3>Constructors</h3>
There are three constructors the BinaryImage class, a blank constructor, one takes two integers and a `t` pointer array and one that takes four arguments two integers, `t` pointer array and a double. The blank constructor is made so that BinaryImages can be called without values. The second constructor calls the matrix constructor with the two integers and the pointer array. It does this because they need to do the same thing and as BinaryImage is derived from Matrix it can be done. The third constructor also calls the Matrix constructor.

<h3>Copy Constructor and Destructor</h3>
The copy constructor calls the Matrix copy constructor as they do they need to carry out the same process. The destructor deletes the memory used by the data pointer.

<h3>GetBlock</h3>
The BinaryImage class also includes its own `GetBlock` method that it overwrites from the Matrix `GetBlock` from that will return a block `BinaryImage` from another `BinaryImage`. The process of this works the same way as the Matrix `GetBlock`.

<h3>Operators +, -, *, /</h3>
The `BinaryImage` has three operator overloads that it overwrites from the `Matrix` class. Each of these overloads takes one `BinaryImage` as an argument. The operators then perform logic checks on the two `BinaryImages` and then returns a Boolean value. The `+` operator preforms the `OR` operation, the `–` operator performs the `XOR` operation, the `*` operator performs the `AND` operation and the `/` operator preforms the `NOR` operation.

<h2>Main Body</h2>
<h3>Task 1 SSD</h3>
In the main body of the application, the function `Task1SSD` takes two double pointer arguments one for each image the task needs to use. The function starts off by declaring two `BinaryImages` with type double for the two inputted double pointers, these will hold that two 512 by 512 images shuffled and noisy. The noisy image is created with a threshold of 170 so it image with noise gets cleaned. Two more Matrix’s are created using the blank constructor that will store the blocks from each image. Nester for loops will then cycle through the cleaned image getting 32 by 32 blocks from the cleaned image. A `SSD` variable will then be set to a high number. More nested loops then go through each shuffled block. The `SDD` is then calculated between the two blocks and if the score is lower than the `SSD` variable it will then set the `SSD` variable to the score and set the shuffled to the position of the cleaned block in the cleaned image. If then `SSD` was o indicating an exact match the program will then exit the loop and go to making a new `cleanedBlock`. After every block has been set the program will then write the cleaned matrix to a PGM file.
```C++
BinaryImage Shuffled(shuffedData)
BinaryImage Cleaned(noisyData, 170)
Matrix shuffledBlock Matrix cleanedBlock
for(ci = 0; ci < 512; ci++)
  for(cj = 0; cj < 512; cj++)
    cleanedBlock = Cleaned.getBlock(ci,cj)
    SSD = 1000;
    for(si = 0; si < 512; si++)
      for(sj = 0; sj < 512; sj++)
        shuffledBlock = Shuffled.getBlock(si,sj)
        current = shuffledBlock.SSD(cleanedBlock)
        if (current < SSD)
          SSD = current
          Cleaned.setblock(ci,cj,shuffledBlock)
          if (SSD == 0)
            Break
WritePGM(cleaned)
```

<h3>Task 1 NC</h3>
The Task1NC function works in the same way the `SSD` works but uses the `NC` member function and a Normalised Correlation variable set to -1. In the if statement it will check is current is greater than Normalised Correlation as the better the match in Normalised Correlation the closer to 1 it will be. The program will then break out of the loop if Normalised Correlation equals 1. 

<h3>Task 2 SSD</h3>
For `Task2SSD` function it takes two arguments the cluttered scene pointer and the `Wally` pointer. It will then create two matrices with this data to hold the two images. Two nested for loops will then be used to get block from the cluttered scene and will increase by 12 and 9 a quarter of the Wally image dimension. This increases the running speed of the application dramatically and still gives a level of accuracy. In order to increase the accuracy the number that `i` and `j` increases can be changed but may cause the application to be slow. The program compares the cluttered block to `Wally` image and if it is lower than the current lowest the location will then be sorted. Once Wally has been compared to every block in the scene the black matrix will be set to the location of Wally in the cluttered scene. The cluttered scene will then be written to a PGM file.
```C++
Matrix Cluttered(clutteredData)
Matrix Wally(wallyData)
for(i = 0; i < 720; i+=12)
  for(j = 0; j < 988; j+=9)
    SSD = Clusted.getBlock(i,j).SSD(Wally)
    if(SSD > current)
      SSD = current
      Ai = i Aj = j
Cluttered.setblock(Ai,Aj,black)
WritePGM(Cluttered)
```

<h3>Task 2 NC</h3>
The `Task2NC` function works the same way as the `Task2SSD` but uses the NC member function. In the if statement it checks if the current is greater than Normalised Correlation.

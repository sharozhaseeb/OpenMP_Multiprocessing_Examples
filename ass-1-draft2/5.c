#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void swap_array(int *first_array, int *second_array)
{
    int temp = *first_array;
    *first_array = *second_array;
    *second_array = temp;
}

int partition(int *array, int MIN, int MAX)
{
    int pivot_point = array[MAX];
    int iteration_x = MIN - 1;
    for (int iteration_y = MIN; iteration_y < MAX; iteration_y++)
    {
        if (array[iteration_y] < pivot_point)
        {
            iteration_x++;
            swap_array(&array[iteration_x], &array[iteration_y]);
        }
    }
    swap_array(&array[iteration_x + 1], &array[MAX]);
    return iteration_x + 1;
}

void quickSort(int *array, int MIN, int MAX)
{
    if (MIN < MAX)
    {
        int pi = partition(array, MIN, MAX);
        quickSort(array, MIN, pi - 1);
        quickSort(array, pi + 1, MAX);
    }
}

void printMatrix(int **matrix, int rows, int columns)
{
    for (int iteration_x = 0; iteration_x < rows; iteration_x++)
    {
        for (int iteration_y = 0; iteration_y < columns; iteration_y++)
        {
            printf("%d ", matrix[iteration_x][iteration_y]);
        }
        printf("\n");
    }
}

int main()
{
    int rows, columns;
    printf("Enter the number of rows and columns seperated by a space: ");
    scanf("%d %d", &rows, &columns);
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int iteration_x = 0; iteration_x < rows; iteration_x++)
    {
        matrix[iteration_x] = (int *)malloc(columns * sizeof(int));
    }
    srand(time(0));
    for (int iteration_x = 0; iteration_x < rows; iteration_x++)
    {
        for (int iteration_y = 0; iteration_y < columns; iteration_y++)
        {
            matrix[iteration_x][iteration_y] = rand() % 100;
        }
    }
    printf("\nMatrix:\n");
    printMatrix(matrix, rows, columns);
    int studentID;
    printf("\nEnter your student ID: ");
    scanf("%d", &studentID);
    int lastDigit = studentID % 10;
    int sum = 0;
    if (lastDigit == 0 || lastDigit == 1 || lastDigit == 2)
    {
        #pragma omp parallel for num_threads(columns)
        for (int iteration_x = 0; iteration_x < columns; iteration_x++)
        {
            quickSort(matrix[iteration_x], 0, rows - 1);
            for (int iteration_y = 0; iteration_y < rows; iteration_y++)
            {
                sum += matrix[iteration_y][iteration_x];
            }
        }
    }
    
    else if (lastDigit == 3 || lastDigit == 4 || lastDigit == 5)
    {
        #pragma omp parallel for num_threads(columns)
        for (int iteration_x = 0; iteration_x < columns; iteration_x++)
        {
            quickSort(matrix[iteration_x], 0, rows - 1);
            for (int iteration_y = 0; iteration_y < rows; iteration_y++)
            {
                sum += matrix[iteration_y][iteration_x];
            }
        }
    }
    else if (lastDigit == 6 || lastDigit == 7)
    {
        #pragma omp parallel for num_threads(rows)
        for (int iteration_x = 0; iteration_x < rows; iteration_x++)
        {
            quickSort(matrix[iteration_x], 0, columns - 1);
            for (int iteration_y = 0; iteration_y < columns; iteration_y++)
            {
                sum += matrix[iteration_x][iteration_y];
            }
        }
    }

    else if (lastDigit == 8 || lastDigit == 9)
    {
        #pragma omp parallel for num_threads(rows)
        for (int iteration_x = 0; iteration_x < rows; iteration_x++)
        {
            quickSort(matrix[iteration_x], 0, columns - 1);
            for (int iteration_y = 0; iteration_y < columns; iteration_y++)
            {
                sum += matrix[iteration_x][iteration_y];
            }
        }
    }

    printf("\nSorted Matrix:\n");
    printMatrix(matrix, rows, columns);
    printf("\nSum of all elements: %d\n", sum);
    return 0;
}

/*

The above code is a C program that generates a random matrix of size rows x columns and performs quicksort on its rows or
columns depending on the last digit of the user's input student ID. The sum of all elements of the matrix is also calculated and printed.

The program starts by including the required header files, which are stdio.h, stdlib.h, omp.h, and time.h. 
Then, the function swap_array() is defined to swap two integers, and the function partition() is defined to partition an array using the last element as the pivot_point.

The function quickSort() is defined to perform quicksort on an array. It uses partition() to partition the array and recursively sorts the subarrays.

The function printMatrix() is defined to print the elements of a matrix.

In the main function, the user is prompted to enter the number of rows and columns of the matrix. The matrix is
then dynamically allocated using malloc(), and each element is initialized with a random integer between 0 and 99 using rand().

The user is then prompted to enter their student ID, and the last digit of the ID is computed using the modulo operator.
Depending on the last digit, quicksort is performed on the rows or columns of the matrix using OpenMP parallelization.

If the last digit is 0, 1, or 2, quicksort is performed on each column of the matrix using OpenMP parallelization.
If the last digit is 3, 4, or 5, quicksort is performed on each column of the matrix using OpenMP parallelization.
If the last digit is 6 or 7, quicksort is performed on each row of the matrix using OpenMP parallelization.
If the last digit is 8 or 9, quicksort is performed on each row of the matrix using OpenMP parallelization.

Finally, the sorted matrix and the sum of all elements are printed using the printMatrix() function and printf()
function, respectively.

In summary, the program generates a random matrix, performs quicksort on its rows or columns using OpenMP parallelization,
and calculates the sum of all elements. The specific operation to be performed (sorting rows or columns) is determined by
the last digit of the user's input student ID.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_NAME "cities.csv"
#define MAX 10000

typedef struct {
    char *city;
    int pop; 
    char *country;
} place;
int compare(const void *a, const void *b)
{
    int *aa, *bb;
    int res;
    aa = (int *)a;
    bb = (int *)b;
    res = *aa - *bb;
    if (res > 0)
    {
        return 1;
    }
    else return -1;
}
/*for some reason this function wouldn't work - so i had to brute force
// int compare_city(const void *citya, const void *cityb)
// {
//     place *ca=(place *)citya;
//     place *cb=(place *)cityb;
//     //printf("citya - %d\n",ca->pop);
//     return (ca->pop - cb->pop);
// }*/

void get_data(char *str, place *array[], int i)
{
    char* token = strtok(str,",");
    place *a = malloc(MAX);
    a->city = malloc(strlen(token)+1);
    strcpy(a->city,token);
    token = strtok(NULL,",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    token = strtok(NULL, ",");
    int b = atoi(token);
    a->pop = b;
    token = strtok(NULL, ",");
    a->country = malloc(strlen(token)+1);
    strcpy(a->country,token);
    array[i] = a;    
}
void cities_search(FILE *input)
{
    char str[MAX];
    place *city_array[MAX];
    int i = 0;
    fgets(str,sizeof(str),input);
    while(fgets(str,sizeof(str),input) != NULL)
    {
        get_data(str, city_array, i);
        i++;
    }
    
    /*qsort(city_array, i, sizeof(place), compare_city); this is the qsort for the one that didnt work*/
    int array[i];
    int l;
    for (l=0;l<i;l++)
    {
        array[l] = city_array[l]->pop;
    }
    qsort(array,i,sizeof(int),compare);
    place *city_array2[i];
    int m, n;
    int p = i;
    int g;
    for(m = 0;m<i;m++)
    {
        for (n=0;n<p;n++)
        {
            if (array[i-m-1] == city_array[n]->pop)
            {
                /*printf("city_array pop = %d\n", city_array[n]->pop);*/
                city_array2[m] = city_array[n];
                for(g = 0;g<=(p-n);g++)
                {
                    city_array[n+g] = city_array[n+g+1];
                }
                p--;
                break;
            }
        }
    }

    int j;
    FILE *output;
    char *outputname = "sorted.csv";
    output = fopen(outputname,"w+");
    for (j =0;j<i;j++)
    {
        fprintf(output, "%s, %d, %s\n", city_array2[j]->city, city_array2[j]->pop, city_array2[j]->country);
    }

}
int main()
{
    FILE *fp;
    fp = fopen(FILE_NAME, "r+");
    if (fp == NULL)
    {
        printf("Can't open %s\n", FILE_NAME);
        exit(EXIT_FAILURE);
    }
    cities_search(fp);
    fclose(fp);
    return 0;
}
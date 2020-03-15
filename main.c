#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


unsigned int ns[] = {2, 10, 500, 1000, 2000, 5000, 10000, 15000, 20000, 30000};

void fill_increasing(int *t, unsigned int n) {
    for(int i = 0; i < n; i++)
    t[i] = i;
}

void fill_decreasing(int *t, unsigned int n) {
    for(int i = 0; i < n; i++)
    t[i] = -i;
}

void fill_vshape(int *t, unsigned int n) {
    int j = 0;
    int k = n-1;
    for(int i = n; i > 0; i--)
    {
      if(i % 2 == 0)
      {
        t[j] = i;
      j++;
      }
      else
      {
        t[k] = i;
        k--;
      }
    }
}

void swap(int *t, int i, int j)
    {
    int tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
    }


void selection_sort(int *t, unsigned int n)
{
      int i, j, minimal;

    for (i = 0; i < n-1; i++)
    {
        minimal = i;
        for (j = i+1; j < n; j++)
          if (t[j] < t[minimal])
            minimal = j;
        swap(t, minimal, i);
    }
}

void insertion_sort(int *t, unsigned int n)
{
int key, i, j;
    for( j = 1; j <= n-1; j++)
        {
        key = t[j];
        i = j - 1;
        while(i >= 0 && t[i]>key)
            {
            t[i+1] = t[i];
            i = i - 1;
            }


        t[i+1] = key;
}
}


int partition(int *t,int p,int r)
{
    int x = t[r];
    int i = (p - 1);
    int j;
    for(j=p; j<r; j++)
        {
            if(t[j] <= x)
            {
                i++;
                swap(t, i, j);
            }
        }
    i = i+1;
    swap(t, i, r);
    return i;
}

int random_partition(int *t,int  p,int  r)
{
    int i = p + rand()%r;
    swap(t, i, r);
    return partition(t, p, r);
}

void quick__sort(int *t,int p,int r)
{
    if(p < r)
        {
        int q = partition(t, p, r);
        quick__sort(t, p, q - 1);
        quick__sort(t, q + 1, r);
        }
}

void quick_sort(int *t, unsigned int n)
{
    quick__sort(t, 0, n - 1);
}

void heapify(int *arr, int n, int i)
    {
        int largest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;

        if (l < n && arr[l] > arr[largest])
            largest = l;

        if (r < n && arr[r] > arr[largest])
            largest = r;

        if (largest != i)
        {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            heapify(arr, n, largest);
        }
    }

    void heap_sort(int *t, unsigned int n) {
          for (int i = n / 2 - 1; i >= 0; i--)
            heapify(t, n, i);

        for (int i=n-1; i>=0; i--)
        {
            int temp = t[0];
            t[0] = t[i];
            t[i] = temp;

            heapify(t, i, 0);
        }
}

void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i-1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}


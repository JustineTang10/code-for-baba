#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SEQUENCES 10000
#define MAX_LIMIT 250
static int sequences[MAX_SEQUENCES][2];
static int bisquares[2 * MAX_LIMIT * MAX_LIMIT];
int count = 0;
int bisquare_count = 0;

/*int compare(const void *a[], const void *b[]) {
  return (*((int*)a[1]) - *((int*)b[1]));
}*/

int is_bisquare(int number) {
  double start = 0, end = bisquare_count - 1;
  double mid;
  if (bisquares[bisquare_count - 1] == number)
    return 1;
  while (floor(end - start) > 0) {
    mid = (end + start) / 2;
    if (bisquares[(int) floor(mid)] == number)
      return 1;
    if (bisquares[(int) floor(mid)] > number)
      start = mid;
    else
      end = mid;
  }
  return 0;
}

void search(int len, int limit, int start, int difference, 
            int initial_start) {
  if (is_bisquare(start) == 0)
    return;
  if (len == 0) {
    sequences[count][0] = initial_start;
    sequences[count][1] = difference;
    count++;
    return;
  }
  search(len - 1, limit, start + difference, difference, 
          initial_start);
}

int main(void) {
  clock_t t = clock();
  FILE *fin = fopen("ariprog.in", "r");
  FILE *fout = fopen("ariprog.out", "w");
  int n, m;
  register int i, j, k;
  int swap[2];
  fscanf(fin, "%d\n%d", &n, &m);
  double square_root;
  int limit = (m * m) << 1;
  for (i = limit; i >= 0; i--) {
    for (j = 0; j <= m; j++) {
      square_root = sqrt((double) i - j * j);
      if (round(square_root) == square_root && 
          square_root <= m) {
        bisquares[bisquare_count] = i;
        bisquare_count++;
        if (i <= limit - n)
          for (k = bisquare_count - 2; k >= 0; k--) {
            if (i + (bisquares[k] - i) * (n - 1) > limit)
              continue;
            search(n - 1, m, i, bisquares[k] - i, i);
          }
        break;
      }
    }
  }
  /*for (i = 1; i <= ceil((double) 2 * m * m / (n - 1)); i++)
    for (j = 0; j < bisquare_loop_count; j++) {
      if (bisquares[j] + i * (n - 1) > 2 * m * m)
        continue;
      search(n - 1, m, bisquares[j], i, bisquares[j]);
    }*/
  //qsort(sequences, count, sizeof(int) * 2, compare);
  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if ((sequences[i][1] > sequences[j][1]) ||
          (sequences[i][1] == sequences[j][1] &&
          sequences[i][0] > sequences[j][0])) {
        swap[0] = sequences[i][0];
        swap[1] = sequences[i][1];
        sequences[i][0] = sequences[j][0];
        sequences[i][1] = sequences[j][1];
        sequences[j][0] = swap[0];
        sequences[j][1] = swap[1];
      }
    }
    fprintf(fout, "%d %d\n", sequences[i][0], sequences[i][1]);
  }
  if (count == 0)
    fprintf(fout, "NONE\n");
  t = clock() - t;
  printf("%f\n", ((double)t)/CLOCKS_PER_SEC);
  return 0;
}

/* // alternate (slower) code

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SEQUENCES 10000
#define MAX_LIMIT 250
static int sequences[MAX_SEQUENCES][2];
static int bisquares[2 * MAX_LIMIT * MAX_LIMIT];
int count = 0;
int bisquare_count = 0;

int compare(const void *a, const void *b) {
  return (*((int*)a) - *((int*)b));
}

int is_bisquare(int number) {
  double start = 0, end = bisquare_count - 1;
  double mid;
  if (end == -1)
    return 0;
  if (bisquares[bisquare_count - 1] == number)
    return 1;
  while (floor(end - start) > 0) {
    mid = (end + start) / 2;
    if (bisquares[(int) floor(mid)] == number)
      return 1;
    if (bisquares[(int) floor(mid)] > number)
      end = mid;
    else
      start = mid;
  }
  return 0;
}

void search(int len, int start, int difference, 
            int initial_start) {
  if (is_bisquare(start) == 0)
    return;
  if (len == 0) {
    sequences[count][0] = initial_start;
    sequences[count][1] = difference;
    count++;
    return;
  }
  search(len - 1, start + difference, difference, initial_start);
}

int main(void) {
  clock_t t = clock();
  FILE *fin = fopen("ariprog.in", "r");
  FILE *fout = fopen("ariprog.out", "w");
  int n, m;
  int swap[2];
  register int i, j;
  fscanf(fin, "%d\n%d", &n, &m);
  for (i = 0; i <= m; i++)
    for (j = i; j <= m; j++) {
      bisquares[bisquare_count] = i * i + j * j;
      bisquare_count++;
    }
  qsort(bisquares, bisquare_count, sizeof(int), compare);
  for (i = 0; i < bisquare_count; i++)
    for (j = i - 1; j >= 0; j--) {
      if (bisquares[j] + (bisquares[i] - bisquares[j]) * (n - 1) > 2 * m * m)
        continue;
      search(n - 1, bisquares[j], bisquares[i] - bisquares[j], 
              bisquares[j]);
    }
  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if ((sequences[i][1] > sequences[j][1]) ||
          (sequences[i][1] == sequences[j][1] &&
          sequences[i][0] > sequences[j][0])) {
        swap[0] = sequences[i][0];
        swap[1] = sequences[i][1];
        sequences[i][0] = sequences[j][0];
        sequences[i][1] = sequences[j][1];
        sequences[j][0] = swap[0];
        sequences[j][1] = swap[1];
      }
    }
    if (sequences[i][1] == 0)
      continue;
    fprintf(fout, "%d %d\n", sequences[i][0], sequences[i][1]);
  }
  if (count == 0)
    fprintf(fout, "NONE\n");
  t = clock() - t;
  printf("%f\n", ((double)t)/CLOCKS_PER_SEC * 2);
  return 0;
}
*/

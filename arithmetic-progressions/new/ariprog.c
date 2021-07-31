#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SEQUENCES 10000
#define MAX_LIMIT 250

typedef struct sequence {
  int start;
  int difference;
} sequence;

static sequence sequences[MAX_SEQUENCES];
static int bisquares[2 * MAX_LIMIT * MAX_LIMIT];
int count = 0;
int bisquare_count = 0;

int compare(const void *a, const void *b) {
  return (*((int*)a) - *((int*)b));
}

int seq_compare(const void *a, const void *b) {
  sequence *seq_a = (sequence*) a;
  sequence *seq_b = (sequence*) b;
  if (seq_a->difference == seq_b->difference)
    return seq_a->start - seq_b->start;
  return seq_a->difference - seq_b->difference;
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
    sequences[count].start = initial_start;
    sequences[count].difference = difference;
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
  //int swap[2];
  register int i, j;
  fscanf(fin, "%d\n%d", &n, &m);
  for (i = 0; i <= m; i++)
    for (j = i; j <= m; j++) {
      if (is_bisquare(i * i + j * j) == 0) {
        bisquares[bisquare_count] = i * i + j * j;
        bisquare_count++;
        qsort(bisquares, bisquare_count, sizeof(int), compare);
      }
    }
  for (i = 0; i < bisquare_count; i++)
    for (j = i - 1; j >= 0; j--) {
      if (bisquares[j] + (bisquares[i] - bisquares[j]) * (n - 1) > 2 * m * m)
        break;
      search(n - 1, bisquares[j], bisquares[i] - bisquares[j], 
              bisquares[j]);
    }
  qsort(sequences, count, sizeof(sequence), seq_compare);
  /*for (i = 0; i < count; i++) {
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
  }*/
  if (count == 0)
    fprintf(fout, "NONE\n");
  for (i = 0; i < count; i++)
    if (sequences[i].difference > 0)
      fprintf(fout, "%d %d\n", sequences[i].start, 
              sequences[i].difference);
  t = clock() - t;
  printf("%f\n", ((double)t)/CLOCKS_PER_SEC * 2);
  return 0;
}

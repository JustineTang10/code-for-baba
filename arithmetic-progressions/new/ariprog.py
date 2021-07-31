import time

t = time.time()

fin = open('ariprog.in', 'r')
fout = open('ariprog.out', 'w')

n, m = [int(i) for i in fin.read().strip().split()]
bisquares = set()
#calculated = {}
sequences = []
for i in range(m + 1):
  for j in range(m + 1):
    bisquares.add(i * i + j * j)
bisquares_list = sorted(list(bisquares))

"""def is_bisquare(number):
  bisquare_count = len(bisquares)
  start = 0
  end = bisquare_count - 1
  if end == -1:
    return 0
  if bisquares[bisquare_count - 1] == number:
    return 1
  while end - start > 1:
    mid = int((end + start) / 2)
    if bisquares[mid] == number:
      return 1
    if bisquares[mid] > number:
      end = mid
    else:
      start = mid
  return 0"""

def search(l, start, difference, initial_start):
  """if (start, difference) in calculated.keys():
    if calculated[(start, difference)] == False: return"""
  #else:
    #calculated[(start, difference)] = True
  if not start in bisquares:
    #calculated[(start, difference)] = False
    return
  if l == 0:
    sequences.append([initial_start, difference])
    return
  search(l - 1, start + difference, difference, initial_start)

for i in range(len(bisquares_list)):
  for j in range(i + 1, len(bisquares_list)):
    if bisquares_list[i] + (bisquares_list[j] - bisquares_list[i]) * (n - 1) > 2 * m * m: continue
    search(n - 1, bisquares_list[i], bisquares_list[j] - bisquares_list[i],
            bisquares_list[i])

sequences.sort(key=lambda x: x[1])

for sequence in sequences:
  fout.write(f"{' '.join([str(i) for i in sequence])}\n")
if len(sequences) == 0:
  fout.write('NONE\n')

fin.close()
fout.close()

print(time.time() - t)

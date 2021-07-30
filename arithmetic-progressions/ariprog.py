import math, time

t = time.time()

fin = open('ariprog.in', 'r')
fout = open('ariprog.out', 'w')

n, m = [int(i) for i in fin.read().strip().split()]
bisquares = set()
calculated = {}
sequences = []
for i in range(m + 1):
  for j in range(m + 1):
    bisquares.add(i * i + j * j)
bisquares = sorted(list(bisquares))

def is_bisquare(number):
  bisquare_count = len(bisquares)
  start = 0
  end = bisquare_count - 1
  if end == -1:
    return 0
  if bisquares[bisquare_count - 1] == number:
    return 1
  while math.floor(end - start) > 0:
    mid = (end + start) / 2
    if bisquares[math.floor(mid)] == number:
      return 1
    if bisquares[math.floor(mid)] > number:
      end = mid
    else:
      start = mid
  return 0

def search(l, start, difference, initial_start):
  if (start, difference) in calculated.keys():
    if calculated[(start, difference)] == False: return
  else:
    calculated[(start, difference)] = True
    if is_bisquare(start) == 0:
      calculated[(start, difference)] = False
      return
  if l == 0:
    if [initial_start, difference] not in sequences:
      sequences.append([initial_start, difference])
    return
  search(l - 1, start + difference, difference, initial_start)

for i in range(len(bisquares)):
  for j in range(i + 1, len(bisquares)):
    if bisquares[i] + (bisquares[j] - bisquares[i]) * (n - 1) > 2 * m * m: continue
    search(n - 1, bisquares[i], bisquares[j] - bisquares[i],
            bisquares[i])

sequences.sort(key=lambda x: x[1])

for sequence in sequences:
  fout.write(f"{' '.join([str(i) for i in sequence])}\n")
if len(sequences) == 0:
  fout.write('NONE\n')

fin.close()
fout.close()

print(time.time() - t)

""" # alternate (slower) code
import math, time, copy

t = time.time()

fin = open('ariprog.in', 'r')
fout = open('ariprog.out', 'w')

n, m = [int(i) for i in fin.read().strip().split()]
bisquares = set()
sequences = []
for i in range(m + 1):
  for j in range(m + 1):
    bisquares.add(i * i + j * j)
bisquares = sorted(list(bisquares))

def is_bisquare(number, bisquares):
  bisquare_count = len(bisquares)
  start = 0
  end = bisquare_count - 1
  if end == -1:
    return False
  if bisquares[bisquare_count - 1] == number:
    return True
  while math.floor(end - start) > 0:
    mid = (end + start) / 2
    if bisquares[math.floor(mid)] == number:
      return True
    if bisquares[math.floor(mid)] > number:
      end = mid
    else:
      start = mid
  return False

for i in range(len(bisquares)):
  for j in range(i + 1, len(bisquares)):
    if is_bisquare(bisquares[j] + bisquares[j] - bisquares[i],
                    bisquares) == True:
      sequences.append((bisquares[i], 
                        (bisquares[j] - bisquares[i]) * 2, 
                        bisquares[j] - bisquares[i]))

for i in range(n - 2):
  current_sequences = copy.copy(sequences)
  for sequence in current_sequences:
    if is_bisquare(sequence[0] + sequence[1], bisquares) == True:
      sequences[sequences.index(sequence)] = (sequence[0], 
                          sequence[1] + sequence[2], sequence[2])
    else:
      sequences.remove(sequence)

sequences.sort(key=lambda x: x[2])

for sequence in sequences:
  fout.write(f'{sequence[0]} {sequence[2]}\n')
if len(sequences) == 0:
  fout.write('NONE\n')

fin.close()
fout.close()

print(time.time() - t)
"""

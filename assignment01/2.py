import time
import numpy as np
from scipy.stats import mstats
size=1000000
def run_experiment(size):
    a = list(range(size))
    b = list(range(size))
    tik = time.time()
    for i in range(size):
        a[i] += b[i]
    tok = time.time()
    t1 = tok - tik

    na = np.arange(size)
    nb = np.arange(size)
    tik = time.time()
    na += nb
    tok = time.time()
    t2 = tok - tik

    return t1, t2

num_repetitions = 5

times_normal = []
times_numpy = []

for _ in range(num_repetitions):
    t_normal, t_numpy = run_experiment(size)
    times_normal.append(t_normal)
    times_numpy.append(t_numpy)

geometric_mean_normal = mstats.gmean(times_normal)
geometric_mean_numpy = mstats.gmean(times_numpy)

print("Geometric Mean without Outlier(Normal):", geometric_mean_normal, "seconds")
print("Geometric Mean without Outlier(NumPy):", geometric_mean_numpy, "seconds")
print("Speed Up:", geometric_mean_normal / geometric_mean_numpy, "times")

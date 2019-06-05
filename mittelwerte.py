import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import sem
from uncertainties import ufloat
from uncertainties.unumpy import (nominal_values as noms, std_devs as stds)
from scipy import optimize
import uncertainties.unumpy as unp
import scipy.constants as const

mittelwerte_ssbar = np.genfromtxt("lambda_mittelwerte1.txt")
mittelwerte_ddbar = np.genfromtxt("lambda_mittelwerte2.txt")
mittelwerte_uubar = np.genfromtxt("lambda_mittelwerte3.txt")

# mittelwerte
ssbar_mean = mean(mittelwerte_ssbar)
ddbar_mean = mean(mittelwerte_ddbar)
uubar_mean = mean(mittelwerte_uubar)

mitteltxt = np.array([mittelwerte_ssbar, mittelwerte_ddbar, mittelwerte_uubar])
mittel = np.array([ssbar_mean, ddbar_mean, uubar_mean])
laenge = np.array(len(mittelwerte_ssbar), len(mittelwerte_ddbar), len(mittelwerte_uubar)])
# mittelwert fehler
for i in range(3):
    factor = 1 / (laenge[i]*(laenge[i]-1))
    for k in range(laenge[i]):
        summe += (mittel[i] - mitteltxt[k])**2
    print(np.sqrt(factor*summe))

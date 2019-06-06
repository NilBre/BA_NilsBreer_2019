import numpy as np
import matplotlib.pyplot as plt
from scipy import optimize
from scipy.stats import sem
from uncertainties import ufloat
from uncertainties.unumpy import (nominal_values as noms, std_devs as stds)
import uncertainties.unumpy as unp
import scipy.constants as const

mittelwerte_ssbar = np.genfromtxt("lambda_mittelwerte1.txt")
mittelwerte_ddbar = np.genfromtxt("lambda_mittelwerte2.txt")
mittelwerte_uubar = np.genfromtxt("lambda_mittelwerte3.txt")

# mittelwerte
ssbar_mean = np.mean(mittelwerte_ssbar)
ddbar_mean = np.mean(mittelwerte_ddbar)
uubar_mean = np.mean(mittelwerte_uubar)

mittel = np.array([ssbar_mean, ddbar_mean, uubar_mean])
laenge = np.array([len(mittelwerte_ssbar), len(mittelwerte_ddbar), len(mittelwerte_uubar)])

# mittelwert fehler
for i in range(3):
    summe = 0
    factor = 1 / (laenge[i]*(laenge[i]-1))
    for k in range(laenge[i]):
        if i == 0:
            summe += (mittel[i] - mittelwerte_ssbar[k])**2
        if i == 1:
            summe += (mittel[i] - mittelwerte_ddbar[k])**2
        if i == 2:
            summe += (mittel[i] - mittelwerte_uubar[k])**2

    print("Der Fehler des Mittelwertes: ", np.sqrt(factor*summe), " zum Mittelwert: ", mittel[i])

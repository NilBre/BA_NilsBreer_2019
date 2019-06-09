import numpy as np
import matplotlib.pyplot as plt

# datenfiles fuer mittelwerte
mittelwerte_ssbar = np.genfromtxt("lambda_mittelwerte1.txt")
mittelwerte_ddbar = np.genfromtxt("lambda_mittelwerte2.txt")
mittelwerte_uubar = np.genfromtxt("lambda_mittelwerte3.txt")

# datenfiles fuer ROC Kurven
# a: links vom cut, b: rechts vom cut
j, a1, b1 = np.genfromtxt("ssbar_werte.txt", unpack=True)
j, a2, b2 = np.genfromtxt("ddbar_werte.txt", unpack=True)
j, a3, b3 = np.genfromtxt("uubar_werte.txt", unpack=True)

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

# auswertung der roc daten
# ssbar and ddbar
tp_ssdd = []
fp_ssdd = []
tn_ssdd = []
fn_ssdd = []
for i in range(len(a1)):
    tp_ssdd.append(abs(b1[i] - b2[i]))
    fp_ssdd.append(b2[i])
    tn_ssdd.append(abs(a2[i] - a1[i]))
    fn_ssdd.append(a1[i])

print("tp_ssdd", tp_ssdd)
print("fp_ssdd", fp_ssdd)
print("tn_ssdd", tn_ssdd)
print("fn_ssdd", fn_ssdd)

sens = []
spec = []
for w in range(len(a1)):
    calc_sens = tp_ssdd[w] / (tp_ssdd[w] + fn_ssdd[w])
    calc_spec = 1 - (tn_ssdd[w] / (fp_ssdd[w] + tn_ssdd[w]))
    sens.append(calc_sens)
    spec.append(calc_spec)

# sens.append(0)
# spec.append(1)

plt.plot(spec, sens, "b--", label="roc punkte")
plt.plot([0,1], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity")
plt.ylabel("sensitivity")
plt.savefig("ROC_xlambda.pdf")
plt.clf()

plt.plot(a1, b1, "r--", label="1")
plt.plot(a2, b2, "g--", label="2")
plt.plot(a3, b3, "b--", label="3")
plt.grid()
plt.legend()
plt.savefig("linke_seite.pdf")
plt.clf()
